/*
** EPITECH PROJECT, 2024
** send_receive_text
** File description:
** Tcp.cpp
*/

#include "Network/Tcp.hpp"

Network::Tcp::Tcp(const AddressHolder &addressHolder)
    : _addressHolder(addressHolder), _ioContext(), _socket(_ioContext)
{
    _initialiseAddress();
    _startAccept();
}

Network::Tcp::~Tcp()
{
    if (_socket.is_open()) {
        _socket.close();
    }
}

void Network::Tcp::sendData(const std::string &data)
{
    asio::async_write(_socket, asio::buffer(data),
        [this](std::error_code ec, std::size_t /*length*/) {
            if (!ec) {
                std::lock_guard<std::mutex> lock(_mutex);
                _packets.push_back(data);
            } else {
                std::cerr << "Send failed: " << ec.message() << std::endl;
            }
        });
}

const std::vector<std::string> Network::Tcp::getPackets()
{
    std::lock_guard<std::mutex> lock(_mutex);
    return _packets;
}

const bool Network::Tcp::isConnected() const
{
    return _socket.is_open();
}

void Network::Tcp::_startAccept()
{
    _socket.async_connect(_endpoint,
        [this](std::error_code ec) {
            if (!ec) {
                _startReceive();
            } else {
                std::cerr << "Connect failed: " << ec.message() << std::endl;
            }
        });
}

void Network::Tcp::_initialiseAddress()
{
    asio::ip::tcp::resolver resolver(_ioContext);
    asio::ip::tcp::resolver::results_type endpoints = resolver.resolve(_addressHolder.getIp(), std::to_string(_addressHolder.getPort()));
    _endpoint = *endpoints.begin();
}

void Network::Tcp::_startReceive()
{
    _socket.async_receive(asio::buffer(_buffer),
        [this](std::error_code ec, std::size_t length) {
            if (!ec) {
                std::lock_guard<std::mutex> lock(_mutex);
                _packets.push_back(std::string(_buffer.data(), length));
                _startReceive();
            } else {
                std::cerr << "Receive failed: " << ec.message() << std::endl;
            }
        });
}
