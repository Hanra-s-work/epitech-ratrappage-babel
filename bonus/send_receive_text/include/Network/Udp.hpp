/*
** EPITECH PROJECT, 2024
** send_receive_text
** File description:
** Sender.hpp
*/

#pragma once

#include <asio.hpp>
#include <iostream>

#include "Logging.hpp"
#include "Recoded.hpp"
#include "Utilities.hpp"
#include "CustomExceptions.hpp"


#include "Network/Packet.hpp"
#include "Network/Translator.hpp"
#include "Network/AddressHolder.hpp"

namespace Network
{
    class Udp {
        public:
        Udp(const AddressHolder &addressHolder);
        ~Udp();

        void send(const Packet &data);
        const std::vector<Packet> getReceivedData();

        private:
        void _startConnect();
        void _initialiseAddress();
        void _startSend();
        void _startReceive(); // New function declaration

        AddressHolder _addressHolder;
        asio::io_context _io_context;
        asio::ip::tcp::acceptor _acceptor;
        asio::ip::tcp::socket _socket;
        std::vector<Packet> _packets;
        std::mutex _mutex;
    };
}
