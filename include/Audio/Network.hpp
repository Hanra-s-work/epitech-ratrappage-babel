/*
** EPITECH PROJECT, 2024
** epitech-ratrappage-babel (Workspace)
** File description:
** AudioNetwork.hpp
*/

/**
 * @file AudioNetwork.hpp
 *
 * @brief This file contains the definition of the Audio::Network class, which handles audio stream conversion for network transmission.
 */

#pragma once

#include <any>
#include <memory>
#include <optional>

#include "Logging.hpp"
#include "Recoded.hpp"
#include "Utilities.hpp"
#include "CustomExceptions.hpp"

#include "Audio/Node.hpp"
#include "Audio/Compressor.hpp"

namespace Audio
{
    /**
     * @brief The Network class handles audio stream conversion for network transmission.
     */
    class Network {
        public:
        /**
         * @brief Construct a new Network object.
         */
        Network();

        /**
         * @brief Destroy the Network object.
         */
        ~Network();

        /**
         * @brief Converts the audio stream to a packet for network transmission.
         *
         * @param stream The audio stream to be converted.
         */
        void toPacket(const std::any &stream);

        /**
         * @brief Retrieves the audio stream from a network packet.
         *
         * @return An optional containing the audio stream if available, std::nullopt otherwise.
         */
        std::optional<std::any> fromPacket() const;

        /**
         * @brief Updates the Network by copying another Audio::Network.
         *
         * @param copy The Audio::Network to copy data from.
         */
        void update(const Audio::Network &copy);

        /**
         * @brief Dumps the current state of the variables for debugging purposes.
         *
         * @param indent The level to which the class should be indented in the dump.
         * @return The formatted output.
         */
        const std::string getInfo(const unsigned int indent = 0) const;

        /**
         * @brief Overloads the assignment operator to copy from another Audio::Network.
         *
         * @param copy The Audio::Network to copy data from.
         * @return A reference to the updated instance.
         */
        Network &operator =(const Audio::Network &copy);

        private:

    };

    /**
     * @brief Overloads the stream insertion operator for Audio::Network.
     *
     * @param os The output stream.
     * @param network The Audio::Network instance.
     * @return The output stream.
     */
    std::ostream &operator<<(std::ostream &os, const Audio::Network &network);
}
