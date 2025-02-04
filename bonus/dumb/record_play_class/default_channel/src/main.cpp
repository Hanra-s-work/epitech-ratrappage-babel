/*
** EPITECH PROJECT, 2024
** epitech-ratrappage-babel (Workspace)
** File description:
** main.cpp
*/

#include <vector>
#include <optional>
#include <iostream>

#include "Audio/Manager.hpp"

const int mainLoop(Audio::Manager &instance, const unsigned int loops = 200)
{
    std::cout << "Starting main loop..." << std::endl;
    int loop = 1;

    try {
        while (loop < loops + 1) {
            std::cout << "Iteration: " << loop << std::endl;

            instance.recordSample();

            instance.setSamplePlaying(instance.getSampleRecording());

            instance.playSample();
            loop++;
        }
    }
    catch (const std::exception &e) {
        std::cerr << "Error in main loop: " << e.what() << std::endl;
        return 1;
    }
    std::cout << "Main loop ended" << std::endl;
    return 0;

}

int main()
{
    std::cout << "PortAudio record and play" << std::endl;

    Audio::Sample buffer;
    buffer.durationSeconds = 0.5;
    buffer.sampleRate = 44100;
    buffer.framesPerBuffer = 256;
    buffer.numChannelsPlayback = 1;
    buffer.numChannelsRecording = 1;

    Audio::Manager audioManager(buffer);

    if (mainLoop(audioManager, 200) != 0) {
        std::cerr << "Error in main loop, aborting program" << std::endl;
        return 84;
    }
    std::cout << "Loop ended without any issues, exiting program" << std::endl;
    return 0;
}
