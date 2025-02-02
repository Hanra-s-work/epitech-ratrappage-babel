/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** Failed.hpp
*/

/**
 * @file Failed.hpp
 *
 * @brief This file contains the definition of the ConnectionFailed exception class used to inform the user about failed connection attempts.
 */

#pragma once
#include <string>
#include <exception>

#include "Recoded.hpp"

namespace CustomExceptions
{
    /**
     * @brief Exception class for failed connection attempts.
     */
    class ConnectionFailed : public std::exception {
        public:
        /**
         * @brief Construct a new ConnectionFailed object.
         *
         * @param address The address the program tried to connect to.
         */
        ConnectionFailed(const std::string &address = "");
        /**
         * @brief Destroy the ConnectionFailed object.
         */
        ~ConnectionFailed();
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
