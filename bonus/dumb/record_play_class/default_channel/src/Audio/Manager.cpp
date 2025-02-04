/*
** EPITECH PROJECT, 2024
** epitech-ratrappage-babel (Workspace)
** File description:
** AudioManager.cpp
*/

#include "Audio/Manager.hpp"

Audio::Manager::Manager()
{
    _initialisePa();
}

Audio::Manager::Manager(const Audio::Sample &sample)
{
    _initialisePa();
    setSamplePlaying(sample);
    setSampleRecording(sample);
}

Audio::Manager::Manager(const float durationseconds, const unsigned int sampleRate, const unsigned int framesPerBuffer, const unsigned int numChannels)
{
    _initialisePa();
    initialiseSamplePlayingBuffer(durationseconds, sampleRate, framesPerBuffer, numChannels);
    initialiseSampleRecordingBuffer(durationseconds, sampleRate, framesPerBuffer, numChannels);
}

Audio::Manager::~Manager()
{
    _freePa();
}

void Audio::Manager::initialiseSampleRecordingBuffer()
{
    std::cout << "Initialising sample buffer..." << std::endl;
    _sampleRecording.sample.resize(_sampleRecording.sampleRate * _sampleRecording.durationSeconds);
    _sampleRecording.initialised = true;
    std::cout << "Sample buffer initialised" << std::endl;
}

void Audio::Manager::initialiseSampleRecordingBuffer(const Sample &sample)
{
    std::cout << "Initialising recording buffer..." << std::endl;
    _sampleRecording = sample;
    _sampleRecording.sample.resize(_sampleRecording.sampleRate * _sampleRecording.durationSeconds);
    _sampleRecording.initialised = true;
    std::cout << "Recording buffer initialised" << std::endl;
}

void Audio::Manager::initialiseSampleRecordingBuffer(const float durationseconds)
{
    std::cout << "Initialising recording buffer..." << std::endl;
    _sampleRecording.durationSeconds = durationseconds;
    _sampleRecording.sample.resize(_sampleRecording.sampleRate * durationseconds);
    _sampleRecording.initialised = true;
    std::cout << "Recording buffer initialised" << std::endl;
}

void Audio::Manager::initialiseSampleRecordingBuffer(const float durationseconds, unsigned int sampleRate, unsigned int framesPerBuffer, unsigned int numChannels)
{
    std::cout << "Initialising recording buffer..." << std::endl;
    _sampleRecording.sampleRate = sampleRate;
    _sampleRecording.framesPerBuffer = framesPerBuffer;
    _sampleRecording.numChannelsPlayback = numChannels;
    _sampleRecording.numChannelsRecording = numChannels;
    _sampleRecording.durationSeconds = durationseconds;
    _sampleRecording.sample.resize(sampleRate * durationseconds);
    _sampleRecording.initialised = true;
    std::cout << "Recording buffer initialised" << std::endl;
}

void Audio::Manager::setSampleRecording(const Sample &sample)
{
    _sampleRecording = sample;
    if (!_sampleRecording.initialised) {
        std::cerr << "Sample not initialised" << std::endl;
        initialiseSampleRecordingBuffer();
    }
    _initialised = true;
}

const Audio::Sample Audio::Manager::getSampleRecording() const
{
    if (!_sampleRecording.initialised) {
        std::cerr << "Recording buffer not initialised" << std::endl;
        throw std::runtime_error("Recording buffer not initialised");
    }
    return _sampleRecording;
}

void Audio::Manager::initialiseSamplePlayingBuffer()
{
    std::cout << "Initialising playing buffer..." << std::endl;
    _samplePlaying.sample.resize(_samplePlaying.sampleRate * _samplePlaying.durationSeconds);
    _samplePlaying.initialised = true;
    std::cout << "Playing buffer initialised" << std::endl;
}

void Audio::Manager::initialiseSamplePlayingBuffer(const Sample &sample)
{
    std::cout << "Initialising playing buffer..." << std::endl;
    _samplePlaying = sample;
    _samplePlaying.sample.resize(_samplePlaying.sampleRate * _samplePlaying.durationSeconds);
    _samplePlaying.initialised = true;
    std::cout << "Playing buffer initialised" << std::endl;
}

void Audio::Manager::initialiseSamplePlayingBuffer(const float durationseconds)
{
    std::cout << "Initialising playing buffer..." << std::endl;
    _samplePlaying.durationSeconds = durationseconds;
    _samplePlaying.sample.resize(_samplePlaying.sampleRate * durationseconds);
    _samplePlaying.initialised = true;
    std::cout << "Playing buffer initialised" << std::endl;
}

void Audio::Manager::initialiseSamplePlayingBuffer(const float durationseconds, unsigned int sampleRate, unsigned int framesPerBuffer, unsigned int numChannels)
{
    std::cout << "Initialising playing buffer..." << std::endl;
    _samplePlaying.sampleRate = sampleRate;
    _samplePlaying.framesPerBuffer = framesPerBuffer;
    _samplePlaying.numChannelsPlayback = numChannels;
    _samplePlaying.numChannelsRecording = numChannels;
    _samplePlaying.durationSeconds = durationseconds;
    _samplePlaying.sample.resize(sampleRate * durationseconds);
    _samplePlaying.initialised = true;
    std::cout << "Playing buffer initialised" << std::endl;
}

void Audio::Manager::setSamplePlaying(const Sample &sample)
{
    _samplePlaying = sample;
    if (!_samplePlaying.initialised) {
        std::cerr << "Sample not initialised" << std::endl;
        initialiseSamplePlayingBuffer();
    }
    _initialised = true;
}

const Audio::Sample Audio::Manager::getSamplePlaying() const
{
    if (!_samplePlaying.initialised) {
        std::cerr << "Paying buffer not initialised" << std::endl;
        throw std::runtime_error("Playing buffer not initialised");
    }
    return _samplePlaying;
}

void Audio::Manager::recordSample()
{
    _recording = true;
    std::cout << "Recording audio..." << std::endl;
    PaError err;
    PaStream *stream;

    if (!_sampleRecording.initialised) {
        initialiseSampleRecordingBuffer();
    }

    err = Pa_OpenDefaultStream(
        &stream,
        _sampleRecording.numChannelsRecording,       // Input channels
        0,                                           // No Output channels for recording
        paFloat32,                                   // Sample format
        _sampleRecording.sampleRate,                 // Sample rate
        _sampleRecording.framesPerBuffer,            // Frames per buffer
        nullptr,                                     // Input callback (null for simple read/write)
        nullptr                                      // User data (here is null)
    );                                               // Output callback (null for simple read/write)

    if (err != paNoError) {
        std::cerr << "PortAudio stream open error: " << Pa_GetErrorText(err) << std::endl;
        _recording = false;
        throw std::runtime_error("PortAudio stream open error");
    }

    // Starting the stream
    err = Pa_StartStream(stream);
    if (err != paNoError) {
        std::cerr << "PortAudio stream start error: " << Pa_GetErrorText(err) << std::endl;
        _recording = false;
        throw std::runtime_error("PortAudio stream start error");
    }

    std::cout << "Recording for " << _sampleRecording.durationSeconds << " seconds..." << std::endl;

    // Recording audio
    err = Pa_ReadStream(stream, _sampleRecording.sample.data(), _sampleRecording.sample.size() / _sampleRecording.numChannelsRecording);
    if (err != paNoError) {
        std::cerr << "PortAudio read stream error: " << Pa_GetErrorText(err) << std::endl;
        _recording = false;
        throw std::runtime_error("PortAudio read stream error");
    }

    // Stoping the stream
    err = Pa_StopStream(stream);
    if (err != paNoError) {
        std::cerr << "PortAudio stop stream error: " << Pa_GetErrorText(err) << std::endl;
    }

    // Closing the stream
    err = Pa_CloseStream(stream);
    if (err != paNoError) {
        std::cerr << "PortAudio close stream error: " << Pa_GetErrorText(err) << std::endl;
    }

    std::cout << "Audio recorded" << std::endl;
    _recording = false;
}

void Audio::Manager::playSample()
{
    _playing = true;
    std::cout << "Playing audio..." << std::endl;
    PaError err;
    PaStream *stream;

    if (!_samplePlaying.initialised) {
        initialiseSamplePlayingBuffer();
    }

    err = Pa_OpenDefaultStream(
        &stream,
        0,                                         // No Input channels required
        _samplePlaying.numChannelsRecording,       // Output channels
        paFloat32,                                 // Sample format
        _samplePlaying.sampleRate,                 // Sample rate
        _samplePlaying.framesPerBuffer,            // Frames per buffer
        nullptr,                                   // Input callback (null for simple read/write)
        nullptr                                    // User data (here is null)
    );                                             // Output callback (null for simple read/write)

    if (err != paNoError) {
        std::cerr << "PortAudio stream open error: " << Pa_GetErrorText(err) << std::endl;
        _playing = false;
        throw std::runtime_error("PortAudio stream open error");
    }

    err = Pa_StartStream(stream);
    if (err != paNoError) {
        std::cerr << "PortAudio stream start error: " << Pa_GetErrorText(err) << std::endl;
        _playing = false;
        throw std::runtime_error("PortAudio stream start error");
    }

    err = Pa_WriteStream(stream, _samplePlaying.sample.data(), _samplePlaying.sample.size() / _samplePlaying.numChannelsPlayback);
    if (err != paNoError) {
        std::cerr << "PortAudio write stream error: " << Pa_GetErrorText(err) << std::endl;
        _playing = false;
        throw std::runtime_error("PortAudio write stream error");
    }

    // Stoping the stream
    err = Pa_StopStream(stream);
    if (err != paNoError) {
        std::cerr << "PortAudio stop stream error: " << Pa_GetErrorText(err) << std::endl;
    }

    // Closing the stream
    err = Pa_CloseStream(stream);
    if (err != paNoError) {
        std::cerr << "PortAudio close stream error: " << Pa_GetErrorText(err) << std::endl;
    }
    std::cout << "Audio played" << std::endl;
    _playing = false;
}

const bool Audio::Manager::isRecording() const
{
    return _recording;
}

const bool Audio::Manager::isPlaying() const
{
    return _playing;
}

const bool Audio::Manager::_initialisePa()
{
    std::cout << "Initializing PortAudio..." << std::endl;
    PaError err = Pa_Initialize();
    if (err != paNoError) {
        std::cerr << "PortAudio initialization error: " << Pa_GetErrorText(err) << std::endl;
        return false;
    }
    std::cout << "PortAudio initialized" << std::endl;
    return true;
}

const bool Audio::Manager::_freePa()
{
    std::cout << "Terminating PortAudio..." << std::endl;
    PaError err = Pa_Terminate();
    if (err != paNoError) {
        std::cerr << "PortAudio termination error: " << Pa_GetErrorText(err) << std::endl;
        return false;
    }
    std::cout << "PortAudio terminated" << std::endl;
    return true;
}
