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
}
