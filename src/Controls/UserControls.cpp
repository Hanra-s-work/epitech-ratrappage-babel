/*
** EPITECH PROJECT, 2024
** epitech-ratrappage-babel (Workspace)
** File description:
** Controls.cpp
*/

/**
 * @file UserControls.cpp
 * @brief This file contains the implementation of the UserControls class, which manages user input and control states.
 */

#include "Controls/UserControls.hpp"
#include <mutex>

std::mutex logMutex;

Controls::UserControls::UserControls()
    : _playing(false), _recording(false), _looping(true), _echo(false), _help(false)
{
}

Controls::UserControls::~UserControls()
{
}

/**
 * @brief Sets the echo state.
 *
 * @param echo The new echo state.
 */
void Controls::UserControls::setEcho(const bool echo)
{
    _echo = echo;
}

/**
 * @brief Sets the help state.
 *
 * @param help The new help state.
 */
void Controls::UserControls::setHelp(const bool help)
{
    _help = help;
}

/**
 * @brief Sets the playing state.
 *
 * @param playing The new playing state.
 */
void Controls::UserControls::setPlaying(const bool playing)
{
    _playing = playing;
}

/**
 * @brief Sets the looping state.
 *
 * @param looping The new looping state.
 */
void Controls::UserControls::setLooping(const bool looping)
{
    _looping = looping;
}

/**
 * @brief Sets the recording state.
 *
 * @param recording The new recording state.
 */
void Controls::UserControls::setRecording(const bool recording)
{
    _recording = recording;
}

/**
 * @brief Sets the user choice and performs the corresponding action.
 *
 * @param userChoice The user choice.
 */
void Controls::UserControls::setUserChoice(const std::string &userChoice)
{
    if (userChoice.empty()) {
        const std::string errMsg = "User choice cannot be empty";
        PRETTY_DEBUG << errMsg << std::endl;
        throw CustomExceptions::InvalidChoice(errMsg);
    }

    const bool logStatus = Logging::Log::getInstance().getLogEnabled();
    Logging::Log::getInstance().setLogEnabled(true);

    // if (userChoice == "r") {
    //     toggleRecording();
    //     if (isRecording()) {
    //         COLOUR_INFO << "Recording is enabled" << std::endl;
    //     } else {
    //         COLOUR_INFO << "Recording is disabled" << std::endl;
    //     }
    // } else if (userChoice == "p") {
    //     togglePlaying();
    //     if (isPlaying()) {
    //         COLOUR_INFO << "Playing is enabled" << std::endl;
    //     } else {
    //         COLOUR_INFO << "Playing is disabled" << std::endl;
    //     }
    // } else
    if (userChoice == "l" || userChoice == "q" || userChoice == "esc") {
        toggleLooping();
        _hangUp = true;
        if (isLooping()) {
            COLOUR_INFO << "Looping is enabled" << std::endl;
        } else {
            COLOUR_INFO << "Looping is disabled" << std::endl;
        }
    } else if (userChoice == "e") {
        toggleEcho();
        if (isEcho()) {
            COLOUR_INFO << "Echo is enabled" << std::endl;
        } else {
            COLOUR_INFO << "Echo is disabled" << std::endl;
        }
    } else if (userChoice == "h") {
        toggleHelp();
    } else if (userChoice == "hu") {
        if (isEcho()) {
            COLOUR_INFO << "Hanging up the call" << std::endl;
        }
        _hangUp = true;
        toggleLooping();
    } else if (userChoice == "i") {
        COLOUR_INFO << getInfo() << std::endl;
    } else {
        Logging::Log::getInstance().setLogEnabled(logStatus);
        throw CustomExceptions::InvalidChoice("Invalid user choice");
    }
    if (isHelp()) {
        _displayHelp();
        setHelp(false);
    }
    Logging::Log::getInstance().setLogEnabled(logStatus);
}

/**
 * @brief Checks if echo is enabled.
 *
 * @return True if echo is enabled, false otherwise.
 */
const bool Controls::UserControls::isEcho() const
{
    return _echo;
}

/**
 * @brief Checks if help is enabled.
 *
 * @return True if help is enabled, false otherwise.
 */
const bool Controls::UserControls::isHelp() const
{
    return _help;
}

/**
 * @brief Checks if playing is enabled.
 *
 * @return True if playing is enabled, false otherwise.
 */
const bool Controls::UserControls::isPlaying() const
{
    return _playing;
}

/**
 * @brief Checks if looping is enabled.
 *
 * @return True if looping is enabled, false otherwise.
 */
const bool Controls::UserControls::isLooping() const
{
    return _looping;
}

/**
 * @brief Checks if recording is enabled.
 *
 * @return True if recording is enabled, false otherwise.
 */
const bool Controls::UserControls::isRecording() const
{
    return _recording;
}

const bool Controls::UserControls::hangUpTheCall() const
{
    return _hangUp;
}

/**
 * @brief Toggles the echo state.
 */
void Controls::UserControls::toggleEcho()
{
    _echo = !_echo;
}

/**
 * @brief Toggles the help state.
 */
void Controls::UserControls::toggleHelp()
{
    _help = !_help;
}

/**
 * @brief Toggles the playing state.
 */
void Controls::UserControls::togglePlaying()
{
    _playing = !_playing;
}

/**
 * @brief Toggles the looping state.
 */
void Controls::UserControls::toggleLooping()
{
    _looping = !_looping;
}

/**
 * @brief Toggles the recording state.
 */
void Controls::UserControls::toggleRecording()
{
    _recording = !_recording;
}

/**
 * @brief Gets the echo state.
 *
 * @return The echo state.
 */
const bool Controls::UserControls::getEcho() const
{
    return _echo;
}

/**
 * @brief Gets the help state.
 *
 * @return The help state.
 */
const bool Controls::UserControls::getHelp() const
{
    return _help;
}

/**
 * @brief Gets the playing state.
 *
 * @return The playing state.
 */
const bool Controls::UserControls::getPlaying() const
{
    return _playing;
}

/**
 * @brief Gets the looping state.
 *
 * @return The looping state.
 */
const bool Controls::UserControls::getLooping() const
{
    return _looping;
}

/**
 * @brief Gets the recording state.
 *
 * @return The recording state.
 */
const bool Controls::UserControls::getRecording() const
{
    return _recording;
}

/**
 * @brief Displays the help message.
 */
void Controls::UserControls::_displayHelp() const
{
    std::cout << RESET_COL << BACKGROUND_COL << INFO_COL << "Help:\n" << RESET_COL << BACKGROUND_COL << DEFAULT_FG;
    // std::cout << RESET_COL << BACKGROUND_COL << "\t" << SUCCESS_COL << "r:" << DEBUG_COL << " Record" << RESET_COL << BACKGROUND_COL << DEFAULT_FG << "\t Start a recording of a specified duration\n";
    // std::cout << RESET_COL << BACKGROUND_COL << "\t" << SUCCESS_COL << "p:" << DEBUG_COL << " Play  " << RESET_COL << BACKGROUND_COL << DEFAULT_FG << "\t Play the recording (if any are present)\n";
    std::cout << RESET_COL << BACKGROUND_COL << "\t" << SUCCESS_COL << "l:" << DEBUG_COL << " Loop  " << RESET_COL << BACKGROUND_COL << DEFAULT_FG << "\t Stop this loop (will stop the whole program)\n";
    std::cout << RESET_COL << BACKGROUND_COL << "\t" << SUCCESS_COL << "hu:" << DEBUG_COL << " Hang Up  " << RESET_COL << BACKGROUND_COL << DEFAULT_FG << "\t Hang the phone up, close the connection between both concerned parties\n";
    std::cout << RESET_COL << BACKGROUND_COL << "\t" << SUCCESS_COL << "e:" << DEBUG_COL << " Echo  " << RESET_COL << BACKGROUND_COL << DEFAULT_FG << "\t Toggle if to display or not the command that was entered\n";
    std::cout << RESET_COL << BACKGROUND_COL << "\t" << SUCCESS_COL << "h:" << DEBUG_COL << " Help  " << RESET_COL << BACKGROUND_COL << DEFAULT_FG << "\t Display this help.\n";
    std::cout << RESET_COL << BACKGROUND_COL << "\t" << SUCCESS_COL << "i:" << DEBUG_COL << " Info  " << RESET_COL << BACKGROUND_COL << DEFAULT_FG << "\t Display the current state of the user command prompt configuration\n";
    std::cout << RESET_COL << BACKGROUND_COL << "\t" << SUCCESS_COL << "q:" << DEBUG_COL << " Quit  " << RESET_COL << BACKGROUND_COL << DEFAULT_FG << "\t Exit the program\n";
    std::cout << RESET_COL << std::flush;
}

/**
 * @brief Gathers the user response from the input.
 *
 * @return The user response.
 */
const std::string Controls::UserControls::_gatherResponse() const
{
    std::string response;
    char c;
    while (std::cin.get(c)) {
        if (c == '\n') {
            break;
        }
        response += c;
    }
    return response;
}

void Controls::UserControls::showPrompt() const
{
    // std::cout << RESET_COL << BACKGROUND_COL << DEFAULT_FG << "Enter your choice ([r]ecord, [p]lay, [l]oop, [e]cho, [h]elp, [i]nfo, [q]uit): " << std::flush;
    std::cout << RESET_COL << BACKGROUND_COL << DEFAULT_FG << "Enter your choice ([hu] Hang Up, [l]oop, [e]cho, [h]elp, [i]nfo, [q]uit): " << std::flush;
}

/**
 * @brief Gets the user choice from the input.
 *
 * @return The user choice.
 */
const std::string Controls::UserControls::_getUserChoice() const
{
    std::string choice;
    showPrompt();
    choice = _gatherResponse();
    return choice;
}

/**
 * @brief Continuously prompts the user for input and processes the choice.
 */
void Controls::UserControls::spamUserChoice()
{
    while (_looping == true) {
        try {
            std::string resp = _getUserChoice();
            if (_echo) {
                bool logStatus = Logging::Log::getInstance().getLogEnabled();
                Logging::Log::getInstance().setLogEnabled(true);
                COLOUR_INFO << "User choice: '" << resp << "'" << std::endl;
                Logging::Log::getInstance().setLogEnabled(logStatus);
            }
            setUserChoice(resp);
        }
        catch (const std::exception &e) {
            bool logStatus = Logging::Log::getInstance().getLogEnabled();
            Logging::Log::getInstance().setLogEnabled(true);
            COLOUR_ERROR << e.what() << std::endl;
            Logging::Log::getInstance().setLogEnabled(logStatus);
        }
    }
}

/**
 * @brief Dumps the current state of the variables for debugging purposes.
 *
 * @param indent The level to which the class should be indented in the dump.
 * @return The formatted output.
 */
const std::string Controls::UserControls::getInfo(const unsigned int indent) const
{
    std::string indentation = "";
    for (unsigned int i = 0; i < indent; ++i) {
        indentation += "\t";
    }
    std::string result = indentation + "User Controls:\n";
    result += indentation + "- Echo: '" + Recoded::myToString(_echo) + "'\n";
    result += indentation + "- Help: '" + Recoded::myToString(_help) + "'\n";
    result += indentation + "- Playing: '" + Recoded::myToString(_playing) + "'\n";
    result += indentation + "- Looping: '" + Recoded::myToString(_looping) + "'\n";
    result += indentation + "- Recording: '" + Recoded::myToString(_recording) + "'\n";
    return result;
}

/**
 * @brief Overloads the stream insertion operator for UserControls.
 *
 * @param os The output stream.
 * @param network The UserControls instance.
 * @return The output stream.
 */
std::ostream &Controls::operator<<(std::ostream &os, const Controls::UserControls &network)
{
    os << network.getInfo();
    return os;
}
