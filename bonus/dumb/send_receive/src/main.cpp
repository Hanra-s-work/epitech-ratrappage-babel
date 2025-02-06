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
#include "Network.hpp"
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

const Network::TCP initialiseTCPManager(asio::io_context &io_context, const std::string &ip, int port, bool is_sender)
{
    try {
        return Network::TCP(io_context, ip, port, is_sender);
    }
    catch (const std::exception &e) {
        std::cerr << "Error in TCP manager: " << e.what() << std::endl;
        throw CustomExceptions::InitialisationFailed("Error in TCP manager");
    }
}

const int mainLoop(Audio::Manager &aInstance, Compressor::Manager &cInstance, Network::TCP &tInstance, Network::UDP &uInstance, const unsigned int loops = 200)
{
    COLOUR_INFO << "Starting main loop..." << std::endl;
    int loop = 1;

    asio::io_context io_context;

    Audio::Sample sample;

    Compressor::Packet compressedStream;

    try {
        while (loop < loops + 1) {
            COLOUR_INFO << "Iteration: " << loop << std::endl;

            COLOUR_DEBUG << "Recording sample..." << std::endl;
            aInstance.recordSample();

            COLOUR_DEBUG << "Fetching sample..." << std::endl;
            sample = aInstance.getSampleRecording();

            // COLOUR_DEBUG << "Setting the sample to be compressed..." << std::endl;
            // cInstance.setUncompressedStream(sample);

            // COLOUR_DEBUG << "Compressing the sample..." << std::endl;
            // cInstance.compress();

            // COLOUR_DEBUG << "Fetching the compressed stream..." << std::endl;
            // compressedStream = cInstance.getCompressedStream();

            PRETTY_INFO << "Sending the compressed stream..." << std::endl;

            // tInstance.sendTo(compressedStream);
            // uInstance.sendTo(compressedStream);
            tInstance.sendTo("Hello");
            uInstance.sendTo("Hello", "127.0.0.1", 8080);

            // COLOUR_DEBUG << "Setting the compressed stream to be decompressed..." << std::endl;
            // cInstance.setCompressedStream(compressedStream);

            // COLOUR_DEBUG << "Decompressing the sample..." << std::endl;
            // cInstance.decompress();

            // COLOUR_DEBUG << "Fetching the decompressed stream..." << std::endl;
            // sample = cInstance.getUncompressedStream();

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

    asio::io_context io_context;

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

        PRETTY_INFO << "Initialising the TCP manager..." << std::endl;
        Network::TCP tcpClient(io_context, "127.0.0.1", 8080, true); // Assuming this is your TCP class

        PRETTY_INFO << "Initialising the UDP manager..." << std::endl;
        Network::UDP udpClient(io_context, "127.0.0.1", 9090, true); // Assuming this is your UDP class

        std::thread ioThread([&io_context]() {io_context.run();});


        PRETTY_INFO << "Starting mainloop" << std::endl;
        if (mainLoop(audioManager, compressorManager, tcpClient, udpClient, 200) != 0) {
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
