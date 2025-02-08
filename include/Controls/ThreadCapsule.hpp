/*
** EPITECH PROJECT, 2024
** epitech-ratrappage-babel (Workspace)
** File description:
** ThreadCapsule.hpp
*/

/**
 * @file ThreadCapsule.hpp
 * @brief This file contains the definition of the ThreadCapsule class, which manages a thread for user controls.
 */

#pragma once

#include <thread>
#include <atomic>

#include "Controls/UserControls.hpp"

namespace Controls
{
    /**
     * @brief Manages a thread for user controls.
     */
    class ThreadCapsule {
        public:
        ThreadCapsule();
        ~ThreadCapsule();

        /**
         * @brief Starts the thread to run the spamUserChoice function.
         */
        void startThread();

        /**
         * @brief Stops the thread safely.
         */
        void stopThread();

        /**
         * @brief Checks if the thread is running.
         *
         * @return True if the thread is running, false otherwise.
         */
        const bool isRunning() const;

        /**
         * @brief Dumps the current state of the variables for debugging purposes.
         *
         * @param indent The level to which the class should be indented in the dump.
         * @return The formatted output.
         */
        const std::string getInfo(const unsigned int indent = 0) const;

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

        void showPrompt() const;

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

        private:
        std::thread _thread; //!< The thread instance.
        std::atomic<bool> _running; //!< Running state.
        UserControls _userControls; //!< User controls instance.
    };

    /**
     * @brief Overloads the stream insertion operator for ThreadCapsule.
     *
     * @param os The output stream.
     * @param network The ThreadCapsule instance.
     * @return The output stream.
     */
    std::ostream &operator<<(std::ostream &os, const ThreadCapsule &network);
}
