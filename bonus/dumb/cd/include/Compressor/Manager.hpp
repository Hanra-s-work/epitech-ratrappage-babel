/*
** EPITECH PROJECT, 2024
** record_compress_decompress_play
** File description:
** Compressor.hpp
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
    class Manager {
        public:
        Manager();
        Manager(const Audio::Sample &sample);

        ~Manager();

        void compress();

        void encode(std::vector<float> &sound, std::vector<unsigned char> &output);

        void decode(std::vector<unsigned char> &sound, std::vector<float> &output);

        void decompress();

        void setMaxPacketSize(const unsigned int maxPacketSize);
        const unsigned int getMaxPacketSize() const;

        void setCompressedStream(const Compressor::Packet &data);
        const Compressor::Packet &getCompressedStream() const;

        void setUncompressedStream(const Audio::Sample &data);
        const Audio::Sample &getUncompressedStream() const;

        private:
        void handleOpusError(int errorCode, const std::string &context) const;

        int _error;
        bool _rawStreamSet = false;
        bool _hasBeenCompressed = false;
        unsigned int _maxPacketSize = 4000; // Default packet size
        OpusEncoder *_encoder = nullptr;
        OpusDecoder *_decoder = nullptr;
        Audio::Sample _uncompressedStream;
        Compressor::Packet _compressedStream;
        mutable std::mutex _mutex; // Mutex for thread safety
    };
}
