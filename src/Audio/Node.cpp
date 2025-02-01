/*
** EPITECH PROJECT, 2024
** epitech-ratrappage-babel (Workspace)
** File description:
** Node.cpp
*/

#include "Audio/Node.hpp"

/**
 * @brief Construct a new Audio::Node object.
 *
 * @param duration The length of the recording in seconds.
 */
Audio::Node::Node(const unsigned int duration)
    : _recording(false), _playing(false), _stream(nullptr, Pa_CloseStream)
{
    setDuration(duration);
}

/**
 * @brief Destroy the Audio::Node object.
 */
Audio::Node::~Node() {}

/**
 * @brief Sets the duration of the recording.
 *
 * @param duration The length of the recording in seconds.
 * @throws CustomExceptions::InvalidDuration if the duration is not within the valid range.
 */
void Audio::Node::setDuration(const unsigned int duration)
{
    if (duration <= MIN_RECORDING_LENGTH || duration > MAX_RECORDING_LENGTH) {
        PRETTY_CRITICAL << "The duration should be between :" << Recoded::myToString(MIN_RECORDING_LENGTH) << " and " << Recoded::myToString(MAX_RECORDING_LENGTH) << ", but was of length: " << Recoded::myToString(duration) << std::endl;
        throw CustomExceptions::InvalidDuration(Recoded::myToString(duration), Recoded::myToString(MIN_RECORDING_LENGTH), Recoded::myToString(MAX_RECORDING_LENGTH));
    }
    _duration = duration;
}

/**
 * @brief Sets the audio stream.
 *
 * @param stream The audio stream to be set.
 * @throws CustomExceptions::NoAudioStream if the stream is invalid.
 */
void Audio::Node::setStream(const std::any &stream)
{
    const std::string errMsg = "Invalid stream type provided.";
    std::optional<std::shared_ptr<PaStream>> streamCapsule = Utilities::unCast<std::shared_ptr<PaStream>>(stream, false, errMsg + " Anycast error: ");
    if (!streamCapsule.has_value()) {
        PRETTY_CRITICAL << "There is no audioStream to process, '" << errMsg << "'." << std::endl;
        throw CustomExceptions::NoAudioStream(errMsg);
    }
    if (streamCapsule.value() == nullptr) {
        PRETTY_CRITICAL << errMsg << std::endl;
        throw CustomExceptions::NoAudioStream(errMsg + " Shared pointer is empty.");
    }
    _stream = streamCapsule.value();
}

/**
 * @brief Starts the recording process.
 *
 * @throws CustomExceptions::NoAudioStream if no audio stream is available.
 * @throws CustomExceptions::InvalidOperation if recording is already in progress.
 */
void Audio::Node::startRecording()
{
    if (!_stream) {
        PRETTY_CRITICAL << "No audio stream available for recording." << std::endl;
        throw CustomExceptions::NoAudioStream("No audio stream available for recording.");
    }
    if (_recording) {
        PRETTY_CRITICAL << "Recording is already in progress." << std::endl;
        throw CustomExceptions::InvalidOperation("Recording is already in progress.");
    }
    PRETTY_SUCCESS << "Setting the required parameters for audio recording" << std::endl;
    PaError err = Pa_StartStream(_stream.get());
    if (err != paNoError) {
        PRETTY_CRITICAL << "Failed to start recording stream." << std::endl;
        throw CustomExceptions::NoAudioStream("Failed to start recording stream.");
    }
    _recording = true;
}

/**
 * @brief Stops the recording process.
 *
 * @throws CustomExceptions::InvalidOperation if recording is not in progress.
 */
void Audio::Node::stopRecording()
{
    if (!_recording) {
        PRETTY_CRITICAL << "Recording is not in progress." << std::endl;
        throw CustomExceptions::InvalidOperation("Recording is not in progress.");
    }
    PRETTY_SUCCESS << "Stopping the audio recording" << std::endl;
    PaError err = Pa_StopStream(_stream.get());
    if (err != paNoError) {
        PRETTY_CRITICAL << "Failed to stop recording stream." << std::endl;
        throw CustomExceptions::NoAudioStream("Failed to stop recording stream.");
    }
    _recording = false;
}

/**
 * @brief Starts the playback process.
 *
 * @throws CustomExceptions::NoAudioStream if no audio stream is available.
 * @throws CustomExceptions::InvalidOperation if playback is already in progress.
 */
void Audio::Node::startPlaying()
{
    if (!_stream) {
        PRETTY_CRITICAL << "No audio stream available for playback." << std::endl;
        throw CustomExceptions::NoAudioStream("No audio stream available for playback.");
    }
    if (_playing) {
        PRETTY_CRITICAL << "Playback is already in progress." << std::endl;
        throw CustomExceptions::InvalidOperation("Playback is already in progress.");
    }
    PRETTY_SUCCESS << "Starting the audio playback" << std::endl;
    PaError err = Pa_StartStream(_stream.get());
    if (err != paNoError) {
        PRETTY_CRITICAL << "Failed to start playback stream." << std::endl;
        throw CustomExceptions::NoAudioStream("Failed to start playback stream.");
    }
    _playing = true;
}

/**
 * @brief Stops the playback process.
 *
 * @throws CustomExceptions::InvalidOperation if playback is not in progress.
 */
void Audio::Node::stopPlaying()
{
    if (!_playing) {
        PRETTY_CRITICAL << "Playback is not in progress." << std::endl;
        throw CustomExceptions::InvalidOperation("Playback is not in progress.");
    }
    PRETTY_SUCCESS << "Stopping the audio playback" << std::endl;
    PaError err = Pa_StopStream(_stream.get());
    if (err != paNoError) {
        PRETTY_CRITICAL << "Failed to stop playback stream." << std::endl;
        throw CustomExceptions::NoAudioStream("Failed to stop playback stream.");
    }
    _playing = false;
}

/**
 * @brief Checks if recording is in progress.
 *
 * @return True if recording is in progress, false otherwise.
 */
const bool Audio::Node::isRecording() const
{
    return _recording;
}

/**
 * @brief Checks if playback is in progress.
 *
 * @return True if playback is in progress, false otherwise.
 */
const bool Audio::Node::isPlaying() const
{
    return _playing;
}

/**
 * @brief Retrieves the audio stream.
 *
 * @return An optional containing the audio stream if available, std::nullopt otherwise.
 */
std::optional<std::any> Audio::Node::getStream() const
{
    if (!_stream) {
        PRETTY_WARNING << "There is no stream to return" << std::endl;
        return std::nullopt;
    }
    return std::make_optional<std::any>(
        std::make_any<std::shared_ptr<PaStream>>(
            _stream
        )
    );
}

/**
 * @brief Gets the duration of the recording.
 *
 * @return The duration of the recording in seconds.
 */
const unsigned int Audio::Node::getDuration() const
{
    return _duration;
}

/**
 * @brief Updates the Node by copying another Audio::Node.
 *
 * @param copy The Audio::Node to copy data from.
 */
void Audio::Node::update(const Audio::Node &copy)
{
    _playing = copy.isPlaying();
    _recording = copy.isRecording();
    setStream(copy.getStream());
    setDuration(copy.getDuration());
}

/**
 * @brief Dumps the current state of the variables for debugging purposes.
 *
 * @param indent The level to which the class should be indented in the dump.
 * @return The formatted output.
 */
const std::string Audio::Node::getInfo(const unsigned int indent) const
{
    std::string indentation = "";
    for (unsigned int i = 0; i < indent; ++i) {
        indentation += "\t";
    }
    std::string result = indentation + "Audio Node:\n";
    result += indentation + "- Playing: '" + Recoded::myToString(_playing) + "'\n";
    result += indentation + "- Recording: '" + Recoded::myToString(_recording) + "'\n";
    return result;
}

/**
 * @brief Overloads the assignment operator to copy from another Audio::Node.
 *
 * @param copy The Audio::Node to copy data from.
 * @return A reference to the updated instance.
 */
Audio::Node &Audio::Node::operator =(const Audio::Node &copy)
{
    update(copy);
    return *this;
}

/**
 * @brief Overloads the stream insertion operator for Audio::Node.
 *
 * @param os The output stream.
 * @param node The Audio::Node instance.
 * @return The output stream.
 */
std::ostream &Audio::operator<<(std::ostream &os, const Audio::Node &node)
{
    os << node.getInfo();
    return os;
}
