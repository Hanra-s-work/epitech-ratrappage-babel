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
    if (_running || _thread.joinable()) {
        stopThread();
    }
}

/**
 * @brief Starts the thread for user controls.
 */
void Controls::ThreadCapsule::startThread()
{
    if (!_running) {
        _running = true;
        _thread = std::thread(&Controls::UserControls::spamUserChoice, &_userControls);
        std::cout << "Thread started" << std::endl;
    }
}

/**
 * @brief Stops the thread for user controls.
 */
void Controls::ThreadCapsule::stopThread(const unsigned int delay)
{
    // if (_running) {
    //     _running = false;

    //     if (_thread.joinable()) {
    //         std::chrono::steady_clock::time_point start_time = std::chrono::steady_clock::now();

    //         while (std::chrono::steady_clock::now() - start_time < std::chrono::seconds(delay)) {
    //             if (!_thread.joinable()) {
    //                 return;
    //             }
    //             std::this_thread::sleep_for(std::chrono::milliseconds(100));
    //         }

    //         PRETTY_INFO << "Thread did not stop in time. Forcibly terminating." << std::endl;
    //         try {
    //             PRETTY_INFO << "Injecting the 'q' key to stop the thread." << std::endl;
    //             std::cin.putback('q');
    //             std::cin.putback('\n');
    //             throw CustomExceptions::ThreadFound();
    //         }
    //         catch (const std::exception &e) {
    //             std::cerr << "Error: " << e.what() << std::endl;
    //         }
    //         catch (...) {
    //             std::cerr << "Unknown error occurred while stopping the thread." << std::endl;
    //         }
    //     }
    // }
    if (_running) {
        _running = false;
        PRETTY_INFO << "Injecting the 'q' key to stop the thread." << std::endl;
        _userControls.setLooping(false);
        _userControls.setPlaying(false);
        std::cin.putback('q');
        std::cin.putback('\n');
        std::cin.putback('\n');
        std::cin.putback('\n');
        std::cin.putback('\n');
        if (_thread.joinable()) {
            _thread.join();
        }
    }
    // if (_running) {
    //     _running = false;
    //     if (_thread.joinable()) {
    //         _thread.join();
    //     }
    // }
}

/**
 * @brief Checks if the thread is running.
 *
 * @return True if the thread is running, false otherwise.
 */
const bool Controls::ThreadCapsule::isRunning() const
{
    return _running;
}

/**
 * @brief Sets the echo state.
 *
 * @param echo The new echo state.
 */
void Controls::ThreadCapsule::setEcho(const bool echo)
{
    _userControls.setEcho(echo);
}

/**
 * @brief Sets the help state.
 *
 * @param help The new help state.
 */
void Controls::ThreadCapsule::setHelp(const bool help)
{
    _userControls.setHelp(help);
}

/**
 * @brief Sets the playing state.
 *
 * @param playing The new playing state.
 */
void Controls::ThreadCapsule::setPlaying(const bool playing)
{
    _userControls.setPlaying(playing);
}

/**
 * @brief Sets the looping state.
 *
 * @param looping The new looping state.
 */
void Controls::ThreadCapsule::setLooping(const bool looping)
{
    _userControls.setLooping(looping);
}

/**
 * @brief Sets the recording state.
 *
 * @param recording The new recording state.
 */
void Controls::ThreadCapsule::setRecording(const bool recording)
{
    _userControls.setRecording(recording);
}

/**
 * @brief Sets the user choice and performs the corresponding action.
 *
 * @param userChoice The user choice.
 */
void Controls::ThreadCapsule::setUserChoice(const std::string &userChoice)
{
    _userControls.setUserChoice(userChoice);
}

/**
 * @brief Checks if echo is enabled.
 *
 * @return True if echo is enabled, false otherwise.
 */
const bool Controls::ThreadCapsule::isEcho() const
{
    return _userControls.isEcho();
}

/**
 * @brief Checks if help is enabled.
 *
 * @return True if help is enabled, false otherwise.
 */
const bool Controls::ThreadCapsule::isHelp() const
{
    return _userControls.isHelp();
}

/**
 * @brief Checks if playing is enabled.
 *
 * @return True if playing is enabled, false otherwise.
 */
const bool Controls::ThreadCapsule::isPlaying() const
{
    return _userControls.isPlaying();
}

/**
 * @brief Checks if looping is enabled.
 *
 * @return True if looping is enabled, false otherwise.
 */
const bool Controls::ThreadCapsule::isLooping() const
{
    return _userControls.isLooping();
}

/**
 * @brief Checks if recording is enabled.
 *
 * @return True if recording is enabled, false otherwise.
 */
const bool Controls::ThreadCapsule::isRecording() const
{
    return _userControls.isRecording();
}

/**
 * @brief Checks if the call should be hung up.
 *
 * @return True if the call should be hung up, false otherwise.
 */
const bool Controls::ThreadCapsule::hangUpTheCall() const
{
    return _userControls.hangUpTheCall();
}

/**
 * @brief Shows the prompt to the user.
 */
void Controls::ThreadCapsule::showPrompt() const
{
    _userControls.showPrompt();
}

/**
 * @brief Toggles the echo state.
 */
void Controls::ThreadCapsule::toggleEcho()
{
    _userControls.toggleEcho();
}

/**
 * @brief Toggles the help state.
 */
void Controls::ThreadCapsule::toggleHelp()
{
    _userControls.toggleHelp();
}

/**
 * @brief Toggles the playing state.
 */
void Controls::ThreadCapsule::togglePlaying()
{
    _userControls.togglePlaying();
}

/**
 * @brief Toggles the looping state.
 */
void Controls::ThreadCapsule::toggleLooping()
{
    _userControls.toggleLooping();
}

/**
 * @brief Toggles the recording state.
 */
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
