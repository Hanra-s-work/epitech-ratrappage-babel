/*
** EPITECH PROJECT, 2024
** epitech-ratrappage-babel (Workspace)
** File description:
** audio.hpp
*/

/**
 * @file Audio.hpp
 * @brief Declares the PortAudio class for handling audio playback and recording using PortAudio.
 */

#pragma once
#include <deque>
#include <mutex>
#include <vector>
#include <iostream>
#include <exception>
#include <portaudio.h>
#include "Logging.hpp"
#include "Constants.hpp"

extern std::mutex _inMutex;
extern std::mutex _outMutex;

/**
 * @brief Class for handling audio playback and recording using PortAudio.
 */
class PortAudio {
    public:
    /**
     * @brief Construct a new PortAudio object.
     */
    PortAudio();

    /**
     * @brief Destroy the PortAudio object.
     */
    ~PortAudio();

    /**
     * @brief Start audio playback.
     */
    void play();

    /**
     * @brief Stop audio playback.
     */
    void stopPlay();

    /**
     * @brief Start audio recording.
     */
    void record();

    /**
     * @brief Stop audio recording.
     */
    void stopRecord();

    /**
     * @brief Get recorded sound data.
     *
     * @param soundVector Vector to store the sound data.
     * @param packetSize Size of the packet to retrieve.
     * @return true if sound data was retrieved successfully.
     * @return false otherwise.
     */
    bool getSound(std::vector<float> &soundVector, int packetSize);

    /**
     * @brief Set the sound data to be played.
     *
     * @param soundVector Vector containing the sound data.
     */
    void setPlaySound(const std::vector<float> &soundVector);

    /**
     * @brief Reset the input and output buffers.
     */
    void resetBuffers();

    private:
    PaStream *_inputStream; ///< Input stream for recording.
    PaStream *_outputStream; ///< Output stream for playback.
    PaStreamParameters _inputParameters; ///< Parameters for the input stream.
    PaStreamParameters _outputParameters; ///< Parameters for the output stream.
    std::deque<float> _inputBuffer; ///< Buffer for storing input data.
    std::deque<float> _outputBuffer; ///< Buffer for storing output data.

    /**
     * @brief Initialize the input stream parameters.
     */
    void initInputParameters();

    /**
     * @brief Initialize the output stream parameters.
     */
    void initOutputParameters();

    /**
     * @brief Callback function for handling input stream data.
     *
     * @param inputBuffer Pointer to the input buffer.
     * @param outputBuffer Pointer to the output buffer.
     * @param framesPerBuffer Number of frames per buffer.
     * @param timeInfo Pointer to the time information.
     * @param statusFlags Status flags.
     * @param userData Pointer to user data.
     * @return int Status code.
     */
    static int inputCallback(const void *inputBuffer, void *outputBuffer,
        unsigned long framesPerBuffer,
        const PaStreamCallbackTimeInfo *timeInfo,
        PaStreamCallbackFlags statusFlags,
        void *userData)
    {
        (void)outputBuffer;
        (void)timeInfo;
        (void)statusFlags;
        (void)userData;

        try {
            _inMutex.lock();
            std::deque<float> *inputData = static_cast<std::deque<float> *>(userData);

            float *input = (float *)inputBuffer;

            for (unsigned long i = 0; i < framesPerBuffer; i++) {
                inputData->push_back(*input++);
            }
            _inMutex.unlock();
            return paContinue;
        }
        catch (std::exception &e) {
            throw e;
        }
    };

    /**
     * @brief Callback function for handling output stream data.
     *
     * @param inputBuffer Pointer to the input buffer.
     * @param outputBuffer Pointer to the output buffer.
     * @param framesPerBuffer Number of frames per buffer.
     * @param timeInfo Pointer to the time information.
     * @param statusFlags Status flags.
     * @param userData Pointer to user data.
     * @return int Status code.
     */
    static int outputCallback(const void *inputBuffer, void *outputBuffer,
        unsigned long framesPerBuffer,
        const PaStreamCallbackTimeInfo *timeInfo,
        PaStreamCallbackFlags statusFlags,
        void *userData)
    {
        (void)inputBuffer;
        (void)timeInfo;
        (void)statusFlags;
        (void)userData;
        unsigned long i = 0;

        try {
            float *output = (float *)outputBuffer;
            std::deque<float> *outputData = static_cast<std::deque<float> *>(userData);

            if (outputData->empty())
                return paContinue;
            _outMutex.lock();
            for (; i < framesPerBuffer; i++) {
                if (outputData->empty())
                    break;
                *output++ = (*outputData)[i];
            }
            for (unsigned long j = 0; j != i; j++) {
                outputData->pop_front();
            }
            _outMutex.unlock();
            return paContinue;
        }
        catch (std::exception &e) {
            throw std::runtime_error(e.what());
        }
    };
};
