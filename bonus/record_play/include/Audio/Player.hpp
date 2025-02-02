/*
** EPITECH PROJECT, 2024
** record_play
** File description:
** Player.hpp
*/

#pragma once

#include <atomic>
#include <vector>
#include <string>
#include <thread>

#include <portaudio.h>

#include "Logging.hpp"
#include "Recoded.hpp"
#include "Constants.hpp"
#include "Utilities.hpp"
#include "CustomExceptions.hpp"
#include "Audio/StreamData.hpp"

namespace Audio
{
    class Player {
        public:
        Player();
        Player(const Player &copy);
        Player(const StreamData &data);

        ~Player();

        /**
         * @brief Sets the recorded audio samples.
         * @param samples A vector containing the recorded audio samples.
         */
        void setRecordedSamples(const std::vector<float> &samples);
        void setRecordedSamples(const StreamData &data);

        /**
         * @brief Sets the duration of the recording.
         * @param duration The duration of the recording in seconds.
         */
        void setDuration(const unsigned int duration);

        /**
         * @brief Starts the playback process.
         * @throws CustomExceptions::NoAudioStream if no audio stream is available.
         * @throws CustomExceptions::InvalidOperation if playback is already in progress.
         */
        void startPlaying();

        /**
         * @brief Stops the playback process.
         * @throws CustomExceptions::InvalidOperation if playback is not in progress.
         */
        void stopPlaying();

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
         * @brief Retrieves the recorded audio samples.
         * @return A vector containing the recorded audio samples.
         */
        const std::vector<float> getRecordedSamples() const;
        const StreamData getRecordedData() const;

        /**
         * @brief Dumps the current state of the variables for debugging purposes.
         * @param indent The level to which the class should be indented in the dump.
         * @return The formatted output.
         */
        const std::string getInfo(const unsigned int indent = 0) const;

        /**
         * @brief Updates the Player by copying another Audio::Player.
         * @param copy The Audio::Player to copy data from.
         */
        void update(const Audio::Player &copy);

        /**
         * @brief Updates the Player by copying another Audio::StreamData.
         * @param copy The Audio::StreamData to copy data from.
         */
        void update(const Audio::StreamData &copy);

        /**
         * @brief Overloads the assignment operator to copy from another Audio::Player.
         * @param copy The Audio::Player to copy data from.
         * @return A reference to the updated instance.
         */
        Player &operator =(const Audio::Player &copy);

        private:

        /**
         * @brief Initializes the recorded samples buffer.
         */
        void _initializeRecordedSamples();

        /**
         * @brief Initializes the audio stream for playback.
         * @throws CustomExceptions::NoAudioStream if there is an error initializing the audio stream.
         */
        void _initializeNodePlaybackStream();

        /**
         * @brief Starts the playback process.
         * @throws CustomExceptions::NoAudioStream if there is an error starting the audio stream.
         */
        void _startPlaying();

        /**
         * @brief Destroys the playback stream.
         * @throws CustomExceptions::NoAudioStream if there is an error stopping or closing the audio stream.
         */
        void _destroyNodePlaybackStream();

        /**
         * @brief Clears the recorded samples buffer.
         */
        void _destroyRecordedSamples();

        std::atomic<bool> _playing = false; //!< Indicates if playback is in progress
        PaError _paPlayErr; //!< PortAudio error for playback
        PaStreamParameters _outputParameters; //!< Output parameters for playback
        PaStream *_paRawStream = nullptr; //!< Raw PortAudio stream
        StreamData _recordedData; //!< The recorded audio samples

        std::thread _playbackThread; //!< The thread for playback
    };

    /**
     * @brief Overloads the stream insertion operator for Audio::Player.
     * @param os The output stream.
     * @param player The Audio::Player instance.
     * @return The output stream.
     */
    std::ostream &operator<<(std::ostream &os, const Audio::Player &player);
}
