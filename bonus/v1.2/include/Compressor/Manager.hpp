/*
** EPITECH PROJECT, 2024
** record_compress_decompress_play
** File description:
** Compressor.hpp
*/

/**
 * @file Manager.hpp
 * @brief This file contains the definition of the Manager class responsible for managing audio compression and decompression.
 */

#pragma once

#include <vector>
#include <iostream>
#include <stdexcept>
#include <mutex>
#include <array>

#include <opus.h>

#include "Logging.hpp"
#include "Audio/Sample.hpp"
#include "Compressor/Packet.hpp"

namespace Compressor
{
    /**
     * @brief Class responsible for managing audio compression and decompression.
     */
    class Manager {
        public:
        /**
         * @brief Default constructor.
         */
        Manager();

        /**
         * @brief Constructor with an uncompressed audio sample.
         * @param sample The uncompressed audio sample.
         */
        Manager(const Audio::Sample &sample);

        /**
         * @brief Destructor.
         */
        ~Manager();

        /**
         * @brief Compress the uncompressed audio stream.
         */
        void compress();

        /**
         * @brief Encode raw audio data into compressed format.
         * @param sound Vector containing the raw audio data.
         * @param output Vector to store the compressed audio data.
         */
        void encode(std::vector<float> &sound, std::vector<unsigned char> &output);

        /**
         * @brief Decode compressed audio data into raw format.
         * @param sound Vector containing the compressed audio data.
         * @param output Vector to store the raw audio data.
         */
        void decode(std::vector<unsigned char> &sound, std::vector<float> &output);

        /**
         * @brief Decompress the compressed audio stream.
         */
        void decompress();

        /**
         * @brief Set the maximum packet size for compression.
         * @param maxPacketSize The maximum packet size.
         */
        void setMaxPacketSize(const unsigned int maxPacketSize);

        /**
         * @brief Get the maximum packet size for compression.
         * @return The maximum packet size.
         */
        const unsigned int getMaxPacketSize() const;

        /**
         * @brief Set the compressed audio stream.
         * @param data The compressed audio packet.
         */
        void setCompressedStream(const Compressor::Packet &data);

        /**
         * @brief Get the compressed audio stream.
         * @return The compressed audio packet.
         */
        const Compressor::Packet &getCompressedStream() const;

        /**
         * @brief Set the uncompressed audio stream.
         * @param data The uncompressed audio sample.
         */
        void setUncompressedStream(const Audio::Sample &data);

        /**
         * @brief Get the uncompressed audio stream.
         * @return The uncompressed audio sample.
         */
        const Audio::Sample &getUncompressedStream() const;

        private:
        /**
         * @brief Handle Opus errors.
         * @param errorCode The error code returned by Opus functions.
         * @param context The context in which the error occurred.
         */
        void handleOpusError(int errorCode, const std::string &context) const;

        int _error; /**< Error code for Opus operations. */
        bool _rawStreamSet = false; /**< Flag indicating if the raw stream has been set. */
        bool _hasBeenCompressed = false; /**< Flag indicating if the stream has been compressed. */
        unsigned int _maxPacketSize = 4000; /**< Default packet size. */
        OpusEncoder *_encoder = nullptr; /**< Pointer to the Opus encoder. */
        OpusDecoder *_decoder = nullptr; /**< Pointer to the Opus decoder. */
        Audio::Sample _uncompressedStream; /**< Uncompressed audio sample. */
        Compressor::Packet _compressedStream; /**< Compressed audio packet. */
        mutable std::mutex _mutex; /**< Mutex for thread safety. */
    };
}
