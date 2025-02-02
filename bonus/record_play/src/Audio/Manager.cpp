/*
** EPITECH PROJECT, 2024
** epitech-ratrappage-babel (Workspace)
** File description:
** Manager.cpp
*/

#include "Audio/Manager.hpp"

Audio::Manager::Manager(const unsigned int duration)
{
    setDuration(duration);
}

Audio::Manager::~Manager()
{
}

void Audio::Manager::setDuration(const unsigned int duration)
{
    _duration = duration;
    _player.setDuration(duration);
    _recorder.setDuration(duration);
}

void Audio::Manager::startRecording()
{
    try {
        COLOUR_INFO << "Recording..." << std::endl;
        PRETTY_INFO << "Recording started." << std::endl;
        _recorder.startRecording();
        PRETTY_SUCCESS << "Recording Done." << std::endl;
        COLOUR_SUCCESS << "Recording Done." << std::endl;
    }
    catch (const std::exception &e) {
        COLOUR_ERROR << e.what() << std::endl;
    }
}

void Audio::Manager::stopRecording()
{
    try {
        COLOUR_INFO << "Stopping recording..." << std::endl;
        PRETTY_INFO << "Recording stopping." << std::endl;
        _recorder.stopRecording();
        PRETTY_SUCCESS << "Recording Done." << std::endl;
        COLOUR_SUCCESS << "Recording Done." << std::endl;
    }
    catch (const std::exception &e) {
        COLOUR_ERROR << e.what() << std::endl;
    }
}

void Audio::Manager::startPlaying()
{
    try {
        COLOUR_INFO << "Playing..." << std::endl;
        PRETTY_DEBUG << "Playing started." << std::endl;
        _player.startPlaying();
        PRETTY_DEBUG << "Playing Done." << std::endl;
        COLOUR_SUCCESS << "Playing Done." << std::endl;
    }
    catch (const std::exception &e) {
        COLOUR_ERROR << e.what() << std::endl;
    }
}

void Audio::Manager::stopPlaying()
{
    try {
        COLOUR_INFO << "Playing stopping..." << std::endl;
        PRETTY_DEBUG << "Playing stopping." << std::endl;
        _player.stopPlaying();
        PRETTY_DEBUG << "Playing Done." << std::endl;
        COLOUR_SUCCESS << "Playing Done." << std::endl;
    }
    catch (const std::exception &e) {
        COLOUR_ERROR << e.what() << std::endl;
    }
}

const bool Audio::Manager::isRecording() const
{
    return _recorder.isRecording();
}

const bool Audio::Manager::isPlaying() const
{
    return _player.isPlaying();
}

const unsigned int Audio::Manager::getDuration() const
{
    return _duration;
}

std::optional<std::any> Audio::Manager::getPacket() const
{
    PRETTY_WARNING << "Packet retrieval is not implemented." << std::endl;
    return std::nullopt;
}

const std::vector<float> Audio::Manager::getRecordedStream() const
{
    return _recorder.getRecordedSamples();
}

const std::vector<float> Audio::Manager::getPlayingStream() const
{
    return _player.getRecordedSamples();
}

std::optional<std::any> Audio::Manager::getCompressedStream() const
{
    PRETTY_WARNING << "Compressed stream retrieval is not implemented." << std::endl;
    return std::nullopt;
}

void Audio::Manager::setRecordedStream(const std::vector<float> &stream)
{
    _recorder.setRecordedSamples(stream);
}

void Audio::Manager::setPlayingStream(const std::vector<float> &stream)
{
    _player.setRecordedSamples(stream);
}

void Audio::Manager::update(const Audio::Manager &copy)
{
    _duration = copy._duration;
    _player = copy._player;
    _recorder = copy._recorder;
}

const std::string Audio::Manager::getInfo(const unsigned int indent) const
{
    std::string indentation = "";
    for (unsigned int i = 0; i < indent; ++i) {
        indentation += "\t";
    }
    std::string result = indentation + "Audio Manager:\n";
    result += indentation + "- Duration: '" + Recoded::myToString(_duration) + "'\n";
    result += indentation + "- Player: {\n" + _player.getInfo(indent + 1) + indentation + "}\n";
    result += indentation + "- Recorder: {\n" + _recorder.getInfo(indent + 1) + indentation + "}\n";
    return result;
}

Audio::Manager &Audio::Manager::operator =(const Audio::Manager &copy)
{
    update(copy);
    return *this;
}

std::ostream &Audio::operator<<(std::ostream &os, const Audio::Manager &manager)
{
    os << manager.getInfo();
    return os;
}
