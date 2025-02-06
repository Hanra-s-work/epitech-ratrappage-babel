/*
** EPITECH PROJECT, 2024
** send_receive_text
** File description:
** Translator.hpp
*/

#pragma once


#include <vector>
#include <string>
#include <asio.hpp>
#include <iostream>

#include "Logging.hpp"
#include "Recoded.hpp"
#include "Utilities.hpp"
#include "CustomExceptions.hpp"

#include "Network/Packet.hpp"

namespace Network
{
    class Translator {
        public:
        Translator();
        ~Translator();

        // Serialize the packet to a byte stream (for sending)
        std::vector<uint8_t> serialize(const Packet &packet) const;

        // Deserialize a byte stream into a Packet object (for receiving)
        Packet deserialize(const std::vector<uint8_t> &byte_stream) const;
    };
}
