/*
** EPITECH PROJECT, 2024
** epitech-ratrappage-babel (Workspace)
** File description:
** audio.cpp
*/

#include "Audio/Audio.hpp"

std::mutex _inMutex{};
std::mutex _outMutex{};

PortAudio::PortAudio()
{
    PRETTY_INFO << "Starting PortAudio" << std::endl;
    PaError err;

    err = Pa_Initialize();
    if (err != paNoError)
        throw std::runtime_error("Error PortAudio initialize!\n");
    initInputParameters();
    initOutputParameters();
    PRETTY_INFO << "PortAudio started" << std::endl;
}

PortAudio::~PortAudio()
{
    PRETTY_INFO << "Stopping PortAudio" << std::endl;
    Pa_CloseStream(_inputStream);
    Pa_CloseStream(_outputStream);
    Pa_Terminate();
    PRETTY_INFO << "PortAudio stopped" << std::endl;
}

void PortAudio::initInputParameters()
{
    PRETTY_INFO << "Initialising input parameters" << std::endl;
    PaError err;

    _inputParameters.device = Pa_GetDefaultInputDevice();
    if (_inputParameters.device == paNoDevice)
        throw std::runtime_error("Error: No default input device.\n");
    _inputParameters.channelCount = 1;
    _inputParameters.sampleFormat = paFloat32;
    _inputParameters.suggestedLatency = Pa_GetDeviceInfo(_inputParameters.device)->defaultLowInputLatency;
    _inputParameters.hostApiSpecificStreamInfo = NULL;

    err = Pa_OpenStream(
        &_inputStream,
        &_inputParameters,
        NULL,
        SAMPLE_RATE,
        FRAMES_PER_BUFFER,
        paClipOff,
        inputCallback,
        &_inputBuffer);

    if (err != paNoError)
        throw std::runtime_error("Cannot open input Stream\n");
    PRETTY_INFO << "Input parameters initialised" << std::endl;
}

void PortAudio::initOutputParameters()
{

    PRETTY_INFO << "Initialising output parameters" << std::endl;
    PaError err;

    _outputParameters.device = Pa_GetDefaultOutputDevice();
    if (_outputParameters.device == paNoDevice)
        throw std::runtime_error("Error: No default output device.\n");
    _outputParameters.channelCount = 1;
    _outputParameters.sampleFormat = paFloat32;
    _outputParameters.suggestedLatency = Pa_GetDeviceInfo(_outputParameters.device)->defaultLowOutputLatency;
    _outputParameters.hostApiSpecificStreamInfo = NULL;

    err = Pa_OpenStream(
        &_outputStream,
        NULL,
        &_outputParameters,
        SAMPLE_RATE,
        FRAMES_PER_BUFFER,
        paClipOff,
        outputCallback,
        &_outputBuffer);

    if (err != paNoError)
        throw std::runtime_error("Cannot open input Stream\n");
    PRETTY_INFO << "Output parameters initialised" << std::endl;
}

void PortAudio::play()
{
    PRETTY_INFO << "Starting play" << std::endl;
    PaError err;
    err = Pa_StartStream(_outputStream);
    if (err != paNoError) {
        throw std::runtime_error("Unable to start output stream\n");
    }
    PRETTY_INFO << "Play started" << std::endl;
}

void PortAudio::stopPlay()
{
    PRETTY_INFO << "Stopping play" << std::endl;
    PaError err = Pa_StopStream(_outputStream);
    if (err != paStreamIsStopped && err != paNoError) {
        throw std::runtime_error("Unable to stop output stream\n");
    }
    PRETTY_INFO << "Play stopped" << std::endl;
}

void PortAudio::record()
{
    PRETTY_INFO << "Starting record" << std::endl;
    PaError err;
    err = Pa_StartStream(_inputStream);
    if (err != paNoError) {
        throw std::runtime_error("Unable to start input stream\n");
    }
    PRETTY_INFO << "Record started" << std::endl;
}

void PortAudio::stopRecord()
{
    PRETTY_INFO << "Stopping record" << std::endl;
    PaError err = Pa_StopStream(_inputStream);
    if (err != paStreamIsStopped && err != paNoError) {
        throw std::runtime_error("Unable to stop input stream\n");
    }
    PRETTY_INFO << "Record stopped" << std::endl;
}

bool PortAudio::getSound(std::vector<float> &soundVector, int packetSize)
{
    PRETTY_INFO << "Getting sound" << std::endl;
    if (packetSize > (int)_inputBuffer.size())
        return false;
    _inMutex.lock();
    for (int i = 0; i != packetSize; i++) {
        soundVector.push_back(_inputBuffer[i]);
    }
    for (int i = 0; i != packetSize; i++)
        _inputBuffer.pop_front();
    _inMutex.unlock();
    PRETTY_INFO << "Sound size is " << soundVector.size() << std::endl;
    return true;
}

void PortAudio::setPlaySound(const std::vector<float> &soundVector)
{
    PRETTY_INFO << "Setting sound" << std::endl;
    _outMutex.lock();
    for (size_t i = 0; i != soundVector.size(); i++) {
        _outputBuffer.push_back(soundVector[i]);
    }
    _outMutex.unlock();
    PRETTY_INFO << "Sound set" << std::endl;
}

void PortAudio::resetBuffers()
{
    PRETTY_INFO << "Resetting buffers" << std::endl;
    _inputBuffer.clear();
    _outputBuffer.clear();
    PRETTY_INFO << "Buffers reset" << std::endl;
}
