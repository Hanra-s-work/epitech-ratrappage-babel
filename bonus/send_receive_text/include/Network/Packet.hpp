/*
** EPITECH PROJECT, 2024
** send_receive_text
** File description:
** Packet.hpp
*/

#pragma once

#include <vector>
#include <string>
#include <cstdint>

namespace Network
{

    // A packet that can be sent over the network
    struct Packet {
        std::vector<uint8_t> data;     // Raw data to be sent (binary)
    };
}

