/*
** EPITECH PROJECT, 2024
** epitech-ratrappage-babel (Workspace)
** File description:
** audio.hpp
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

class PortAudio {
    public:
    PortAudio();
    ~PortAudio();
    void play();
    void stopPlay();
    void record();
    void stopRecord();
    bool getSound(std::vector<float> &soundVector, int packetSize);
    void setPlaySound(const std::vector<float> &soundVector);
    void resetBuffers();

    private:

    PaStream *_inputStream;
    PaStream *_outputStream;
    PaStreamParameters _inputParameters;
    PaStreamParameters _outputParameters;
    std::deque<float> _inputBuffer;
    std::deque<float> _outputBuffer;

    void initInputParameters();
    void initOutputParameters();

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
