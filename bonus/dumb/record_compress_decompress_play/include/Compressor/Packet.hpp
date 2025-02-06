/*
** EPITECH PROJECT, 2024
** record_compress_decompress_play
** File description:
** Packet.hpp
*/

#pragma once

#include <vector>

namespace Compressor
{
    struct Packet {
        unsigned int size = 0;
        unsigned int maxPacketSize = 4000;
        unsigned int sampleRate = 44100;
        std::vector<unsigned char> data;
    };
}
