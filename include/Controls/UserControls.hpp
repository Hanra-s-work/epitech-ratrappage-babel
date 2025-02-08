/*
** EPITECH PROJECT, 2024
** epitech-ratrappage-babel (Workspace)
** File description:
** Controls.hpp
*/

/**
 * @file UserControls.hpp
 * @brief This file contains the definition of the UserControls class, which manages user input and control states.
 */

#pragma once
#include <atomic>
#include <string>

#include "Logging.hpp"
#include "Recoded.hpp"
#include "CustomExceptions.hpp"

namespace Controls
{
    /**
     * @brief Manages user input and control states.
     */
    class UserControls {
        public:
        UserControls();
        ~UserControls();

        /**
         * @brief Sets the echo state.
         * @param echo The new echo state.
         */
        void setEcho(const bool echo);

        /**
         * @brief Sets the help state.
         * @param help The new help state.
         */
        void setHelp(const bool help);

        /**
         * @brief Sets the playing state.
         * @param playing The new playing state.
         */
        void setPlaying(const bool playing);

        /**
         * @brief Sets the looping state.
         * @param looping The new looping state.
         */
        void setLooping(const bool looping);

        /**
         * @brief Sets the recording state.
         * @param recording The new recording state.
         */
        void setRecording(const bool recording);

        /**
         * @brief Processes the user choice.
         * @param userChoice The user choice.
         */
        void setUserChoice(const std::string &userChoice);

        /**
         * @brief Checks if echo is enabled.
         * @return True if echo is enabled, false otherwise.
         */
        const bool isEcho() const;

        /**
         * @brief Checks if help is enabled.
         * @return True if help is enabled, false otherwise.
         */
        const bool isHelp() const;

        /**
         * @brief Checks if playing is enabled.
         * @return True if playing is enabled, false otherwise.
         */
        const bool isPlaying() const;

        /**
         * @brief Checks if looping is enabled.
         * @return True if looping is enabled, false otherwise.
         */
        const bool isLooping() const;

        /**
         * @brief Checks if recording is enabled.
         * @return True if recording is enabled, false otherwise.
         */
        const bool isRecording() const;

        const bool hangUpTheCall() const;

        /**
         * @brief Toggles the echo state.
         */
        void toggleEcho();

        /**
         * @brief Toggles the help state.
         */
        void toggleHelp();

        /**
         * @brief Toggles the playing state.
         */
        void togglePlaying();

        /**
         * @brief Toggles the looping state.
         */
        void toggleLooping();

        /**
         * @brief Toggles the recording state.
         */
        void toggleRecording();

        /**
         * @brief Gets the echo state.
         * @return The echo state.
         */
        const bool getEcho() const;

        /**
         * @brief Gets the help state.
         * @return The help state.
         */
        const bool getHelp() const;

        /**
         * @brief Gets the playing state.
         * @return The playing state.
         */
        const bool getPlaying() const;

        /**
         * @brief Gets the looping state.
         * @return The looping state.
         */
        const bool getLooping() const;

        /**
         * @brief Gets the recording state.
         * @return The recording state.
         */
        const bool getRecording() const;

        /**
         * @brief Continuously prompts the user for input and processes it.
         */
        void spamUserChoice();

        /**
         * @brief Dumps the current state of the variables for debugging purposes.
         *
         * @param indent The level to which the class should be indented in the dump.
         * @return The formatted output.
         */
        const std::string getInfo(const unsigned int indent = 0) const;

        private:
        /**
         * @brief Displays the help message.
         */
        void _displayHelp() const;

        const std::string _gatherResponse() const;

        /**
         * @brief Prompts the user for input.
         * @return The user input.
         */
        const std::string _getUserChoice() const;

        std::atomic<bool> _echo; //!< Echo state.
        std::atomic<bool> _help; //!< Help state.
        std::atomic<bool> _hangUp; //!< Echo state.
        std::atomic<bool> _playing; //!< Playing state.
        std::atomic<bool> _looping; //!< Looping state.
        std::atomic<bool> _recording; //!< Recording state.
    };

    /**
     * @brief Overloads the stream insertion operator for UserControls.
     *
     * @param os The output stream.
     * @param network The UserControls instance.
     * @return The output stream.
     */
    std::ostream &operator<<(std::ostream &os, const UserControls &network);
}
