/*
** EPITECH PROJECT, 2024
** send_receive
** File description:
** UDP.hpp
*/

#pragma once

#include <string>
#include <iostream>
#include <asio.hpp>
#include <queue>

namespace Network
{
    class UDP {
        public:
        UDP(asio::io_context &io_context, const std::string &ip, int port, bool is_sender);
        ~UDP();

        void sendTo(const std::string &message, const std::string &address, int port);
        void sendRaw(const char *data, std::size_t size, const std::string &address, int port);
        std::string receiveFrom(std::string &address, int &port);
        bool isConnectionAlive();
        std::string fetchPacket();

        private:
        bool _is_sender;
        asio::ip::udp::socket _socket;
        std::queue<std::string> _received_packets;
    };
}
