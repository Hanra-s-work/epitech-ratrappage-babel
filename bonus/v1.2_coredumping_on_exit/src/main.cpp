/*
** EPITECH PROJECT, 2024
** epitech-ratrappage-babel (Workspace)
** File description:
** main.cpp
*/

/**
 * @file main.cpp
 *
 * @brief File containing the main function for the program.
 */

#include "Logging.hpp"
#include "Network.hpp"
#include "Controls.hpp"
#include "Constants.hpp"
#include "BootScreen.hpp"
#include "Audio/Audio.hpp"
#include "Compressor/Manager.hpp"

 /**
  * @brief Main function of the program.
  *
  * This function initializes the program, processes command-line arguments,
  * and starts the main loop for sending or receiving audio data.
  *
  * @param argc Number of command-line arguments.
  * @param argv Array of command-line arguments.
  * @return int Program exit status.
  */
int main(int argc, char **argv)
{
    // Start the boot screen class
    BootScreen BootScreen;
    // Start the user control options
    Controls::ThreadCapsule myCapsule;
    // Set the default values for the flags
    bool defaultDebug = false;
    bool defaultLog = false;
    bool defaultSenderMode = true;
    unsigned int DefaultLoopLimit = 0;
    int defaultPort = 9000;
    std::string defaultIp = "0.0.0.0";
    // Set the values for the flags
    int port = defaultPort;
    bool is_sender = defaultSenderMode;
    std::string ip = defaultIp;
    bool log = defaultLog;
    bool debug = defaultDebug;
    unsigned int maxRounds = DefaultLoopLimit;
    // Check the arguments if present
    for (int i = 1; i < argc; i++) {
        std::string arg = std::string(argv[i]);
        if (arg == "-p") {
            if (i + 1 < argc) {
                port = std::stoi(argv[i + 1]);
                i++;
            } else {
                std::cout << "Missing argument parameter, use -h for help" << std::endl;
            }
        } else if (arg == "-i") {
            if (i + 1 < argc) {
                ip = argv[i + 1];
                i++;
            } else {
                std::cout << "Missing argument parameter, use -h for help" << std::endl;
            }
        } else if (arg == "-r") {
            is_sender = false;
        } else if (arg == "-s") {
            is_sender = true;
        } else if (arg == "-d") {
            debug = true;
        } else if (arg == "-l") {
            log = true;
        } else if (arg == "-m") {
            if (i + 1 < argc) {
                maxRounds = std::stoi(argv[i + 1]);
                i++;
            } else {
                std::cout << "Missing argument parameter, use -h for help" << std::endl;
            }
        } else if (arg == "-e") {
            myCapsule.setEcho(true);
        } else if (arg == "-a") {
            BootScreen.displayAllScreens();
            return PROGRAM_SUCCESS;
        } else if (arg == "-h" || arg == "--help") {
            std::cout << "USAGE:\n";
            std::cout << std::string(argv[0]) << " -p <port> -i <ip> [-r <receiver> | -s <sender>] -d -l\n";
            std::cout << "\n";
            std::cout << "OPTIONS:\n";
            std::cout << "-p <port> : Set the port to connect to (default: " << defaultPort << ")\n";
            std::cout << "-i <ip> : Set the ip to connect to (default: " << defaultIp << ")\n";
            std::cout << "-r <receiver> : Set the client to receiver mode (default: " << Recoded::myToString(!defaultSenderMode) << "\n";
            std::cout << "-s <sender> : Set the client to sender mode (default: " << Recoded::myToString(defaultSenderMode) << ")\n";
            std::cout << "-d : Enable debug mode (default: " << Recoded::myToString(defaultDebug) << ")\n";
            std::cout << "-l : Enable log mode (default: " << Recoded::myToString(defaultLog) << ")\n";
            std::cout << "-m <maxRounds> : Set the maximum number of rounds, 0 = endless (default: " << DefaultLoopLimit << ")\n";
            std::cout << "-e : Enable echo mode for the user prompt (default: false)\n";
            std::cout << "-a : Display all boot screens (Epilepsy warning, all the" << Recoded::myToString(BootScreen.getAvailableScreens()) << "logos will be displayed one after the other without any delay, meaning they will come out as fast as you terminal can diplay them)\n";
            std::cout << "\n";
            std::cout << "VERSION:\n";
            std::cout << "The program's version is: " << VERSION << std::endl;
            std::cout << "\n";
            std::cout << "AUTHOR:\n";
            std::cout << "Written by:";
            std::cout << "\t-\tHenry Letellier              : https://github.com/HenraL\n";
            std::cout << "Epitech student 2025\n";
            std::cout << "\n" << std::flush;
            return PROGRAM_SUCCESS;
        } else {
            std::cout << "Invalid argument, use -h for help" << std::endl;
            std::cout << "The argument you provided was: " << argv[i] << std::endl;
        }
    }

    // Set the logging status
    Logging::Log::getInstance().setLogEnabled(log);
    Logging::Log::getInstance().setDebugEnabled(debug);

    PRETTY_INFO << "Starting the program" << std::endl;

    // Initialised asio
    asio::io_context io_context;

    // Set the end message
    const std::string endMessage = "END";

    char usrC = ' ';
    unsigned int rounds = 0;
    bool continueRunning = true;
    std::vector<float> sound;
    std::vector<unsigned char> compressedSound;
    try {
        PortAudio audio;
        Compressor::Manager myManager;
        Network::UDP myUDP(io_context, ip, port, is_sender);
        BootScreen.display();
        // if (is_sender) {
        audio.record();
        myCapsule.startThread();
        // } else {
        audio.play();
        // }

        while ((rounds < maxRounds || maxRounds == 0) && continueRunning == true && myUDP.isConnectionAlive()) {
            if (is_sender) {
                if (myCapsule.hangUpTheCall()) {
                    PRETTY_INFO << "Haging up the call" << std::endl;
                    continueRunning = false;
                    PRETTY_INFO << "Sending end message" << std::endl;
                    std::cout << "Sending end message" << std::endl;
                    myUDP.sendRaw(endMessage.c_str(), endMessage.size(), ip, port);
                    break;
                }
                PRETTY_INFO << "Round " << rounds << std::endl;
                audio.getSound(sound, 480);
                PRETTY_INFO << "Compressing" << std::endl;
                myManager.encode(sound, compressedSound);
                PRETTY_INFO << "Decompressing" << std::endl;
                PRETTY_INFO << "compressedSound size: " << compressedSound.size() << std::endl;
                PRETTY_DEBUG << "compressed sound data: " << compressedSound << std::endl;
                myUDP.sendRaw(reinterpret_cast<const char *>(compressedSound.data()), compressedSound.size(), ip, port);
            } else {
                std::string receivedData = myUDP.receiveFrom(ip, port);
                if (receivedData == "END") {
                    std::cout << "Received end message, ending program" << std::endl;
                    continueRunning = false;
                    myCapsule.hangUpTheCall();
                    break;
                }
                PRETTY_INFO << "Received data size: " << receivedData.size() << std::endl;
                PRETTY_INFO << "Received data: " << receivedData << std::endl;
                for (int i = 0; i < receivedData.size(); i++) {
                    compressedSound.push_back(receivedData[i]);
                }
                PRETTY_INFO << "compressed sound data: " << compressedSound << std::endl;
                myManager.decode(compressedSound, sound);
                audio.setPlaySound(sound);
            }
            PRETTY_INFO << "Round end " << rounds << std::endl;
            PRETTY_INFO << "Clearing sound buffer and compressed buffer" << std::endl;
            sound.clear();
            compressedSound.clear();
            PRETTY_INFO << "Sound buffer and compressed buffer cleared" << std::endl;
            rounds++;
        }
        // if (is_sender) {
        audio.stopRecord();
        PRETTY_INFO << "Sending end message" << std::endl;
        myUDP.sendRaw(endMessage.c_str(), endMessage.size(), ip, port);
        // } else {
        audio.stopPlay();
        // }
        // if (myCapsule.isRunning()) {
        //     try {
        //         myCapsule.stopThread();
        //     }
        //     catch (const CustomExceptions::ThreadFound &e) {
        //         PRETTY_WARNING << e.what() << std::endl;
        //     }
        //     catch (...) {
        //         PRETTY_ERROR << "The thread stopping did not happen in a clean manner" << std::endl;
        //     }
        // }
        PRETTY_SUCCESS << "Program ended successfully" << std::endl;
        std::cout << "Program ended successfully" << std::endl;
    }
    catch (const std::exception &e) {
        std::cerr << "An error occurred: " << e.what() << std::endl;
        PRETTY_ERROR << e.what() << std::endl;
        return PROGRAM_ERROR;
    }
    return PROGRAM_SUCCESS;
}
