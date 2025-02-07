/*
** EPITECH PROJECT, 2024
** epitech-ratrappage-babel (Workspace)
** File description:
** main.cpp
*/

#include "Logging.hpp"
#include "Constants.hpp"
#include "Audio/Audio.hpp"
#include "Compressor/Manager.hpp"

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

    // Set the logging status
    Logging::Log::getInstance().setLogEnabled(log);
    Logging::Log::getInstance().setDebugEnabled(debug);

    PRETTY_INFO << "Starting the program" << std::endl;
    unsigned int rounds = 0;
    unsigned int maxRounds = 200;
    std::vector<float> sound;
    std::vector<unsigned char> compressedSound;
    try {
        PortAudio audio;
        Compressor::Manager myManager;
        audio.record();
        audio.play();
        while (rounds < maxRounds) {
            PRETTY_INFO << "Round " << rounds << std::endl;
            audio.getSound(sound, 480);
            PRETTY_INFO << "Compressing" << std::endl;
            myManager.encode(sound, compressedSound);
            PRETTY_INFO << "Decompressing" << std::endl;
            PRETTY_INFO << "compressedSound size: " << compressedSound.size() << std::endl;
            PRETTY_INFO << "compressed sound data: " << compressedSound << std::endl;
            myManager.decode(compressedSound, sound);
            audio.setPlaySound(sound);
            PRETTY_INFO << "Round end " << rounds << std::endl;
            PRETTY_INFO << "Clearing sound buffer and compressed buffer" << std::endl;
            sound.clear();
            compressedSound.clear();
            PRETTY_INFO << "Sound buffer and compressed buffer cleared" << std::endl;
            rounds++;
        }
        audio.stopRecord();
        audio.stopPlay();
    }
    catch (const std::exception &e) {
        PRETTY_ERROR << e.what() << std::endl;
        return PROGRAM_ERROR;
    }
    return PROGRAM_SUCCESS;
}
