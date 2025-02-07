/*
** EPITECH PROJECT, 2024
** send_receive
** File description:
** UDP.cpp
*/

#include "Network/UDP.hpp"

namespace Network
{
    UDP::UDP(asio::io_context &io_context, const std::string &ip, int port, bool is_sender)
        : _socket(io_context), _is_sender(is_sender)
    {
        if (_is_sender) {
            _socket.open(asio::ip::udp::v4());
        } else {
            asio::ip::udp::endpoint endpoint(asio::ip::address::from_string(ip), port);
            _socket.open(endpoint.protocol());
            _socket.bind(endpoint);
        }
    }

    UDP::~UDP()
    {
        _socket.close();
    }

    void UDP::sendTo(const std::string &message, const std::string &address, int port)
    {
        asio::ip::udp::endpoint endpoint(asio::ip::address::from_string(address), port);
        _socket.send_to(asio::buffer(message), endpoint);
    }

    void UDP::sendRaw(const char *data, std::size_t size, const std::string &address, int port)
    {
        asio::ip::udp::endpoint endpoint(asio::ip::address::from_string(address), port);
        _socket.send_to(asio::buffer(data, size), endpoint);
    }

    std::string UDP::receiveFrom(std::string &address, int &port)
    {
        char buffer[1024];
        asio::ip::udp::endpoint sender_endpoint;
        size_t len = _socket.receive_from(asio::buffer(buffer), sender_endpoint);

        address = sender_endpoint.address().to_string();
        port = sender_endpoint.port();

        std::string received_data(buffer, len);
        _received_packets.push(received_data);

        return received_data;
    }

    bool UDP::isConnectionAlive()
    {
        return _socket.is_open();
    }

    std::string UDP::fetchPacket()
    {
        if (_received_packets.empty()) {
            return "";
        }
        std::string packet = _received_packets.front();
        _received_packets.pop();
        return packet;
    }
}
