/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** NotFound.hpp
*/

/**
 * @file NotFound.hpp
 *
 * @brief This file contains the definition of the FileNotFound exception class used to inform the user about missing files.
 */

#pragma once
#include <string>
#include <exception>

#include "Recoded.hpp"

namespace CustomExceptions
{
    /**
     * @brief Exception class for missing files.
     */
    class FileNotFound : public std::exception {
        public:
        /**
         * @brief Construct a new FileNotFound object.
         *
         * @param error Additional information about the error.
         */
        FileNotFound(const std::string &error = "");
        /**
         * @brief Destroy the FileNotFound object.
         */
        ~FileNotFound();
        /**
         * @brief Retrieves the error message.
         * @return A C-style string representing the error message.
         */
        const char *what() const noexcept;

        private:
        std::string _msg; //!< Stores the error message.
        const char *_buffer; //!< Buffer for formatted error message.
    };
}
