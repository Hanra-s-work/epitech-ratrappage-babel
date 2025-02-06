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

#include "Network/Packet.hpp"
#include "Network/Translator.hpp"
#include "Network/AddressHolder.hpp"

namespace Network
{
    class Listener {
        public:
        Listener(const AddressHolder &addressHolder);
        ~Listener();

        void sendData(const std::vector<Packet> &data);
        const std::vector<Packet> getPackets();

        private:
        void _startAccept();
        void _initialiseAddress();
        void _startReceive();

        AddressHolder _addressHolder;
        asio::io_context _io_context;
        asio::ip::tcp::acceptor _acceptor;
        asio::ip::tcp::socket _socket;
        std::array<char, 1024> _buffer;
        Translator _translator;
        std::vector<Packet> _packets;
        std::mutex _mutex;
    };
}
