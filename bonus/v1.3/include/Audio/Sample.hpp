/*
** EPITECH PROJECT, 2024
** record_compress_decompress_play
** File description:
** Sample.hpp
*/

/**
 * @file Sample.hpp
 * @brief Defines the structure representing an audio sample.
 */

#pragma once

#include <vector>

namespace Audio
{
    /**
     * @brief Structure representing an audio sample.
     */
    struct Sample {
        bool initialised = false; ///< Indicates if the sample is initialised.
        std::vector<float> sample; ///< Vector containing the audio sample data.
        float durationSeconds = 1; ///< Duration of the sample in seconds.
        unsigned int sampleRate = 48000; ///< Sample rate of the audio in Hz.
        unsigned int framesPerBuffer = 480; ///< Number of frames per buffer.
        unsigned int numChannelsPlayback = 1; ///< Number of playback channels.
        unsigned int numChannelsRecording = 1; ///< Number of recording channels.
    };
}
