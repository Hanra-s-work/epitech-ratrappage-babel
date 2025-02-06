/*
** EPITECH PROJECT, 2024
** record_compress_decompress_play
** File description:
** Initialisation.hpp
*/

#pragma once

#include <string>
#include <exception>

namespace CustomExceptions
{
    class InitialisationFailed : public std::exception {
        public:
        /**
         * @brief Construct a new InitialisationFailed object.
         *
         * @param address The address the program tried to connect to.
         */
        InitialisationFailed(const std::string &address = "");
        /**
         * @brief Destroy the InitialisationFailed object.
         */
        ~InitialisationFailed();
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
