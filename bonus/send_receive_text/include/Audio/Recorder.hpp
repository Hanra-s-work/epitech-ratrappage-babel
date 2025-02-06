/*
** EPITECH PROJECT, 2024
** record_play
** File description:
** Recorder.hpp
*/

#pragma once

#include <atomic>
#include <string>
#include <vector>
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
    class Recorder {
        public:
        Recorder();
        Recorder(const Recorder &copy);
        Recorder(const StreamData &data);
        Recorder(const unsigned int duration);

        ~Recorder();

        /**
         * @brief Sets the duration of the recording.
         * @param duration The length of the recording in seconds.
         * @throws CustomExceptions::InvalidDuration if the duration is not within the valid range.
         */
        void setDuration(const unsigned int duration);

        /**
         * @brief Sets the recorded audio samples.
         * @param samples A vector containing the recorded audio samples.
         */
        void setRecordedSamples(const std::vector<float> &samples);
        void setRecordedSamples(const StreamData &data);

        /**
         * @brief Starts the recording process.
         * @throws CustomExceptions::NoAudioStream if no audio stream is available.
         * @throws CustomExceptions::InvalidOperation if recording is already in progress.
         */
        void startRecording();

        /**
         * @brief Stops the recording process.
         * @throws CustomExceptions::InvalidOperation if recording is not in progress.
         */
        void stopRecording();

        /**
         * @brief Checks if recording is in progress.
         * @return True if recording is in progress, false otherwise.
         */
        const bool isRecording() const;

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
         * @brief Updates the Recorder by copying another Audio::Recorder.
         * @param copy The Audio::Recorder to copy data from.
         */
        void update(const Audio::Recorder &copy);

        /**
         * @brief Updates the Recorder by copying another Audio::StreamData.
         * @param copy The Audio::StreamData to copy data from.
         */
        void update(const Audio::StreamData &copy);

        /**
         * @brief Overloads the assignment operator to copy from another Audio::Recorder.
         * @param copy The Audio::Recorder to copy data from.
         * @return A reference to the updated instance.
         */
        Recorder &operator =(const Audio::Recorder &copy);

        private:

        /**
         * @brief Initializes the recorded samples buffer.
         */
        void _initializeRecordedSamples();

        /**
         * @brief Initializes the audio stream for recording.
         * @throws CustomExceptions::NoAudioStream if there is an error initializing the audio stream.
         */
        void _initializeNodeRecordingStream();

        void _recordingLoop();

        /**
         * @brief Destroys the recording stream.
         * @throws CustomExceptions::NoAudioStream if there is an error stopping or closing the audio stream.
         */
        void _destroyRecordingStream();

        /**
         * @brief Clears the recorded samples buffer.
         */
        void _destroyRecordedSamples();

        std::atomic<bool> _recording = false; //!< Indicates if recording is in progress
        std::atomic<bool> _stopThread = false; //!< Indicates if the recording thread should stop
        StreamData _recordedData; //!< The recorded audio samples
        PaError _paRecordErr; //!< PortAudio error for recording
        PaStream *_paRawStream = nullptr; //!< Raw PortAudio stream
        std::thread _recordingThread; //!< The thread for recording
    };

    /**
     * @brief Overloads the stream insertion operator for Audio::Recorder.
     * @param os The output stream.
     * @param recorder The Audio::Recorder instance.
     * @return The output stream.
     */
    std::ostream &operator<<(std::ostream &os, const Audio::Recorder &recorder);
}
