/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** Found.hpp
*/

/**
 * @file Found.hpp
 *
 * @brief This file contains the definitions of custom exception classes used to inform the program about found content.
 */

#pragma once
#include <string>
#include <exception>

#include "Recoded.hpp"

namespace CustomExceptions
{

    /**
     * @brief Exception class for the help flag.
     * This is not an error.
     */
    class HelpFound : public std::exception {
        public:
        /**
         * @brief Construct a new HelpFound object.
         * Sets the message indicating that the help option was found.
         */
        HelpFound();
        /**
         * @brief Destroy the HelpFound object.
         */
        ~HelpFound();
        /**
         * @brief Retrieves the message.
         * @return A C-style string representing the message.
         */
        const char *what() const noexcept;

        private:
        std::string _msg; //!< Stores the message.
        const char *_buffer; //!< Buffer for formatted message.
    };

    /**
     * @brief Exception class for the version flag.
     * This is not an error.
     */
    class VersionFound : public std::exception {
        public:
        /**
         * @brief Construct a new VersionFound object.
         * Sets the message indicating that the version option was found.
         */
        VersionFound();
        /**
         * @brief Destroy the VersionFound object.
         */
        ~VersionFound();
        /**
         * @brief Retrieves the message.
         * @return A C-style string representing the message.
         */
        const char *what() const noexcept;

        private:
        std::string _msg; //!< Stores the message.
        const char *_buffer; //!< Buffer for formatted message.
    };

    /**
     * @brief Exception class for the thread termination.
     * This is not an error.
     */
    class ThreadFound : public std::exception {
        public:
        /**
         * @brief Construct a new ThreadFound object.
         * Sets the message indicating that a thread was found and terminated.
         */
        ThreadFound();
        /**
         * @brief Destroy the ThreadFound object.
         */
        ~ThreadFound();
        /**
         * @brief Retrieves the message.
         * @return A C-style string representing the message.
         */
        const char *what() const noexcept;

        private:
        std::string _msg; //!< Stores the message.
        const char *_buffer; //!< Buffer for formatted message.
    };
}
