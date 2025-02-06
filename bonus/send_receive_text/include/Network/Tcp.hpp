/*
** EPITECH PROJECT, 2024
** send_receive_text
** File description:
** Listener.hpp
*/

#pragma once

#include <string>
#include <asio.hpp>
#include <iostream>
#include <vector>
#include <array>
#include <mutex>

#include "Logging.hpp"
#include "Recoded.hpp"
#include "Utilities.hpp"
#include "CustomExceptions.hpp"

#include "Network/AddressHolder.hpp"

namespace Network
{
    class Tcp {
        public:
        Tcp(const AddressHolder &addressHolder);
        ~Tcp();

        void sendData(const std::string &data);
        const std::vector<std::string> getPackets();

        const bool isConnected() const;

        private:
        void _startAccept();
        void _initialiseAddress();
        void _startReceive();

        AddressHolder _addressHolder;
        asio::io_context _ioContext;
        asio::ip::tcp::socket _socket;
        asio::ip::tcp::endpoint _endpoint;
        std::array<char, 1024> _buffer;
        std::vector<std::string> _packets;
        std::mutex _mutex;
    };
}
