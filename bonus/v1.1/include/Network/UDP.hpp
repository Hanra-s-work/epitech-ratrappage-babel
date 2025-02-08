/*
** EPITECH PROJECT, 2024
** send_receive
** File description:
** UDP.hpp
*/

/**
 * @file UDP.hpp
 * @brief This file contains the definition of the UDP class for handling UDP network communication.
 */

#pragma once

#include <string>
#include <iostream>
#include <asio.hpp>
#include <queue>

namespace Network
{
    /**
     * @class UDP
     * @brief A class for handling UDP network communication.
     */
    class UDP {
        public:
        /**
         * @brief Construct a new UDP object.
         *
         * @param io_context The ASIO I/O context.
         * @param ip The IP address to bind or connect to.
         * @param port The port number to bind or connect to.
         * @param is_sender Indicates whether the instance is for sending or receiving.
         */
        UDP(asio::io_context &io_context, const std::string &ip, int port, bool is_sender);
        /**
         * @brief Destroy the UDP object.
         */
        ~UDP();

        /**
         * @brief Send a message to a specified address and port.
         *
         * @param message The message to send.
         * @param address The destination IP address.
         * @param port The destination port number.
         */
        void sendTo(const std::string &message, const std::string &address, int port);

        /**
         * @brief Send raw data to a specified address and port.
         *
         * @param data The raw data to send.
         * @param size The size of the data.
         * @param address The destination IP address.
         * @param port The destination port number.
         */
        void sendRaw(const char *data, std::size_t size, const std::string &address, int port);

        /**
         * @brief Receive a message from a specified address and port.
         *
         * @param address The source IP address.
         * @param port The source port number.
         * @return The received message.
         */
        std::string receiveFrom(std::string &address, int &port);

        /**
         * @brief Check if the connection is alive.
         *
         * @return `true` if the connection is alive; `false` otherwise.
         */
        bool isConnectionAlive();

        /**
         * @brief Fetch a packet from the received packets queue.
         *
         * @return The fetched packet.
         */
        std::string fetchPacket();

        private:
        bool _is_sender; //!< Indicates whether the instance is for sending or receiving.
        asio::ip::udp::socket _socket; //!< The UDP socket.
        std::queue<std::string> _received_packets; //!< Queue for storing received packets.
    };
}
