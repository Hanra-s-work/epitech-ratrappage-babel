/*
** EPITECH PROJECT, 2024
** record_compress_decompress_play
** File description:
** Manager.cpp
*/

#include "Audio/Manager.hpp"

Audio::Manager::Manager()
{
    PRETTY_INFO << "Initialising the PortAudio manager" << std::endl;
    _initialisePa();
    PRETTY_SUCCESS << "PortAudio manager initialised" << std::endl;
}

Audio::Manager::Manager(const Audio::Sample &sample)
{
    PRETTY_INFO << "Initialising the PortAudio manager" << std::endl;
    _initialisePa();
    PRETTY_SUCCESS << "PortAudio manager initialised" << std::endl;
    PRETTY_INFO << "Initialising the player and recorder sample..." << std::endl;
    setSamplePlaying(sample);
    setSampleRecording(sample);
    PRETTY_SUCCESS << "Player and recorder sample set" << std::endl;
}

Audio::Manager::Manager(const float durationseconds, const unsigned int sampleRate, const unsigned int framesPerBuffer, const unsigned int numChannels)
{
    PRETTY_INFO << "Initialising the PortAudio manager" << std::endl;
    _initialisePa();
    PRETTY_SUCCESS << "PortAudio manager initialised" << std::endl;
    PRETTY_INFO << "Initialising the player and recorder sample..." << std::endl;
    initialiseSamplePlayingBuffer(durationseconds, sampleRate, framesPerBuffer, numChannels);
    initialiseSampleRecordingBuffer(durationseconds, sampleRate, framesPerBuffer, numChannels);
    PRETTY_SUCCESS << "Player and recorder sample set" << std::endl;
}

Audio::Manager::~Manager()
{
    PRETTY_INFO << "Destroying the PortAudio manager" << std::endl;
    _freePa();
    PRETTY_SUCCESS << "PortAudio manager destroyed" << std::endl;
}

void Audio::Manager::initialiseSampleRecordingBuffer()
{
    PRETTY_INFO << "Initialising sample buffer..." << std::endl;
    _sampleRecording.sample.resize(_sampleRecording.numChannelsRecording * _sampleRecording.sampleRate * _sampleRecording.durationSeconds);
    _sampleRecording.initialised = true;
    PRETTY_SUCCESS << "Sample buffer initialised" << std::endl;
}

void Audio::Manager::initialiseSampleRecordingBuffer(const Sample &sample)
{
    PRETTY_INFO << "Initialising recording buffer..." << std::endl;
    _sampleRecording = sample;
    _sampleRecording.sample.resize(_sampleRecording.numChannelsRecording * _sampleRecording.sampleRate * _sampleRecording.durationSeconds);
    _sampleRecording.initialised = true;
    PRETTY_SUCCESS << "Recording buffer initialised" << std::endl;
}

void Audio::Manager::initialiseSampleRecordingBuffer(const float durationseconds)
{
    PRETTY_INFO << "Initialising recording buffer..." << std::endl;
    _sampleRecording.durationSeconds = durationseconds;
    _sampleRecording.sample.resize(_sampleRecording.numChannelsRecording * _sampleRecording.sampleRate * durationseconds);
    _sampleRecording.initialised = true;
    PRETTY_SUCCESS << "Recording buffer initialised" << std::endl;
}

void Audio::Manager::initialiseSampleRecordingBuffer(const float durationseconds, unsigned int sampleRate, unsigned int framesPerBuffer, unsigned int numChannels)
{
    PRETTY_INFO << "Initialising recording buffer..." << std::endl;
    _sampleRecording.sampleRate = sampleRate;
    _sampleRecording.framesPerBuffer = framesPerBuffer;
    _sampleRecording.numChannelsPlayback = numChannels;
    _sampleRecording.numChannelsRecording = numChannels;
    _sampleRecording.durationSeconds = durationseconds;
    _sampleRecording.sample.resize(numChannels * sampleRate * durationseconds);
    _sampleRecording.initialised = true;
    PRETTY_SUCCESS << "Recording buffer initialised" << std::endl;
}

void Audio::Manager::setSampleRecording(const Sample &sample)
{
    _sampleRecording = sample;
    if (!_sampleRecording.initialised) {
        PRETTY_WARNING << "Sample not initialised, initialising..." << std::endl;
        initialiseSampleRecordingBuffer();
    }
    _initialised = true;
}

const Audio::Sample Audio::Manager::getSampleRecording() const
{
    if (!_sampleRecording.initialised) {
        PRETTY_ERROR << "Recording buffer not initialised" << std::endl;
        std::cerr << "Recording buffer not initialised" << std::endl;
        throw std::runtime_error("Recording buffer not initialised");
    }
    return _sampleRecording;
}

void Audio::Manager::initialiseSamplePlayingBuffer()
{
    PRETTY_INFO << "Initialising playing buffer..." << std::endl;
    _samplePlaying.sample.resize(_samplePlaying.numChannelsPlayback * _samplePlaying.sampleRate * _samplePlaying.durationSeconds);
    _samplePlaying.initialised = true;
    PRETTY_SUCCESS << "Playing buffer initialised" << std::endl;
}

void Audio::Manager::initialiseSamplePlayingBuffer(const Sample &sample)
{
    PRETTY_INFO << "Initialising playing buffer..." << std::endl;
    _samplePlaying = sample;
    _samplePlaying.sample.resize(_samplePlaying.numChannelsPlayback * _samplePlaying.sampleRate * _samplePlaying.durationSeconds);
    _samplePlaying.initialised = true;
    PRETTY_SUCCESS << "Playing buffer initialised" << std::endl;
}

void Audio::Manager::initialiseSamplePlayingBuffer(const float durationseconds)
{
    PRETTY_INFO << "Initialising playing buffer..." << std::endl;
    _samplePlaying.durationSeconds = durationseconds;
    _samplePlaying.sample.resize(_samplePlaying.numChannelsPlayback * _samplePlaying.sampleRate * durationseconds);
    _samplePlaying.initialised = true;
    PRETTY_SUCCESS << "Playing buffer initialised" << std::endl;
}

void Audio::Manager::initialiseSamplePlayingBuffer(const float durationseconds, unsigned int sampleRate, unsigned int framesPerBuffer, unsigned int numChannels)
{
    PRETTY_INFO << "Initialising playing buffer..." << std::endl;
    _samplePlaying.sampleRate = sampleRate;
    _samplePlaying.framesPerBuffer = framesPerBuffer;
    _samplePlaying.numChannelsPlayback = numChannels;
    _samplePlaying.numChannelsRecording = numChannels;
    _samplePlaying.durationSeconds = durationseconds;
    _samplePlaying.sample.resize(numChannels * sampleRate * durationseconds);
    _samplePlaying.initialised = true;
    PRETTY_SUCCESS << "Playing buffer initialised" << std::endl;
}

void Audio::Manager::setSamplePlaying(const Sample &sample)
{
    _samplePlaying = sample;
    if (!_samplePlaying.initialised) {
        PRETTY_WARNING << "Sample not initialised, initialising..." << std::endl;
        initialiseSamplePlayingBuffer();
    }
    _initialised = true;
}

const Audio::Sample Audio::Manager::getSamplePlaying() const
{
    if (!_samplePlaying.initialised) {
        PRETTY_ERROR << "Paying buffer not initialised" << std::endl;
        std::cerr << "Paying buffer not initialised" << std::endl;
        throw std::runtime_error("Playing buffer not initialised");
    }
    return _samplePlaying;
}

void Audio::Manager::recordSample()
{
    _recording = true;
    PRETTY_INFO << "Recording audio..." << std::endl;
    PaError err;
    PaStream *stream;

    if (!_sampleRecording.initialised) {
        PRETTY_WARNING << "Recording buffer not initialised, initialising..." << std::endl;
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
        PRETTY_ERROR << "PortAudio stream open error: " << Pa_GetErrorText(err) << std::endl;
        std::cerr << "PortAudio stream open error: " << Pa_GetErrorText(err) << std::endl;
        _recording = false;
        throw std::runtime_error("PortAudio stream open error");
    }

    // Starting the stream
    err = Pa_StartStream(stream);
    if (err != paNoError) {
        PRETTY_ERROR << "PortAudio stream start error: " << Pa_GetErrorText(err) << std::endl;
        std::cerr << "PortAudio stream start error: " << Pa_GetErrorText(err) << std::endl;
        _recording = false;
        throw std::runtime_error("PortAudio stream start error");
    }

    PRETTY_INFO << "Recording for " << _sampleRecording.durationSeconds << " seconds..." << std::endl;

    // Recording audio
    err = Pa_ReadStream(stream, _sampleRecording.sample.data(), _sampleRecording.sample.size() / _sampleRecording.numChannelsRecording);
    if (err != paNoError) {
        PRETTY_ERROR << "PortAudio read stream error: " << Pa_GetErrorText(err) << std::endl;
        std::cerr << "PortAudio read stream error: " << Pa_GetErrorText(err) << std::endl;
        _recording = false;
        throw std::runtime_error("PortAudio read stream error");
    }

    // Stoping the stream
    err = Pa_StopStream(stream);
    if (err != paNoError) {
        PRETTY_ERROR << "PortAudio stop stream error: " << Pa_GetErrorText(err) << std::endl;
        std::cerr << "PortAudio stop stream error: " << Pa_GetErrorText(err) << std::endl;
    }

    // Closing the stream
    err = Pa_CloseStream(stream);
    if (err != paNoError) {
        PRETTY_ERROR << "PortAudio close stream error: " << Pa_GetErrorText(err) << std::endl;
        std::cerr << "PortAudio close stream error: " << Pa_GetErrorText(err) << std::endl;
    }

    PRETTY_SUCCESS << "Audio recorded" << std::endl;
    _recording = false;
}

void Audio::Manager::playSample()
{
    _playing = true;
    PRETTY_INFO << "Playing audio..." << std::endl;
    PaError err;
    PaStream *stream;

    if (!_samplePlaying.initialised) {
        PRETTY_WARNING << "Playing buffer not initialised, initialising..." << std::endl;
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
        PRETTY_ERROR << "PortAudio stream open error: " << Pa_GetErrorText(err) << std::endl;
        std::cerr << "PortAudio stream open error: " << Pa_GetErrorText(err) << std::endl;
        _playing = false;
        throw std::runtime_error("PortAudio stream open error");
    }

    err = Pa_StartStream(stream);
    if (err != paNoError) {
        PRETTY_ERROR << "PortAudio stream start error: " << Pa_GetErrorText(err) << std::endl;
        std::cerr << "PortAudio stream start error: " << Pa_GetErrorText(err) << std::endl;
        _playing = false;
        throw std::runtime_error("PortAudio stream start error");
    }

    err = Pa_WriteStream(stream, _samplePlaying.sample.data(), _samplePlaying.sample.size() / _samplePlaying.numChannelsPlayback);
    if (err != paNoError) {
        PRETTY_ERROR << "PortAudio write stream error: " << Pa_GetErrorText(err) << std::endl;
        std::cerr << "PortAudio write stream error: " << Pa_GetErrorText(err) << std::endl;
        _playing = false;
        throw std::runtime_error("PortAudio write stream error");
    }

    // Stoping the stream
    err = Pa_StopStream(stream);
    if (err != paNoError) {
        PRETTY_ERROR << "PortAudio stop stream error: " << Pa_GetErrorText(err) << std::endl;
        std::cerr << "PortAudio stop stream error: " << Pa_GetErrorText(err) << std::endl;
    }

    // Closing the stream
    err = Pa_CloseStream(stream);
    if (err != paNoError) {
        PRETTY_ERROR << "PortAudio close stream error: " << Pa_GetErrorText(err) << std::endl;
        std::cerr << "PortAudio close stream error: " << Pa_GetErrorText(err) << std::endl;
    }
    PRETTY_SUCCESS << "Audio played" << std::endl;
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
    PRETTY_INFO << "Initializing PortAudio..." << std::endl;
    PaError err = Pa_Initialize();
    if (err != paNoError) {
        PRECISE_ERROR << "PortAudio initialization error: " << Pa_GetErrorText(err) << std::endl;
        std::cerr << "PortAudio initialization error: " << Pa_GetErrorText(err) << std::endl;
        return false;
    }
    PRETTY_SUCCESS << "PortAudio initialized" << std::endl;
    return true;
}

const bool Audio::Manager::_freePa()
{
    PRETTY_INFO << "Terminating PortAudio..." << std::endl;
    PaError err = Pa_Terminate();
    if (err != paNoError) {
        PRECISE_ERROR << "PortAudio termination error: " << Pa_GetErrorText(err) << std::endl;
        std::cerr << "PortAudio termination error: " << Pa_GetErrorText(err) << std::endl;
        return false;
    }
    PRETTY_SUCCESS << "PortAudio terminated" << std::endl;
    return true;
}
