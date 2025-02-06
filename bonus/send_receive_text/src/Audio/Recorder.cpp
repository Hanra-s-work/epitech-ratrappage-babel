/*
** EPITECH PROJECT, 2024
** record_play
** File description:
** Recorder.cpp
*/

#include "Audio/Recorder.hpp"

Audio::Recorder::Recorder()
    : _recording(false), _paRawStream(nullptr)
{
    setDuration(MIN_RECORDING_LENGTH);
    _initializeRecordedSamples();
}

Audio::Recorder::Recorder(const Recorder &copy)
    : _recording(false), _paRawStream(nullptr)
{
    update(copy);
}

Audio::Recorder::Recorder(const StreamData &data)
    : _recording(false), _paRawStream(nullptr)
{
    update(data);
}

Audio::Recorder::Recorder(const unsigned int duration)
    : _recording(false), _paRawStream(nullptr)
{
    setDuration(duration);
    _initializeRecordedSamples();
}

Audio::Recorder::~Recorder()
{
    stopRecording();
    if (_recordingThread.joinable())
        _recordingThread.join();

    _destroyRecordedSamples();
    _destroyRecordingStream();
}

/**
 * @brief Sets the duration of the recording.
 * @param duration The length of the recording in seconds.
 * @throws CustomExceptions::InvalidDuration if the duration is not within the valid range.
 */
void Audio::Recorder::setDuration(const unsigned int duration)
{
    if (duration < MIN_RECORDING_LENGTH || duration > MAX_RECORDING_LENGTH) {
        PRETTY_CRITICAL << "The duration should be between :" << Recoded::myToString(MIN_RECORDING_LENGTH) << " and " << Recoded::myToString(MAX_RECORDING_LENGTH) << ", but was of length: " << Recoded::myToString(duration) << std::endl;
        throw CustomExceptions::InvalidDuration(
            Recoded::myToString(duration),
            Recoded::myToString(MIN_RECORDING_LENGTH),
            Recoded::myToString(MAX_RECORDING_LENGTH));
    }
    _recordedData.duration = duration;
    _initializeRecordedSamples();
}

/**
 * @brief Sets the recorded audio samples.
 * @param samples A vector containing the recorded audio samples.
 */
void Audio::Recorder::setRecordedSamples(const std::vector<float> &samples)
{
    _recordedData.samples = samples;
}

/**
 * @brief Sets the recorded audio samples from StreamData.
 * @param data The StreamData containing the recorded audio samples.
 */
void Audio::Recorder::setRecordedSamples(const StreamData &data)
{
    _recordedData = data;
}

/**
 * @brief Starts the recording process.
 * @throws CustomExceptions::NoAudioStream if no audio stream is available.
 * @throws CustomExceptions::InvalidOperation if recording is already in progress.
 */
void Audio::Recorder::startRecording()
{
    if (_recording) {
        PRETTY_CRITICAL << "Recording is already in progress." << std::endl;
        throw CustomExceptions::InvalidOperation("Recording is already in progress.");
    }

    _destroyRecordedSamples();
    _destroyRecordingStream();
    _initializeRecordedSamples();
    _initializeNodeRecordingStream();

    _recording = true;
    _stopThread = false;

    _recordingThread = std::thread(&Audio::Recorder::_recordingLoop, this);
}

/**
 * @brief Stops the recording process.
 * @throws CustomExceptions::InvalidOperation if recording is not in progress.
 */
void Audio::Recorder::stopRecording()
{
    if (!_recording) {
        PRETTY_CRITICAL << "Recording is not in progress." << std::endl;
        throw CustomExceptions::InvalidOperation("Recording is not in progress.");
    }

    _recording = false;
    _stopThread = true;

    if (_recordingThread.joinable())
        _recordingThread.join();
}

/**
 * @brief Checks if recording is in progress.
 * @return True if recording is in progress, false otherwise.
 */
const bool Audio::Recorder::isRecording() const
{
    return _recording;
}

/**
 * @brief Gets the duration of the recording.
 * @return The duration of the recording in seconds.
 */
const unsigned int Audio::Recorder::getDuration() const
{
    return _recordedData.duration;
}

/**
 * @brief Retrieves the recorded audio samples.
 * @return A vector containing the recorded audio samples.
 */
const std::vector<float> Audio::Recorder::getRecordedSamples() const
{
    return _recordedData.samples;
}

/**
 * @brief Retrieves the recorded audio data.
 * @return A StreamData object containing the recorded audio data.
 */
const Audio::StreamData Audio::Recorder::getRecordedData() const
{
    return _recordedData;
}

/**
 * @brief Dumps the current state of the variables for debugging purposes.
 * @param indent The level to which the class should be indented in the dump.
 * @return The formatted output.
 */
const std::string Audio::Recorder::getInfo(const unsigned int indent) const
{
    std::string indentation(indent, '\t');
    std::string result = indentation + "Audio Recorder:\n";
    result += indentation + "- Recording: '" + Recoded::myToString(_recording, 0) + "'\n";
    result += indentation + "- Recorded Data: {\n" + Recoded::myToString(_recordedData, indent + 1) + indentation + "}\n";
    return result;
}

/**
 * @brief Updates the Recorder by copying another Audio::Recorder.
 * @param copy The Audio::Recorder to copy data from.
 */
void Audio::Recorder::update(const Audio::Recorder &copy)
{
    _recording = copy.isRecording();
    _recordedData = copy._recordedData;
    _paRecordErr = copy._paRecordErr;
}

/**
 * @brief Updates the Recorder by copying another Audio::StreamData.
 * @param copy The Audio::StreamData to copy data from.
 */
void Audio::Recorder::update(const Audio::StreamData &copy)
{
    _recordedData = copy;
}

/**
 * @brief Overloads the assignment operator to copy from another Audio::Recorder.
 * @param copy The Audio::Recorder to copy data from.
 * @return A reference to the updated instance.
 */
Audio::Recorder &Audio::Recorder::operator =(const Audio::Recorder &copy)
{
    update(copy);
    return *this;
}

/**
 * @brief Initializes the recorded samples buffer.
 */
void Audio::Recorder::_initializeRecordedSamples()
{
    _recordedData.samples.resize(_recordedData.duration * AUDIO_SAMPLE_RATE);
}

/**
 * @brief Initializes the audio stream for recording.
 * @throws CustomExceptions::NoAudioStream if there is an error initializing the audio stream.
 */
void Audio::Recorder::_initializeNodeRecordingStream()
{
    _paRecordErr = Pa_Initialize();
    if (_paRecordErr != paNoError) {
        const std::string errMsg = "PortAudio initialization error: " + std::string(Pa_GetErrorText(_paRecordErr));
        COLOUR_ERROR << errMsg << std::endl;
        throw CustomExceptions::NoAudioStream(errMsg);
    }

    _paRecordErr = Pa_OpenDefaultStream(
        &_paRawStream,
        1, // Mono Input
        0, // No Output
        paFloat32,
        AUDIO_SAMPLE_RATE,
        AUDIO_FRAMES_PER_BUFFER,
        nullptr,
        nullptr
    );

    if (_paRecordErr != paNoError) {
        Pa_Terminate();
        const std::string errMsg = "PortAudio open default stream error: " + std::string(Pa_GetErrorText(_paRecordErr));
        COLOUR_ERROR << errMsg << std::endl;
        throw CustomExceptions::NoAudioStream(errMsg);
    }
}

void Audio::Recorder::_recordingLoop()
{
    std::vector<float> buffer(AUDIO_FRAMES_PER_BUFFER);

    while (!_stopThread) {
        _paRecordErr = Pa_ReadStream(_paRawStream, buffer.data(), AUDIO_FRAMES_PER_BUFFER);
        if (_paRecordErr != paNoError) {
            _recording = false;
            break;
        }

        _recordedData.samples.insert(_recordedData.samples.end(), buffer.begin(), buffer.end());
    }

    _recording = false;
}

/**
 * @brief Destroys the recording stream.
 * @throws CustomExceptions::NoAudioStream if there is an error stopping or closing the audio stream.
 */
void Audio::Recorder::_destroyRecordingStream()
{
    if (_paRawStream) {
        Pa_StopStream(_paRawStream);
        Pa_CloseStream(_paRawStream);
        _paRawStream = nullptr;
    }
    Pa_Terminate();
}

/**
 * @brief Clears the recorded samples buffer.
 */
void Audio::Recorder::_destroyRecordedSamples()
{
    _recordedData.samples.clear();
}

/**
 * @brief Overloads the stream insertion operator for Audio::Recorder.
 * @param os The output stream.
 * @param recorder The Audio::Recorder instance.
 * @return The output stream.
 */
std::ostream &Audio::operator <<(std::ostream &os, const Audio::Recorder &recorder)
{
    os << recorder.getInfo();
    return os;
}
