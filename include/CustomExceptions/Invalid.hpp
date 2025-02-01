/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** Invalid.hpp
*/

/**
 * @file Invalid.hpp
 *
 * @brief This file contains the definitions of custom exception classes used to inform the user about various invalid inputs.
 */

#pragma once

#include <string>
#include <exception>

#include "Recoded.hpp"
#include "Constants.hpp"

namespace CustomExceptions
{

    /**
     * @brief Exception class for invalid IP addresses.
     */
    class InvalidIp : public std::exception {
        public:
        /**
         * @brief Construct a new InvalidIp object.
         *
         * @param error Additional information about the error.
         */
        InvalidIp(const std::string &error = "");
        /**
         * @brief Destroy the InvalidIp object.
         */
        ~InvalidIp();
        /**
         * @brief Retrieves the error message.
         * @return A C-style string representing the error message.
         */
        const char *what() const noexcept;

        private:
        std::string _msg; //!< Stores the error message.
        const char *_buffer; //!< Buffer for formatted error message.
    };

    /**
     * @brief Exception class for invalid port numbers.
     */
    class InvalidPort : public std::exception {
        public:
        /**
         * @brief Construct a new InvalidPort object.
         *
         * @param error Additional information about the error.
         */
        InvalidPort(const std::string &error = "");
        /**
         * @brief Destroy the InvalidPort object.
         */
        ~InvalidPort();
        /**
         * @brief Retrieves the error message.
         * @return A C-style string representing the error message.
         */
        const char *what() const noexcept;

        private:
        std::string _msg; //!< Stores the error message.
        const char *_buffer; //!< Buffer for formatted error message.
    };


    /**
     * @brief Exception class for invalid types in std::any.
     */
    class InvalidType : public std::exception {
        public:
        /**
         * @brief Construct a new InvalidType object.
         *
         * @param extraDetails A string with a more detailed explanation of the error.
         */
        InvalidType(const std::string &extraDetails = "");
        /**
         * @brief Destroy the InvalidType object.
         */
        ~InvalidType();
        /**
         * @brief Retrieves the error message.
         * @return A C-style string representing the error message.
         */
        const char *what() const noexcept;

        private:
        std::string _msg; //!< Stores the error message.
        const char *_buffer; //!< Buffer for formatted error message.
    };

    /**
     * @brief Exception class for invalid usernames.
     */
    class InvalidUsername : public std::exception {
        public:
        /**
         * @brief Construct a new InvalidUsername object.
         *
         * @param error Additional information about the error.
         */
        InvalidUsername(const std::string &error = "");
        /**
         * @brief Destroy the InvalidUsername object.
         */
        ~InvalidUsername();
        /**
         * @brief Retrieves the error message.
         * @return A C-style string representing the error message.
         */
        const char *what() const noexcept;

        private:
        std::string _msg; //!< Stores the error message.
        const char *_buffer; //!< Buffer for formatted error message.
    };

    /**
     * @brief Exception class for invalid durations.
     */
    class InvalidDuration : public std::exception {
        public:
        /**
         * @brief Construct a new InvalidDuration object.
         *
         * @param duration The duration provided by the user.
         * @param min The minimum allowed duration.
         * @param max The maximum allowed duration.
         */
        InvalidDuration(const std::string &duration = "", const std::string &min = "", const std::string &max = "");
        /**
         * @brief Destroy the InvalidDuration object.
         */
        ~InvalidDuration();
        /**
         * @brief Retrieves the error message.
         * @return A C-style string representing the error message.
         */
        const char *what() const noexcept;

        private:
        std::string _msg; //!< Stores the error message.
        const char *_buffer; //!< Buffer for formatted error message.
    };

    /**
     * @brief Exception class for invalid TOML files.
     */
    class InvalidTOML : public std::exception {
        public:
        /**
         * @brief Construct a new InvalidTOML object.
         *
         * @param path The path to the TOML file provided by the user.
         * @param error Additional information about the error.
         */
        InvalidTOML(const std::string &path = "", const std::string &error = "");
        /**
         * @brief Destroy the InvalidTOML object.
         */
        ~InvalidTOML();
        /**
         * @brief Retrieves the error message.
         * @return A C-style string representing the error message.
         */
        const char *what() const noexcept;

        private:
        std::string _msg; //!< Stores the error message.
        const char *_buffer; //!< Buffer for formatted error message.
    };

    /**
     * @brief Exception class for invalid TOML key types.
     */
    class InvalidTOMLKeyType : public std::exception {
        public:
        /**
         * @brief Construct a new InvalidTOMLKeyType object.
         *
         * @param tomlPath The path to the TOML file.
         * @param tomlKey The key that contains the invalid type.
         * @param currentType The current type of the key in the configuration file.
         * @param expectedType The expected type of the key.
         */
        InvalidTOMLKeyType(const std::string &tomlPath = "", const std::string &tomlKey = "", const std::string &currentType = "", const std::string &expectedType = "");
        /**
         * @brief Destroy the InvalidTOMLKeyType object.
         */
        ~InvalidTOMLKeyType();
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
