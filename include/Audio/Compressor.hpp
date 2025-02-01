/*
** EPITECH PROJECT, 2024
** epitech-ratrappage-babel (Workspace)
** File description:
** AudioCompressor.hpp
*/

/**
 * @file AudioCompressor.hpp
 * @brief Definition of the Audio::Compressor class, which handles audio compression and decompression.
 */

#pragma once

#include <any>
#include <memory>

#include "Logging.hpp"
#include "Recoded.hpp"
#include "Utilities.hpp"

#include "Audio/Node.hpp"

namespace Audio
{
    /**
     * @brief The Compressor class handles audio compression and decompression.
     */
    class Compressor {
        public:
        /**
         * @brief Construct a new Compressor object.
         */
        Compressor();

        /**
         * @brief Destroy the Compressor object.
         */
        ~Compressor();

        /**
         * @brief Compresses the audio data from a Node.
         *
         * @param node The Node containing the audio data to compress.
         * @return An optional containing the compressed audio data if successful, std::nullopt otherwise.
         */
        std::optional<std::any> compressAudio(const Node &node);

        /**
         * @brief Decompresses the audio data.
         *
         * @param stream The compressed audio data to decompress.
         * @return A Node containing the decompressed audio data.
         */
        const Node decompressAudio(const std::any &stream);

        /**
         * @brief Updates the Compressor by copying another Compressor.
         *
         * @param copy The Compressor to copy data from.
         */
        void update(const Audio::Compressor &copy);

        /**
         * @brief Dumps the current state of the variables for debugging purposes.
         *
         * @param indent The level to which the class should be indented in the dump.
         * @return The formatted output.
         */
        const std::string getInfo(const unsigned int indent = 0) const;

        /**
         * @brief Overloads the assignment operator to copy from another Compressor.
         *
         * @param copy The Compressor to copy data from.
         * @return A reference to the updated instance.
         */
        Compressor &operator =(const Audio::Compressor &copy);

        private:

    };

    /**
     * @brief Overloads the stream insertion operator for Compressor.
     * @param os The output stream.
     * @param compressor The Compressor instance.
     * @return The output stream.
     */
    std::ostream &operator<<(std::ostream &os, const Audio::Compressor &compressor);
}
