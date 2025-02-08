/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** No.hpp
*/

/**
 * @file No.hpp
 *
 * @brief This file contains the definitions of custom exception classes used to inform the user about missing elements.
 */

#pragma once
#include <string>
#include <exception>

#include "Recoded.hpp"

namespace CustomExceptions
{
    /**
     * @brief Exception class for missing flag parameters.
     */
    class NoFlagParameter : public std::exception {
        public:
        /**
         * @brief Construct a new NoFlagParameter object.
         *
         * @param error Additional information about the error.
         */
        NoFlagParameter(const std::string &error = "");
        /**
         * @brief Destroy the NoFlagParameter object.
         */
        ~NoFlagParameter();
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
     * @brief Exception class for missing TOML files.
     */
    class NoTOML : public std::exception {
        public:
        /**
         * @brief Construct a new NoTOML object.
         *
         * @param tomlPath The path to the TOML file.
         */
        NoTOML(const std::string &tomlPath = "");
        /**
         * @brief Destroy the NoTOML object.
         */
        ~NoTOML();
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
     * @brief Exception class for missing TOML keys.
     */
    class NoTOMLKey : public std::exception {
        public:
        /**
         * @brief Construct a new NoTOMLKey object.
         *
         * @param tomlPath The path to the TOML file.
         * @param tomlKey The key that the user tried to access.
         */
        NoTOMLKey(const std::string &tomlPath = "", const std::string &tomlKey = "");
        /**
         * @brief Destroy the NoTOMLKey object.
         */
        ~NoTOMLKey();
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
     * @brief Exception class for missing active network managers.
     */
    class NoActiveNetwork : public std::exception {
        public:
        /**
         * @brief Construct a new NoActiveNetwork object.
         *
         * @param exceptionDetails Additional details provided for the specific reason the error was raised.
         */
        NoActiveNetwork(const std::string &exceptionDetails = "");
        ~NoActiveNetwork();
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
     * @brief Exception class for missing address managers.
     */
    class NoAddressManager : public std::exception {
        public:
        /**
         * @brief Construct a new NoAddressManager object.
         *
         * @param exceptionDetails Additional details provided for the specific reason the error was raised.
         */
        NoAddressManager(const std::string &exceptionDetails = "");
        ~NoAddressManager();
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
     * @brief Exception class for missing network class instances.
     */
    class NoNetworkClass : public std::exception {
        public:
        /**
         * @brief Construct a new NoNetworkClass object.
         *
         * @param exceptionDetails Additional details provided for the specific reason the error was raised.
         */
        NoNetworkClass(const std::string &exceptionDetails = "");
        ~NoNetworkClass();
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
     * @brief Exception class for missing audio streams.
     */
    class NoAudioStream : public std::exception {
        public:
        /**
         * @brief Construct a new NoAudioStream object.
         *
         * @param exceptionDetails Additional details provided for the specific reason the error was raised.
         */
        NoAudioStream(const std::string &exceptionDetails = "");
        /**
         * @brief Destroy the NoAudioStream object.
         */
        ~NoAudioStream();
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
     * @brief Exception class for missing compressed audio data.
     */
    class NoCompressedAudio : public std::exception {
        public:
        /**
         * @brief Construct a new NoCompressedAudio object.
         *
         * @param exceptionDetails Additional details provided for the specific reason the error was raised.
         */
        NoCompressedAudio(const std::string &exceptionDetails = "");
        /**
         * @brief Destroy the NoCompressedAudio object.
         */
        ~NoCompressedAudio();
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
     * @brief Exception class for missing audio packets.
     */
    class NoAudioPacket : public std::exception {
        public:
        /**
         * @brief Construct a new NoAudioPacket object.
         *
         * @param exceptionDetails Additional details provided for the specific reason the error was raised.
         */
        NoAudioPacket(const std::string &exceptionDetails = "");
        /**
         * @brief Destroy the NoAudioPacket object.
         */
        ~NoAudioPacket();
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
