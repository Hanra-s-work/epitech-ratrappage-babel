/*
** EPITECH PROJECT, 2024
** send_receive
** File description:
** UDP.cpp
*/

/**
 * @file UDP.cpp
 *
 * @brief This file contains the implementation of the UDP class for network communication.
 */

#include "Network/UDP.hpp"

namespace Network
{
    /**
     * @brief Constructs a new UDP object.
     *
     * @param io_context The ASIO I/O context.
     * @param ip The IP address to bind or connect to.
     * @param port The port number to bind or connect to.
     * @param is_sender True if the UDP object is for sending, false if for receiving.
     */
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
        _socket.non_blocking(true);
    }

    /**
     * @brief Destroys the UDP object.
     */
    UDP::~UDP()
    {
        _socket.close();
    }

    /**
     * @brief Sends a message to the specified address and port.
     *
     * @param message The message to send.
     * @param address The destination IP address.
     * @param port The destination port number.
     */
    void UDP::sendTo(const std::string &message, const std::string &address, int port)
    {
        asio::ip::udp::endpoint endpoint(asio::ip::address::from_string(address), port);
        _socket.send_to(asio::buffer(message), endpoint);
    }

    /**
     * @brief Sends raw data to the specified address and port.
     *
     * @param data The raw data to send.
     * @param size The size of the data.
     * @param address The destination IP address.
     * @param port The destination port number.
     */
    void UDP::sendRaw(const char *data, std::size_t size, const std::string &address, int port)
    {
        asio::ip::udp::endpoint endpoint(asio::ip::address::from_string(address), port);
        _socket.send_to(asio::buffer(data, size), endpoint);
    }

    /**
     * @brief Receives a message from a remote endpoint.
     *
     * @param address The source IP address.
     * @param port The source port number.
     * @return The received message.
     */
    std::string UDP::receiveFrom(std::string &address, int &port)
    {
        char buffer[1024];
        asio::ip::udp::endpoint sender_endpoint;
        std::error_code ec; // Error code object

        size_t len = _socket.receive_from(asio::buffer(buffer), sender_endpoint, 0, ec);

        if (ec == asio::error::would_block) {
            PRETTY_WARNING << "Would block" << std::endl;
            return "";
        }

        if (ec) {
            PRETTY_WARNING << "Receive failed: " << ec.message() << std::endl;
            throw std::runtime_error("Receive failed: " + ec.message());
        }

        address = sender_endpoint.address().to_string();
        port = sender_endpoint.port();

        std::string received_data(buffer, len);
        _received_packets.push(received_data);
        return received_data;
    }

    /**
     * @brief Checks if the connection is alive.
     *
     * @return True if the connection is alive, otherwise false.
     */
    bool UDP::isConnectionAlive()
    {
        return _socket.is_open();
    }

    /**
     * @brief Fetches a received packet from the queue.
     *
     * @return The received packet.
     */
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
