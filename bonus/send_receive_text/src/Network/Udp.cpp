/*
** EPITECH PROJECT, 2024
** send_receive_text
** File description:
** Udp.cpp
*/

#include "Network/Udp.hpp"


Network::Udp::Udp(const AddressHolder &addressHolder)
    : _addressHolder(addressHolder), _acceptor(_io_context), _socket(_io_context)
{
    _initialiseAddress();
    _startConnect();
}

Network::Udp::~Udp()
{
    _io_context.stop();
}

void Network::Udp::send(const Packet &data)
{
    std::vector<uint8_t> byte_stream = _translator.serialize(data);
    _socket.async_send(asio::buffer(byte_stream),
        [this](std::error_code ec, std::size_t /*length*/) {
            if (ec) {
                std::cerr << "Error sending data: " << ec.message() << std::endl;
            }
        });
}

const std::vector<Packet> Network::Udp::getReceivedData()
{
    std::lock_guard<std::mutex> lock(_mutex);
    std::vector<Packet> packets;
    for (const auto &packet : _packets) {
        packets.emplace_back(packet.begin(), packet.end());
    }
    return packets;
}

void Network::Udp::_startConnect()
{
    _acceptor.async_accept(_socket, [this](std::error_code ec) {
        if (!ec) {
            _startSend();
        }
        });
    _io_context.run();
}

void Network::Udp::_initialiseAddress()
{
    asio::ip::tcp::endpoint endpoint(asio::ip::make_address(_addressHolder.getIp()), _addressHolder.getPort());
    _acceptor.open(endpoint.protocol());
    _acceptor.bind(endpoint);
    _acceptor.listen();
}

void Network::Udp::_startSend()
{
    _socket.async_read_some(asio::buffer(_buffer), [this](std::error_code ec, std::size_t length) {
        if (!ec) {
            std::lock_guard<std::mutex> lock(_mutex);
            _packets.emplace_back(_buffer.data(), _buffer.data() + length);
            _startSend();
        }
        });
}

void Network::Udp::_startReceive()
{
    _socket.async_receive(asio::buffer(_buffer),
        [this](std::error_code ec, std::size_t length) {
            if (!ec) {
                std::lock_guard<std::mutex> lock(_mutex);
                std::vector<uint8_t> byte_stream(_buffer.data(), _buffer.data() + length);
                Packet packet = _translator.deserialize(byte_stream);
                _packets.push_back(packet);
                _startReceive();
            }
        });
}

Network::Udp::Udp(const Network::AddressHolder &addressHolder)
    : _addressHolder(addressHolder), _socket(_io_context, asio::ip::udp::endpoint(asio::ip::udp::v4(), 0))
{
    _initialiseAddress();
    _startReceive();
}
