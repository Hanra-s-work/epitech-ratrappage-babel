/*
** EPITECH PROJECT, 2024
** epitech-ratrappage-babel (Workspace)
** File description:
** AudioNode.hpp
*/

/**
 * @file AudioNode.hpp
 *
 * @brief This file contains the definition of the Audio::Node class, which handles audio recording and playback.
 */

#pragma once

#include <any>
#include <memory>
#include <optional>
#include <portaudio.h>

#include "Logging.hpp"
#include "Recoded.hpp"
#include "Constants.hpp"
#include "Utilities.hpp"
#include "CustomExceptions.hpp"

namespace Audio
{
    /**
     * @brief The Node class handles audio recording and playback.
     */
    class Node {
        public:
        /**
         * @brief Construct a new Node object.
         *
         * @param duration The length of the recording in seconds.
         */
        Node(const unsigned int duration = 5);

        /**
         * @brief Destroy the Node object.
         */
        ~Node();

        /**
         * @brief Sets the duration of the recording.
         *
         * @param duration The length of the recording in seconds.
         * @throws CustomExceptions::InvalidDuration if the duration is not within the valid range.
         */
        void setDuration(const unsigned int duration);

        /**
         * @brief Sets the audio stream.
         *
         * @param stream The audio stream to be set.
         * @throws CustomExceptions::NoAudioStream if the stream is invalid.
         */
        void setStream(const std::any &stream);

        /**
         * @brief Starts the recording process.
         *
         * @throws CustomExceptions::NoAudioStream if no audio stream is available.
         * @throws CustomExceptions::InvalidOperation if recording is already in progress.
         */
        void startRecording();

        /**
         * @brief Stops the recording process.
         *
         * @throws CustomExceptions::InvalidOperation if recording is not in progress.
         */
        void stopRecording();

        /**
         * @brief Starts the playback process.
         *
         * @throws CustomExceptions::NoAudioStream if no audio stream is available.
         * @throws CustomExceptions::InvalidOperation if playback is already in progress.
         */
        void startPlaying();

        /**
         * @brief Stops the playback process.
         *
         * @throws CustomExceptions::InvalidOperation if playback is not in progress.
         */
        void stopPlaying();

        /**
         * @brief Checks if recording is in progress.
         *
         * @return True if recording is in progress, false otherwise.
         */
        const bool isRecording() const;

        /**
         * @brief Checks if playback is in progress.
         *
         * @return True if playback is in progress, false otherwise.
         */
        const bool isPlaying() const;

        /**
         * @brief Retrieves the audio stream.
         *
         * @return An optional containing the audio stream if available, std::nullopt otherwise.
         */
        std::optional<std::any> getStream() const;

        /**
         * @brief Gets the duration of the recording.
         *
         * @return The duration of the recording in seconds.
         */
        const unsigned int getDuration() const;

        /**
         * @brief Updates the Node by copying another Audio::Node.
         *
         * @param copy The Audio::Node to copy data from.
         */
        void update(const Audio::Node &copy);

        /**
         * @brief Dumps the current state of the variables for debugging purposes.
         *
         * @param indent The level to which the class should be indented in the dump.
         * @return The formatted output.
         */
        const std::string getInfo(const unsigned int indent = 0) const;

        /**
         * @brief Overloads the assignment operator to copy from another Audio::Node.
         *
         * @param copy The Audio::Node to copy data from.
         * @return A reference to the updated instance.
         */
        Node &operator =(const Audio::Node &copy);

        private:
        bool _playing = false; //!< Indicates if playback is in progress
        bool _recording = false; //!< Indicates if recording is in progress
        unsigned int _duration; //!< The recording length in seconds
        std::shared_ptr<PaStream> _stream; //!< Use shared_ptr for PaStream
        PaStreamParameters _inputParameters; //!< Input parameters for recording
        PaStreamParameters _outputParameters; //!< Output parameters for playback
    };

    /**
     * @brief Overloads the stream insertion operator for Audio::Node.
     *
     * @param os The output stream.
     * @param node The Audio::Node instance.
     * @return The output stream.
     */
    std::ostream &operator<<(std::ostream &os, const Audio::Node &node);
}
