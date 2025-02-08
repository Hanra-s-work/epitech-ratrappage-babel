/*
** EPITECH PROJECT, 2024
** record_compress_decompress_play
** File description:
** Sample.hpp
*/

#pragma once

#include <vector>

namespace Audio
{
    struct Sample {
        bool initialised = false;
        std::vector<float> sample;
        float durationSeconds = 1;
        unsigned int sampleRate = 48000;
        // unsigned int framesPerBuffer = 256;
        unsigned int framesPerBuffer = 480;
        unsigned int numChannelsPlayback = 1;
        unsigned int numChannelsRecording = 1;
    };
}
