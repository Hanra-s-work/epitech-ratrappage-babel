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


int main()
{
    std::cout << "PortAudio record and play" << std::endl;

    int i = 0;
    int loops = 200;

    Audio::Sample buffer;
    buffer.durationSeconds = 0.5;
    buffer.sampleRate = 44100;
    buffer.framesPerBuffer = 256;
    buffer.channelPlaying = Audio::DefaultOutputStream;
    buffer.channelRecording = Audio::DefaultInputStream;

    std::vector<Audio::Sample> audioSample;

    Audio::Manager audioManager(buffer);

    audioManager.startRecording();
    audioManager.startPlaying();


    while (i < loops) {
        std::cout << "Loop " << i << std::endl;
        audioSample = audioManager.getRecordingBuffer();
        for (int j = 0; j < audioSample.size(); j++) {
            audioManager.addSampleToPlayingBuffer(audioSample[j]);
            i++;
        }
    }

    std::cout << "Recording and playing finished" << std::endl;
    audioManager.stopRecording();
    audioManager.stopPlaying();

    std::cout << "Loop ended without any issues, exiting program" << std::endl;
    return 0;
}
