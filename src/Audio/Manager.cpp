/*
** EPITECH PROJECT, 2024
** epitech-ratrappage-babel (Workspace)
** File description:
** Manager.cpp
*/

#include "Audio/Manager.hpp"

Audio::Manager::Manager(const unsigned int duration)
    : _duration(duration), _node(duration)
{
}

Audio::Manager::~Manager()
{
}

void Audio::Manager::setDuration(const unsigned int duration)
{
    _duration = duration;
    _node.setDuration(duration);
}

void Audio::Manager::startRecording()
{
    try {
        COLOUR_INFO << "Recording..." << std::endl;
        PRETTY_INFO << "Recording started." << std::endl;
        _node.startRecording();
        PRETTY_SUCCESS << "Recording Done." << std::endl;
        COLOUR_SUCCESS << "Recording Done." << std::endl;
    }
    catch (const std::exception &e) {
        COLOUR_ERROR << e.what() << std::endl;
    }
}

void Audio::Manager::stopRecording()
{
    _node.stopRecording();
}

void Audio::Manager::startPlaying()
{
    try {
        COLOUR_INFO << "Playing..." << std::endl;
        PRETTY_DEBUG << "Playing started." << std::endl;
        _node.startPlaying();
        PRETTY_DEBUG << "Playing Done." << std::endl;
        COLOUR_SUCCESS << "Playing Done." << std::endl;
    }
    catch (const std::exception &e) {
        COLOUR_ERROR << e.what() << std::endl;
    }
}

void Audio::Manager::stopPlaying()
{
    _node.stopPlaying();
}

const bool Audio::Manager::isRecording()
{
    return _node.isRecording();
}

const bool Audio::Manager::isPlaying()
{
    return _node.isPlaying();
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

std::optional<std::any> Audio::Manager::getRawStream() const
{
    return _node.getStream();
}

std::optional<std::any> Audio::Manager::getCompressedStream() const
{
    PRETTY_WARNING << "Compressed stream retrieval is not implemented." << std::endl;
    return std::nullopt;
}

void Audio::Manager::setStream(const std::any &stream)
{
    _node.setStream(stream);
}

void Audio::Manager::update(const Audio::Manager &copy)
{
    _duration = copy._duration;
    _node.update(copy._node);
}

const std::string Audio::Manager::getInfo(const unsigned int indent) const
{
    std::string indentation = "";
    for (unsigned int i = 0; i < indent; ++i) {
        indentation += "\t";
    }
    std::string result = indentation + "Audio Manager:\n";
    result += indentation + "- Duration: '" + Recoded::myToString(_duration) + "'\n";
    result += indentation + "- Node: {\n" + _node.getInfo(indent + 1) + indentation + "'}\n";
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
