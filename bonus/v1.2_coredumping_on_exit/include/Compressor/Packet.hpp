/*
** EPITECH PROJECT, 2024
** record_compress_decompress_play
** File description:
** Packet.hpp
*/

/**
 * @file Packet.hpp
 * @brief This file contains the definition of the Packet structure used for storing compressed audio data.
 */

#pragma once

#include <vector>

namespace Compressor
{
    /**
     * @brief Structure representing a packet of compressed audio data.
     */
    struct Packet {
        unsigned int size = 0; /**< Size of the packet data. */
        unsigned int maxPacketSize = 4000; /**< Maximum allowed packet size. */
        unsigned int sampleRate = 44100; /**< Sample rate of the audio data. */
        std::vector<unsigned char> data; /**< Vector containing the compressed audio data. */
    };
}
