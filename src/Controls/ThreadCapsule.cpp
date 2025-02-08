/*
** EPITECH PROJECT, 2024
** epitech-ratrappage-babel (Workspace)
** File description:
** ThreadCapsule.cpp
*/

/**
 * @file ThreadCapsule.cpp
 * @brief This file contains the implementation of the ThreadCapsule class, which manages a thread for user controls.
 */

#include "Controls/ThreadCapsule.hpp"

Controls::ThreadCapsule::ThreadCapsule()
    : _running(false)
{

}

Controls::ThreadCapsule::~ThreadCapsule()
{
    stopThread();
}

void Controls::ThreadCapsule::startThread()
{
    if (!_running) {
        _running = true;
        _thread = std::thread(&Controls::UserControls::spamUserChoice, &_userControls);
        std::cout << "Thread started" << std::endl;
    }
}

void Controls::ThreadCapsule::stopThread()
{
    if (_running) {
        _running = false;
        if (_thread.joinable()) {
            _thread.join();
        }
    }
}

const bool Controls::ThreadCapsule::isRunning() const
{
    return _running;
}

void Controls::ThreadCapsule::setEcho(const bool echo)
{
    _userControls.setEcho(echo);
}

void Controls::ThreadCapsule::setHelp(const bool help)
{
    _userControls.setHelp(help);
}

void Controls::ThreadCapsule::setPlaying(const bool playing)
{
    _userControls.setPlaying(playing);
}

void Controls::ThreadCapsule::setLooping(const bool looping)
{
    _userControls.setLooping(looping);
}

void Controls::ThreadCapsule::setRecording(const bool recording)
{
    _userControls.setRecording(recording);
}

void Controls::ThreadCapsule::setUserChoice(const std::string &userChoice)
{
    _userControls.setUserChoice(userChoice);
}

const bool Controls::ThreadCapsule::isEcho() const
{
    return _userControls.isEcho();
}

const bool Controls::ThreadCapsule::isHelp() const
{
    return _userControls.isHelp();
}

const bool Controls::ThreadCapsule::isPlaying() const
{
    return _userControls.isPlaying();
}

const bool Controls::ThreadCapsule::isLooping() const
{
    return _userControls.isLooping();
}

const bool Controls::ThreadCapsule::isRecording() const
{
    return _userControls.isRecording();
}

const bool Controls::ThreadCapsule::hangUpTheCall() const
{
    return _userControls.hangUpTheCall();
}

void Controls::ThreadCapsule::showPrompt() const
{
    _userControls.showPrompt();
}

void Controls::ThreadCapsule::toggleEcho()
{
    _userControls.toggleEcho();
}

void Controls::ThreadCapsule::toggleHelp()
{
    _userControls.toggleHelp();
}

void Controls::ThreadCapsule::togglePlaying()
{
    _userControls.togglePlaying();
}

void Controls::ThreadCapsule::toggleLooping()
{
    _userControls.toggleLooping();
}

void Controls::ThreadCapsule::toggleRecording()
{
    _userControls.toggleRecording();
}

/**
 * @brief Dumps the current state of the variables for debugging purposes.
 *
 * @param indent The level to which the class should be indented in the dump.
 * @return The formatted output.
 */
const std::string Controls::ThreadCapsule::getInfo(const unsigned int indent) const
{
    std::string indentation = "";
    for (unsigned int i = 0; i < indent; ++i) {
        indentation += "\t";
    }
    std::string result = indentation + "Thread Capsule:\n";
    result += indentation + "- Running: '" + Recoded::myToString(_running) + "'\n";
    result += indentation + "- User Controls: {\n" + _userControls.getInfo(indent + 1) + indentation + "}\n";
    return result;
}

/**
 * @brief Overloads the stream insertion operator for ThreadCapsule.
 *
 * @param os The output stream.
 * @param network The ThreadCapsule instance.
 * @return The output stream.
 */
std::ostream &Controls::operator<<(std::ostream &os, const Controls::ThreadCapsule &network)
{
    os << network.getInfo();
    return os;
}
