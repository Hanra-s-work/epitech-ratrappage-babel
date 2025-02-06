/*
** EPITECH PROJECT, 2024
** send_receive_text
** File description:
** Listener.cpp
*/

#include "Network/Listener.hpp"

Network::Listener::Listener(const Network::AddressHolder &addressHolder)
    : _addressHolder(addressHolder), _io_context(), _acceptor(_io_context), _socket(_io_context), _translator()
{
    _initialiseAddress();
    _startAccept();
}

Network::Listener::~Listener()
{
    _socket.close();
}

void Network::Listener::_startAccept()
{
    _acceptor.async_accept(_socket, [this](std::error_code ec) {
        if (!ec) {
            std::cout << "Client connected" << std::endl;
            _startReceive();
        }
        _startAccept();
        });
}

void Network::Listener::_initialiseAddress()
{
    asio::ip::tcp::endpoint endpoint(asio::ip::make_address(_addressHolder.getIp()), _addressHolder.getPort());
    _acceptor.open(endpoint.protocol());
    _acceptor.set_option(asio::ip::tcp::acceptor::reuse_address(true));
    _acceptor.bind(endpoint);
    _acceptor.listen();
}

void Network::Listener::_startReceive()
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

void Network::Listener::sendData(const std::vector<Packet> &data)
{
    for (const auto &packet : data) {
        std::vector<uint8_t> byte_stream = _translator.serialize(packet);
        asio::write(_socket, asio::buffer(byte_stream));
    }
}

const std::vector<Network::Packet> Network::Listener::getPackets()
{
    std::lock_guard<std::mutex> lock(_mutex);
    std::vector<Packet> packets = _packets;
    _packets.clear();
    return packets;
}
