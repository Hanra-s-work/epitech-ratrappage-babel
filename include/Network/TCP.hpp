/*
** EPITECH PROJECT, 2024
** send_receive
** File description:
** TCP.hpp
*/

/**
 * @file TCP.hpp
 * @brief This file contains the definition of the TCP class for handling TCP network communication.
 */

#pragma once

#include <string>
#include <iostream>
#include <asio.hpp>
#include <queue>
#include <thread>
#include <memory>
#include "Logging.hpp"

namespace Network
{
    /**
     * @class TCP
     * @brief A class for handling TCP network communication.
     */
    class TCP {
        public:
        /**
         * @brief Construct a new TCP object.
         *
         * @param io_context The ASIO I/O context.
         * @param ip The IP address to bind or connect to.
         * @param port The port number to bind or connect to.
         * @param is_sender Indicates whether the instance is for sending or receiving.
         */
        TCP(asio::io_context &io_context, const std::string &ip, int port, bool is_sender);
        /**
         * @brief Destroy the TCP object.
         */
        ~TCP();

        /**
         * @brief Send a message to the connected peer.
         *
         * @param message The message to send.
         */
        void sendTo(const std::string &message);

        /**
         * @brief Receive a message from the connected peer.
         *
         * @return The received message.
         */
        std::string receive();

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
        /**
         * @brief Accept connections (for receiver mode).
         */
        void startAccept();

        /**
         * @brief Read data asynchronously (for both sender and receiver).
         */
        void startRead();

        asio::io_context &_io_context; //!< The ASIO I/O context.
        asio::ip::tcp::socket _socket; //!< The TCP socket.
        asio::ip::tcp::acceptor _acceptor; //!< The TCP acceptor (for receiver mode).
        bool _is_sender; //!< Indicates whether the instance is for sending or receiving.
        std::queue<std::string> _received_packets; //!< Queue for storing received packets.
        std::shared_ptr<std::thread> _server_thread; //!< Thread for running the server (for receiver mode).
    };
}
