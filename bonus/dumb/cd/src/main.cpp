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

const int mainLoop(Audio::Manager &aInstance, Compressor::Manager &cInstance, const unsigned int loops = 200)
//}, Network::TCP &tInstance, Network::UDP &uInstance)
{
    COLOUR_INFO << "Starting main loop..." << std::endl;
    int loop = 1;

    asio::io_context io_context;

    Audio::Sample sample;

    Compressor::Packet compressedStream;

    int maxFrameSize = 480;

    std::vector<float> uncompressed;
    std::vector<float> uncompresssedChunk;
    std::vector<unsigned char> compressed;

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

            uncompressed = sample.sample;
            for (int chunk = 0; chunk < uncompressed.size(); chunk += maxFrameSize) {}
            if (uncompressed.empty()) {
                PRETTY_WARNING << "Uncompressed sample is empty" << std::endl;
                return 1;
            }

            if (uncompressed.size() > maxFrameSize) {
                PRETTY_WARNING << "Uncompressed sample is too big, size is: " << uncompressed.size() << ", reducing" << std::endl;
                for (int i = 0; i < maxFrameSize; i++) {
                    uncompressed.push_back(uncompressed[i]);
                }
                PRETTY_INFO << "Uncompressed sample size: " << uncompressed.size() << std::endl;
            }

            cInstance.encode(uncompressed, compressed);

            // COLOUR_DEBUG << "Fetching the compressed stream..." << std::endl;
            // compressedStream = cInstance.getCompressedStream();

            PRETTY_INFO << "Sending the compressed stream..." << std::endl;

            // tInstance.sendTo(compressedStream);
            // uInstance.sendTo(compressedStream);
            // tInstance.sendTo("Hello");
            // uInstance.sendTo("Hello", "127.0.0.1", 8080);

            // COLOUR_DEBUG << "Setting the compressed stream to be decompressed..." << std::endl;
            // cInstance.setCompressedStream(compressedStream);

            // COLOUR_DEBUG << "Decompressing the sample..." << std::endl;
            // cInstance.decompress();

            cInstance.decode(compressed, uncompressed);
            sample.sample = uncompressed;

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

int main(int argc, char **argv)
{
    bool defaultDebug = false;
    bool defaultLog = false;
    bool defaultSenderMode = true;
    int defaultPort = 9000;
    std::string defaultIp = "0.0.0.0";
    int port = defaultPort;
    bool is_sender = defaultSenderMode;
    std::string ip = defaultIp;
    bool log = defaultLog;
    bool debug = defaultDebug;
    if (argc > 0) {
        for (int i = 0; i < argc; i++) {
            std::string arg = std::string(argv[i]);
            if (arg == "-p") {
                port = std::stoi(argv[i + 1]);
                if (i + 1 < argc) {
                    i++;
                }
                continue;
            }
            if (arg == "-i") {
                ip = argv[i + 1];
                if (i + 1 < argc) {
                    i++;
                }
                continue;
            }
            if (arg == "-r") {
                is_sender = false;
                continue;
            }
            if (arg == "-s") {
                is_sender = true;
                continue;
            }
            if (arg == "-d") {
                debug = true;
                continue;
            }
            if (arg == "-l") {
                log = true;
                continue;
            }
            if (arg == "-h" || arg == "--help") {
                std::cout << "USAGE:\n";
                std::cout << std::string(argv[0]) << " -p <port> -i <ip>[-r <receiver> | -s <sender>]\n";
                std::cout << "\n";
                std::cout << "OPTIONS:\n";
                std::cout << "-p <port> : Set the port to connect to (default: " << defaultPort << ")\n";
                std::cout << "-i <ip> : Set the ip to connect to (default: " << defaultIp << ")\n";
                std::cout << "-r <receiver> : Set the client to receiver mode (default: " << Recoded::myToString(!defaultSenderMode) << "\n";
                std::cout << "-s <sender> : Set the client to sender mode (default: " << Recoded::myToString(defaultSenderMode) << ")\n";
                std::cout << "-d : Enable debug mode (default: " << Recoded::myToString(defaultDebug) << ")\n";
                std::cout << "-l : Enable log mode (default: " << Recoded::myToString(defaultLog) << ")\n";
                std::cout << "\n";
                std::cout << "AUTHOR:\n";
                std::cout << "Written by: Henry Letellier\n";
                std::cout << "Epitech student 2025\n";
                std::cout << "\n" << std::flush;
                return PROGRAM_SUCCESS;
            }
            std::cout << "Invalid argument, use -h for help" << std::endl;
            std::cout << "The argument you provided was: " << argv[i] << std::endl;
        }
    }
    std::cout << "PortAudio record and play" << std::endl;

    asio::io_context io_context;

    // Set the logging status
    Logging::Log::getInstance().setLogEnabled(log);
    Logging::Log::getInstance().setDebugEnabled(debug);

    Audio::Sample buffer;
    buffer.durationSeconds = 0.5;
    buffer.sampleRate = 48000;
    // buffer.framesPerBuffer = 256;
    buffer.framesPerBuffer = 480;
    buffer.numChannelsPlayback = 1;
    buffer.numChannelsRecording = 1;

    PRETTY_INFO << "Initialising the audio manager..." << std::endl;
    try {
        Audio::Manager audioManager = initialiseAudioManager(buffer);
        Compressor::Manager compressorManager = initialiseCompressionManager(buffer);
        PRETTY_INFO << "Audio manager initialised" << std::endl;

        // PRETTY_INFO << "Initialising the TCP manager..." << std::endl;
        // Network::TCP tcpClient(io_context, ip, port, is_sender);

        // PRETTY_INFO << "Initialising the UDP manager..." << std::endl;
        // Network::UDP udpClient(io_context, ip, port, is_sender);

        // std::thread ioThread([&io_context]() {io_context.run();});


        PRETTY_INFO << "Starting mainloop" << std::endl;
        if (mainLoop(audioManager, compressorManager, 200) != 0) { //, tcpClient, udpClient, 200) != 0) {
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
