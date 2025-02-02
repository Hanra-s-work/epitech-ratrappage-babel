/*
** EPITECH PROJECT, 2024
** record_play
** File description:
** Player.cpp
*/

#include "Audio/Player.hpp"

Audio::Player::Player()
    : _playing(false)
{
    _initializeRecordedSamples();
}

Audio::Player::Player(const Player &copy)
    : _playing(false)
{
    update(copy);
}

Audio::Player::Player(const StreamData &data)
    : _playing(false)
{
    update(data);
}

Audio::Player::~Player()
{
    _destroyRecordedSamples();
    _destroyNodePlaybackStream();
    if (_playbackThread.joinable()) {
        _playbackThread.join();  // Ensure thread is joined before destruction
    }
}

/**
 * @brief Sets the recorded audio samples.
 * @param samples A vector containing the recorded audio samples.
 */
void Audio::Player::setRecordedSamples(const std::vector<float> &samples)
{
    _recordedData.samples = samples;
}

/**
 * @brief Sets the recorded audio samples from StreamData.
 * @param data The StreamData containing the recorded audio samples.
 */
void Audio::Player::setRecordedSamples(const StreamData &data)
{
    _recordedData = data;
}

/**
 * @brief Sets the duration of the recording.
 * @param duration The duration of the recording in seconds.
 */
void Audio::Player::setDuration(const unsigned int duration)
{
    _recordedData.duration = duration;
}

/**
 * @brief Starts the playback process.
 * @throws CustomExceptions::NoAudioStream if no audio stream is available.
 * @throws CustomExceptions::InvalidOperation if playback is already in progress.
 */
void Audio::Player::startPlaying()
{
    if (_playing) {
        PRETTY_CRITICAL << "Playback is already in progress." << std::endl;
        throw CustomExceptions::InvalidOperation("Playback is already in progress.");
    }

    try {
        _destroyNodePlaybackStream();
    }
    catch (const CustomExceptions::NoAudioStream &e) {
        COLOUR_INFO << "Playback destruction attempt: " << std::string(e.what()) << std::endl;
    }

    _initializeNodePlaybackStream();
    _playing = true;

    // Start playback in a separate thread
    _playbackThread = std::thread(&Audio::Player::_startPlaying, this);
}

/**
 * @brief Stops the playback process.
 * @throws CustomExceptions::InvalidOperation if playback is not in progress.
 */
void Audio::Player::stopPlaying()
{
    if (!_playing) {
        PRETTY_CRITICAL << "Playback is not in progress." << std::endl;
        throw CustomExceptions::InvalidOperation("Playback is not in progress.");
    }

    _playing = false;
    try {
        _destroyNodePlaybackStream();
    }
    catch (const CustomExceptions::NoAudioStream &e) {
        COLOUR_INFO << "Playback destruction attempt: " << std::string(e.what()) << std::endl;
    }

    // Wait for the playback thread to finish before returning
    if (_playbackThread.joinable()) {
        _playbackThread.join();
    }
}

/**
 * @brief Checks if playback is in progress.
 * @return True if playback is in progress, false otherwise.
 */
const bool Audio::Player::isPlaying() const
{
    return _playing;
}

/**
 * @brief Gets the duration of the recording.
 * @return The duration of the recording in seconds.
 */
const unsigned int Audio::Player::getDuration() const
{
    return _recordedData.duration;
}

/**
 * @brief Retrieves the recorded audio samples.
 * @return A vector containing the recorded audio samples.
 */
const std::vector<float> Audio::Player::getRecordedSamples() const
{
    return _recordedData.samples;
}

/**
 * @brief Retrieves the recorded audio data.
 * @return A StreamData object containing the recorded audio data.
 */
const Audio::StreamData Audio::Player::getRecordedData() const
{
    return _recordedData;
}

/**
 * @brief Dumps the current state of the variables for debugging purposes.
 * @param indent The level to which the class should be indented in the dump.
 * @return The formatted output.
 */
const std::string Audio::Player::getInfo(const unsigned int indent) const
{
    std::string indentation(indent, '\t');
    std::string result = indentation + "Audio Player:\n";
    result += indentation + "- Playing: '" + Recoded::myToString(_playing) + "'\n";
    result += indentation + "- Duration: '" + Recoded::myToString(_recordedData.duration) + "'\n";
    result += indentation + "- Samples: {\n" + Recoded::myToString(_recordedData.samples, indent + 1) + indentation + "}\n";
    return result;
}

/**
 * @brief Updates the Player by copying another Audio::Player.
 * @param copy The Audio::Player to copy data from.
 */
void Audio::Player::update(const Audio::Player &copy)
{
    _playing = copy.isPlaying();
    setRecordedSamples(copy.getRecordedSamples());
}

/**
 * @brief Updates the Player by copying another Audio::StreamData.
 * @param copy The Audio::StreamData to copy data from.
 */
void Audio::Player::update(const Audio::StreamData &copy)
{
    _recordedData = copy;
}

/**
 * @brief Overloads the assignment operator to copy from another Audio::Player.
 * @param copy The Audio::Player to copy data from.
 * @return A reference to the updated instance.
 */
Audio::Player &Audio::Player::operator =(const Audio::Player &copy)
{
    update(copy);
    return *this;
}

/**
 * @brief Initializes the recorded samples buffer.
 */
void Audio::Player::_initializeRecordedSamples()
{
    _recordedData.samples = std::vector<float>(_recordedData.duration * AUDIO_SAMPLE_RATE);
}

/**
 * @brief Initializes the audio stream for playback.
 * @throws CustomExceptions::NoAudioStream if there is an error initializing the audio stream.
 */
void Audio::Player::_initializeNodePlaybackStream()
{
    _paPlayErr = Pa_Initialize();
    if (_paPlayErr != paNoError) {
        std::string errMsg = "PortAudio initialization error: " + std::string(Pa_GetErrorText(_paPlayErr));
        COLOUR_ERROR << errMsg << std::endl;
        throw CustomExceptions::NoAudioStream(errMsg);
    }

    PaStream *stream;
    _paRawStream = stream;

    _initializeRecordedSamples();

    _paPlayErr = Pa_OpenDefaultStream(
        &_paRawStream,
        AUDIO_NUM_CHANNELS,
        AUDIO_NUM_CHANNELS,
        paFloat32,
        AUDIO_SAMPLE_RATE,
        AUDIO_FRAMES_PER_BUFFER,
        nullptr,
        nullptr
    );

    if (_paPlayErr != paNoError) {
        std::string errMsg = "PortAudio stream open error: " + std::string(Pa_GetErrorText(_paPlayErr));
        COLOUR_ERROR << errMsg << std::endl;
        Pa_Terminate();
        throw CustomExceptions::NoAudioStream(errMsg);
    }
}

/**
 * @brief Starts the playback process.
 * @throws CustomExceptions::NoAudioStream if there is an error starting the audio stream.
 */
void Audio::Player::_startPlaying()
{
    _paPlayErr = Pa_StartStream(_paRawStream);
    if (_paPlayErr != paNoError) {
        std::string errMsg = "PortAudio start stream error: " + std::string(Pa_GetErrorText(_paPlayErr));
        COLOUR_ERROR << errMsg << std::endl;
        Pa_Terminate();
        throw CustomExceptions::NoAudioStream(errMsg);
    }

    COLOUR_INFO << "Playing recorded audio..." << std::endl;

    _paPlayErr = Pa_WriteStream(_paRawStream, _recordedData.samples.data(), _recordedData.samples.size());
    if (_paPlayErr != paNoError) {
        std::string errMsg = "PortAudio write stream error: " + std::string(Pa_GetErrorText(_paPlayErr));
        COLOUR_ERROR << errMsg << std::endl;
        Pa_Terminate();
        throw CustomExceptions::NoAudioStream(errMsg);
    }

    // Signal playback is complete (you can handle completion status here)
    COLOUR_INFO << "Playback complete." << std::endl;
}

/**
 * @brief Destroys the playback stream.
 * @throws CustomExceptions::NoAudioStream if there is an error stopping or closing the audio stream.
 */
void Audio::Player::_destroyNodePlaybackStream()
{
    if (_paRawStream) {
        _paPlayErr = Pa_StopStream(_paRawStream);
        if (_paPlayErr != paNoError) {
            COLOUR_ERROR << "PortAudio stop stream error: " << Pa_GetErrorText(_paPlayErr) << std::endl;
        }
        _paPlayErr = Pa_CloseStream(_paRawStream);
        if (_paPlayErr != paNoError) {
            COLOUR_ERROR << "PortAudio close stream error: " << Pa_GetErrorText(_paPlayErr) << std::endl;
        }
        _paRawStream = nullptr;
    }
    _destroyRecordedSamples();
}

/**
 * @brief Clears the recorded samples buffer.
 */
void Audio::Player::_destroyRecordedSamples()
{
    _recordedData.samples.clear();
}

/**
 * @brief Overloads the stream insertion operator for Audio::Player.
 * @param os The output stream.
 * @param player The Audio::Player instance.
 * @return The output stream.
 */
std::ostream &Audio::operator<<(std::ostream &os, const Audio::Player &player)
{
    os << player.getInfo();
    return os;
}
