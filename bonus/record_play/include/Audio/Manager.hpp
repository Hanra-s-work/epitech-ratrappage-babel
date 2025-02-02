/*
** EPITECH PROJECT, 2024
** epitech-ratrappage-babel (Workspace)
** File description:
** Manager.hpp
*/

/**
 * @file Manager.hpp
 * @brief Definition of the Audio::Manager class, which manages audio recording and playback.
 */

#pragma once

#include <any>
#include <optional>

#include <portaudio.h>

#include "Logging.hpp"
#include "Recoded.hpp"
#include "Utilities.hpp"
#include "CustomExceptions.hpp"

#include "Audio/Player.hpp"
#include "Audio/Network.hpp"
#include "Audio/Recorder.hpp"
#include "Audio/Compressor.hpp"

#include "Network/Manager.hpp"
#include "Network/AddressHolder.hpp"

namespace Audio
{
    /**
     * @brief The Manager class manages audio recording and playback.
     */
    class Manager {
        public:
        /**
         * @brief Constructs a new Manager object.
         * @param duration The length of the recording in seconds.
         */
        Manager(const unsigned int duration = 5);

        /**
         * @brief Destroys the Manager object.
         */
        ~Manager();

        /**
         * @brief Sets the duration of the recording.
         * @param duration The length of the recording in seconds.
         */
        void setDuration(const unsigned int duration = 300);

        /**
         * @brief Sets the recorded audio stream.
         * @param stream The audio stream to be set.
         */
        void setRecordedStream(const std::vector<float> &stream);

        /**
         * @brief Sets the playing audio stream.
         * @param stream The audio stream to be set.
         */
        void setPlayingStream(const std::vector<float> &stream);

        /**
         * @brief Starts the recording process.
         */
        void startRecording();

        /**
         * @brief Stops the recording process.
         */
        void stopRecording();

        /**
         * @brief Starts the playback process.
         */
        void startPlaying();

        /**
         * @brief Stops the playback process.
         */
        void stopPlaying();

        /**
         * @brief Checks if recording is in progress.
         * @return True if recording is in progress, false otherwise.
         */
        const bool isRecording() const;

        /**
         * @brief Checks if playback is in progress.
         * @return True if playback is in progress, false otherwise.
         */
        const bool isPlaying() const;

        /**
         * @brief Gets the duration of the recording.
         * @return The duration of the recording in seconds.
         */
        const unsigned int getDuration() const;

        /**
         * @brief Retrieves the packet.
         * @return The packet as an std::any object.
         */
        std::optional<std::any> getPacket() const;

        /**
         * @brief Retrieves the recorded audio stream.
         * @return The recorded audio stream as a vector of floats.
         */
        const std::vector<float> getRecordedStream() const;

        /**
         * @brief Retrieves the playing audio stream.
         * @return The playing audio stream as a vector of floats.
         */
        const std::vector<float> getPlayingStream() const;

        /**
         * @brief Retrieves the compressed audio stream.
         * @return The compressed audio stream as an std::any object.
         */
        std::optional<std::any> getCompressedStream() const;

        /**
         * @brief Updates the Manager by copying another Audio::Manager.
         * @param copy The Audio::Manager to copy data from.
         */
        void update(const Audio::Manager &copy);

        /**
         * @brief Dumps the current state of the variables for debugging purposes.
         * It will dump them for itself and any of its underlying classes.
         * @param indent The level to which the class should be indented in the dump.
         * @return The formatted output.
         */
        const std::string getInfo(const unsigned int indent = 0) const;

        /**
         * @brief Overloads the assignment operator to copy from another Audio::Manager.
         * @param copy The Audio::Manager to copy data from.
         * @return A reference to the updated instance.
         */
        Manager &operator =(const Audio::Manager &copy);

        private:
        unsigned int _duration; //!< The recording length in seconds
        Audio::Player _player; //!< The audio node handling recording and playback
        Audio::Recorder _recorder; //!< The audio node handling recording and playback
    };

    /**
     * @brief Overloads the stream insertion operator for Audio::Manager.
     * @param os The output stream.
     * @param manager The Audio::Manager instance.
     * @return The output stream.
     */
    std::ostream &operator<<(std::ostream &os, const Audio::Manager &manager);
}
