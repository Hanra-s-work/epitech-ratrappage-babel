/*
** EPITECH PROJECT, 2024
** epitech-ratrappage-babel (Workspace)
** File description:
** AudioManager.cpp
*/

#include "Audio/Manager.hpp"


const Audio::InputStream Audio::getDefaultInputStream()
{
    InputStream input;
    PaStreamParameters params;

    params.device = Pa_GetDefaultInputDevice();
    params.channelCount = 1;
    params.sampleFormat = paFloat32;
    params.suggestedLatency = Pa_GetDeviceInfo(params.device)->defaultLowInputLatency;
    params.hostApiSpecificStreamInfo = nullptr;

    input.device = params.device;
    input.channelCount = params.channelCount;
    input.sampleFormat = params.sampleFormat;
    input.suggestedLatency = params.suggestedLatency;
    input.hostApiSpecificStreamInfo = params.hostApiSpecificStreamInfo;

    return input;
}

const Audio::OutputStream Audio::getDefaultOutputStream()
{
    OutputStream output;
    PaStreamParameters params;

    params.device = Pa_GetDefaultOutputDevice();
    params.channelCount = 1;
    params.sampleFormat = paFloat32;
    params.suggestedLatency = Pa_GetDeviceInfo(params.device)->defaultLowOutputLatency;
    params.hostApiSpecificStreamInfo = nullptr;

    output.device = params.device;
    output.channelCount = params.channelCount;
    output.sampleFormat = params.sampleFormat;
    output.suggestedLatency = params.suggestedLatency;
    output.hostApiSpecificStreamInfo = params.hostApiSpecificStreamInfo;

    return output;
}


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

Audio::Manager::Manager(const float durationseconds, const unsigned int sampleRate, const unsigned int framesPerBuffer, const InputStream &input, const OutputStream &output)
{
    _initialisePa();
    initialiseSamplePlayingBuffer(durationseconds, sampleRate, framesPerBuffer, input, output);
    initialiseSampleRecordingBuffer(durationseconds, sampleRate, framesPerBuffer, input, output);
}

Audio::Manager::~Manager()
{
    stopRecording();
    stopPlaying();
    clearRecordingBuffer();
    clearPlayingBuffer();
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
    _sampleRecording = initialiseSampleRecordingBufferNode(sample);
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

void Audio::Manager::initialiseSampleRecordingBuffer(const float durationseconds, unsigned int sampleRate, unsigned int framesPerBuffer, const InputStream &input, const OutputStream &output)
{
    std::cout << "Initialising recording buffer..." << std::endl;
    _sampleRecording.sampleRate = sampleRate;
    _sampleRecording.framesPerBuffer = framesPerBuffer;
    _sampleRecording.channelPlaying = input;
    _sampleRecording.channelRecording = output;
    _sampleRecording.durationSeconds = durationseconds;
    _sampleRecording.sample.resize(sampleRate * durationseconds);
    _sampleRecording.initialised = true;
    std::cout << "Recording buffer initialised" << std::endl;
}

const Audio::Sample Audio::Manager::initialiseSampleRecordingBufferNode(const Sample &sample)
{
    Sample copy;
    copy = sample;
    copy.sample.resize(_sampleRecording.sampleRate * _sampleRecording.durationSeconds);
    copy.initialised = true;
    return copy;
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
    _samplePlaying = initialiseSamplePlayingBufferNode(sample);
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

void Audio::Manager::initialiseSamplePlayingBuffer(const float durationseconds, const unsigned int sampleRate, const unsigned int framesPerBuffer, const InputStream &input, const OutputStream &output)
{
    std::cout << "Initialising playing buffer..." << std::endl;
    _samplePlaying.sampleRate = sampleRate;
    _samplePlaying.framesPerBuffer = framesPerBuffer;
    _samplePlaying.channelPlaying = input;
    _samplePlaying.channelRecording = output;
    _samplePlaying.durationSeconds = durationseconds;
    _samplePlaying.sample.resize(sampleRate * durationseconds);
    _samplePlaying.initialised = true;
    std::cout << "Playing buffer initialised" << std::endl;
}

const Audio::Sample Audio::Manager::initialiseSamplePlayingBufferNode(const Sample &sample)
{
    Sample copy;
    copy = sample;
    copy.sample.resize(_samplePlaying.sampleRate * _samplePlaying.durationSeconds);
    copy.initialised = true;
    return copy;
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

void Audio::Manager::startRecording()
{
    _recording = true;
    _recordingPaused = false;
    std::cout << "Starting recording in a separate thread..." << std::endl;
    if (!_sampleRecording.initialised) {
        initialiseSampleRecordingBuffer();
    }

    // Start the recording in a separate thread
    _recordingThread = std::thread(&Audio::Manager::_continuouslyRecord, this);
}

void Audio::Manager::pauseRecording()
{
    _recordingPaused = true;
    std::cout << "Recording paused" << std::endl;
}

void Audio::Manager::resumeRecording()
{
    _recordingPaused = false;
    std::cout << "Recording resumed" << std::endl;
}

void Audio::Manager::stopRecording()
{
    _recording = false;
    _recordingPaused = false;
    if (_recordingThread.joinable())
        _recordingThread.join();
    std::cout << "Recording stopped" << std::endl;
}

void Audio::Manager::clearRecordingBuffer()
{
    {
        std::lock_guard<std::mutex> lock(_recordingMutex);
        _recordingBuffer.clear();
    }
    std::cout << "Recording buffer cleared" << std::endl;
}

void Audio::Manager::startPlaying()
{
    _playing = true;
    _playingPaused = false;
    std::cout << "Starting playback in a separate thread..." << std::endl;
    if (!_samplePlaying.initialised) {
        initialiseSamplePlayingBuffer();
    }

    // Start the playback in a separate thread
    _playingThread = std::thread(&Audio::Manager::_continuouslyPlay, this);
}

void Audio::Manager::pausePlaying()
{
    _playingPaused = true;
    std::cout << "Playback paused" << std::endl;
}

void Audio::Manager::resumePlaying()
{
    _playingPaused = false;
    _playerNotifier.notify_all();
    std::cout << "Playback resumed" << std::endl;
}

void Audio::Manager::stopPlaying()
{
    _playing = false;
    _playingPaused = false;
    if (_playingThread.joinable())
        _playingThread.join();
    std::cout << "Playback stopped" << std::endl;
}

void Audio::Manager::clearPlayingBuffer()
{
    {
        std::lock_guard<std::mutex> lock(_playingMutex);
        _playingBuffer.clear();
    }
    std::cout << "Playing buffer cleared" << std::endl;
}

void Audio::Manager::addSampleToPlayingBuffer(const Sample &sample)
{
    Sample copy = sample;
    if (!copy.initialised) {
        copy = initialiseSamplePlayingBufferNode(sample);
    }
    // Lock the mutex while modifying the playing buffer
    {
        std::lock_guard<std::mutex> lock(_playingMutex);
        _playingBuffer.push_back(copy);
    }
    _playerNotifier.notify_all();
}

const std::vector<Audio::Sample> Audio::Manager::getRecordingBuffer()
{
    std::vector<Sample> copy;

    {
        std::lock_guard<std::mutex> lock(_recordingMutex);
        copy = _recordingBuffer;
    }

    clearRecordingBuffer();
    return copy;
}

const bool Audio::Manager::isRecording() const
{
    return _recording && !_recordingPaused;
}

const bool Audio::Manager::isPlaying() const
{
    return _playing && !_playingPaused;
}

void Audio::Manager::_continuouslyRecord()
{
    while (_recording) {
        if (!_recording) {
            break;
        }
        if (_recordingPaused) {
            std::unique_lock<std::mutex> lock(_recordingMutex);
            _recorderNotifier.wait(lock, [this]() { return !_recordingPaused; });
            continue;
        }

        // Proceeding with recording
        std::optional<Sample> sample = _recordChunk();

        if (!sample.has_value()) {
            continue;
        }

        // Lock the mutex while modifying the recording buffer
        {
            std::lock_guard<std::mutex> lock(_recordingMutex);
            _recordingBuffer.push_back(sample.value());
        }
    }
}

void Audio::Manager::_continuouslyPlay()
{
    while (_playing) {
        if (!_playing) {
            break;
        }

        if (_playingPaused) {
            std::unique_lock<std::mutex> lock(_playingMutex);
            _playerNotifier.wait(lock, [this]() { return !_playingPaused; });
            continue;
        }

        // Proceeding with playing
        Sample sample;

        {
            std::unique_lock<std::mutex> lock(_playingMutex);
            _playerNotifier.wait(lock, [this]() { return !_playingBuffer.empty(); });
            if (_playingBuffer.empty()) {
                std::this_thread::sleep_for(std::chrono::milliseconds(_playPauseCheckDelay));
                continue;
            }
            sample = _playingBuffer.front();
            _playingBuffer.pop_front();
        }

        _playChunk(sample);
    };
}

const std::optional<Audio::Sample> Audio::Manager::_recordChunk()
{
    PaError err;
    PaStream *stream;
    Sample sample = initialiseSampleRecordingBufferNode(_sampleRecording);

    AStream customParams = sample.channelRecording;
    PaStreamParameters params;

    params = _toPaStreamParameters(sample.channelRecording);

    err = Pa_OpenStream(
        &stream,
        &params,                                     // Input channels
        0,                                           // No Output channels for recording
        sample.sampleRate,                           // Sample rate
        sample.framesPerBuffer,                      // Frames per buffer
        0,                                           // Pa stream flags
        nullptr,                                     // Input callback (null for simple read/write)
        nullptr                                      // User data (here is null)
    );                                               // Output callback (null for simple read/write)

    if (err != paNoError) {
        std::cerr << "PortAudio stream open error: " << Pa_GetErrorText(err) << std::endl;
        return std::nullopt;
    }

    err = Pa_StartStream(stream);
    if (err != paNoError) {
        std::cerr << "PortAudio stream start error: " << Pa_GetErrorText(err) << std::endl;
        return std::nullopt;
    }

    // Recording audio
    err = Pa_ReadStream(stream, sample.sample.data(), sample.sample.size() / customParams.channelCount);
    if (err != paNoError) {
        std::cerr << "PortAudio read stream error: " << Pa_GetErrorText(err) << std::endl;
        return std::nullopt;
    }

    err = Pa_StopStream(stream);
    if (err != paNoError) {
        std::cerr << "PortAudio stop stream error: " << Pa_GetErrorText(err) << std::endl;
    }

    err = Pa_CloseStream(stream);
    if (err != paNoError) {
        std::cerr << "PortAudio close stream error: " << Pa_GetErrorText(err) << std::endl;
    }

    std::cout << "Recording finished" << std::endl;
    return std::make_optional<Sample>(sample);
};

void Audio::Manager::_playChunk(const Sample &sample)
{
    PaError err;
    PaStream *stream;

    AStream CustomParams = sample.channelPlaying;
    PaStreamParameters params;

    params = _toPaStreamParameters(CustomParams);

    err = Pa_OpenStream(
        &stream,
        nullptr,                                   // No Input channels required
        &params,                                   // Output channels
        sample.sampleRate,                         // Sample rate
        sample.framesPerBuffer,                    // Frames per buffer
        0,                                         // Pa stream flags
        nullptr,                                   // Input callback (null for simple read/write)
        nullptr                                    // User data (here is null)
    );

    if (err != paNoError) {
        std::cerr << "PortAudio stream open error: " << Pa_GetErrorText(err) << std::endl;
        return;
    }

    err = Pa_StartStream(stream);
    if (err != paNoError) {
        std::cerr << "PortAudio stream start error: " << Pa_GetErrorText(err) << std::endl;
        return;
    }

    err = Pa_WriteStream(stream, sample.sample.data(), sample.sample.size() / CustomParams.channelCount);
    if (err != paNoError) {
        std::cerr << "PortAudio write stream error: " << Pa_GetErrorText(err) << std::endl;
        return;
    }

    err = Pa_StopStream(stream);
    if (err != paNoError) {
        std::cerr << "PortAudio stop stream error: " << Pa_GetErrorText(err) << std::endl;
    }

    err = Pa_CloseStream(stream);
    if (err != paNoError) {
        std::cerr << "PortAudio close stream error: " << Pa_GetErrorText(err) << std::endl;
    }

    std::cout << "Playback finished" << std::endl;
};

const PaStreamParameters Audio::Manager::_toPaStreamParameters(const AStream &stream) const
{
    PaStreamParameters params;

    params.device = stream.device;
    params.channelCount = stream.channelCount;
    params.sampleFormat = stream.sampleFormat;
    params.suggestedLatency = stream.suggestedLatency;
    params.hostApiSpecificStreamInfo = stream.hostApiSpecificStreamInfo;


    return params;
}

// const PaStreamParameters Audio::Manager::_toPaStreamParameters(const OutputStream &output) const
// {
//     PaStreamParameters params;

//     params.device = output.device;
//     params.channelCount = output.channelCount;
//     params.sampleFormat = output.sampleFormat;
//     params.suggestedLatency = output.suggestedLatency;
//     params.hostApiSpecificStreamInfo = output.hostApiSpecificStreamInfo;

//     return params;
// }

// const PaStreamParameters Audio::Manager::_toPaStreamParameters(const InputStream &input) const
// {
//     PaStreamParameters params;

//     params.device = input.device;
//     params.channelCount = input.channelCount;
//     params.sampleFormat = input.sampleFormat;
//     params.suggestedLatency = input.suggestedLatency;
//     params.hostApiSpecificStreamInfo = input.hostApiSpecificStreamInfo;

//     return params;
// }

const bool Audio::Manager::_initialisePa()
{
    std::cout << "Initializing PortAudio..." << std::endl;
    _playingBuffer.clear();
    _recordingBuffer.clear();
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
    _playingBuffer.clear();
    _recordingBuffer.clear();
    PaError err = Pa_Terminate();
    if (err != paNoError) {
        std::cerr << "PortAudio termination error: " << Pa_GetErrorText(err) << std::endl;
        return false;
    }
    std::cout << "PortAudio terminated" << std::endl;
    return true;
}
