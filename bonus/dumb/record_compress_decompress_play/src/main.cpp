/*
** EPITECH PROJECT, 2024
** epitech-ratrappage-babel (Workspace)
** File description:
** main.cpp
*/

#include <vector>
#include <optional>
#include <iostream>

#include "Audio.hpp"
#include "Logging.hpp"
#include "Constants.hpp"
#include "Compressor.hpp"
#include "CustomExceptions.hpp"

const Audio::Manager initialiseAudioManager(const Audio::Sample &sample)
{
    try {
        return Audio::Manager(sample);
    }
    catch (const std::exception &e) {
        std::cerr << "Error in audio manager: " << e.what() << std::endl;
        throw CustomExceptions::InitialisationFailed("Error in audio manager");
    }
}

const Compressor::Manager initialiseCompressionManager(const Audio::Sample &sample)
{
    try {
        // return Compressor::Manager(sample);
        return Compressor::Manager();
    }
    catch (const std::exception &e) {
        std::cerr << "Error in compression manager: " << e.what() << std::endl;
        throw CustomExceptions::InitialisationFailed("Error in compression manager");
    }
}

const int mainLoop(Audio::Manager &aInstance, Compressor::Manager &cInstance, const unsigned int loops = 200)
{
    COLOUR_INFO << "Starting main loop..." << std::endl;
    int loop = 1;
    Audio::Sample sample;

    Compressor::Packet compressedStream;

    try {
        while (loop < loops + 1) {
            COLOUR_INFO << "Iteration: " << loop << std::endl;

            COLOUR_DEBUG << "Recording sample..." << std::endl;
            aInstance.recordSample();

            COLOUR_DEBUG << "Fetching sample..." << std::endl;
            sample = aInstance.getSampleRecording();

            COLOUR_DEBUG << "Setting the sample to be compressed..." << std::endl;
            cInstance.setUncompressedStream(sample);

            COLOUR_DEBUG << "Compressing the sample..." << std::endl;
            cInstance.compress();

            COLOUR_DEBUG << "Fetching the compressed stream..." << std::endl;
            compressedStream = cInstance.getCompressedStream();

            COLOUR_DEBUG << "Setting the compressed stream to be decompressed..." << std::endl;
            cInstance.setCompressedStream(compressedStream);

            COLOUR_DEBUG << "Decompressing the sample..." << std::endl;
            cInstance.decompress();

            COLOUR_DEBUG << "Fetching the decompressed stream..." << std::endl;
            sample = cInstance.getUncompressedStream();

            COLOUR_DEBUG << "Setting the sample to be played..." << std::endl;
            aInstance.setSamplePlaying(sample);

            COLOUR_DEBUG << "Playing the sample..." << std::endl;
            aInstance.playSample();

            COLOUR_SUCCESS << "Iteration " << loop << " ended" << std::endl;
            loop++;
        }
    }
    catch (const std::exception &e) {
        std::cerr << "Error in main loop: " << e.what() << std::endl;
        return 1;
    }
    COLOUR_SUCCESS << "Main loop ended" << std::endl;
    return 0;

}

int main()
{
    std::cout << "PortAudio record and play" << std::endl;

    // Set the logging status
    Logging::Log::getInstance().setLogEnabled(true);
    Logging::Log::getInstance().setDebugEnabled(true);

    Audio::Sample buffer;
    buffer.durationSeconds = 0.5;
    buffer.sampleRate = 48000;
    buffer.framesPerBuffer = 256;
    buffer.numChannelsPlayback = 1;
    buffer.numChannelsRecording = 1;

    PRETTY_INFO << "Initialising the audio manager..." << std::endl;
    try {
        Audio::Manager audioManager = initialiseAudioManager(buffer);
        Compressor::Manager compressorManager = initialiseCompressionManager(buffer);
        PRETTY_INFO << "Audio manager initialised" << std::endl;

        PRETTY_INFO << "Starting mainloop" << std::endl;
        if (mainLoop(audioManager, compressorManager, 200) != 0) {
            std::cerr << "Error in main loop, aborting program" << std::endl;
            return PROGRAM_ERROR;
        }
        PRETTY_SUCCESS << "Main loop ended without any issues, exiting program" << std::endl;
        std::cout << "Loop ended without any issues, exiting program" << std::endl;
        return PROGRAM_SUCCESS;
    }
    catch (const std::exception &e) {
        PRECISE_ERROR << "Error in main: " << e.what() << std::endl;
        std::cerr << "Error in main: " << e.what() << std::endl;
        return PROGRAM_ERROR;
    }
}
