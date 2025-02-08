/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** Unknown.hpp
*/

/**
 * @file Unknown.hpp
 *
 * @brief This file contains the definition of the UnknownArgument exception class used to inform the user about unknown arguments.
 */

#pragma once
#include <string>
#include <exception>

#include "Recoded.hpp"

namespace CustomExceptions
{

    /**
     * @brief Exception class for unknown arguments.
     */
    class UnknownArgument : public std::exception {
        public:
        /**
         * @brief Construct a new UnknownArgument object.
         *
         * @param argument The argument that was provided by the user.
         */
        UnknownArgument(const std::string &argument = "");
        /**
         * @brief Destroy the UnknownArgument object.
         */
        ~UnknownArgument();
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
