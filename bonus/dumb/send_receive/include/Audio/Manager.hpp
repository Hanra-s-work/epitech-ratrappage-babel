/*
** EPITECH PROJECT, 2024
** epitech-ratrappage-babel (Workspace)
** File description:
** Manager.hpp
*/

#pragma once

#include <vector>
#include <optional>
#include <iostream>

#include <atomic>

#include <portaudio.h>

#include "Logging.hpp"
#include "Audio/Sample.hpp"

namespace Audio
{
    class Manager {
        public:
        Manager();
        Manager(const Sample &sample);
        Manager(const float durationseconds = 5, const unsigned int sampleRate = 44100, const unsigned int framesPerBuffer = 256, const unsigned int numChannels = 1);

        ~Manager();

        void initialiseSampleRecordingBuffer();
        void initialiseSampleRecordingBuffer(const Sample &sample);
        void initialiseSampleRecordingBuffer(const float durationseconds);
        void initialiseSampleRecordingBuffer(const float durationseconds, unsigned int sampleRate, unsigned int framesPerBuffer, unsigned int numChannels);

        void setSampleRecording(const Sample &sample);
        const Sample getSampleRecording() const;

        void initialiseSamplePlayingBuffer();
        void initialiseSamplePlayingBuffer(const Sample &sample);
        void initialiseSamplePlayingBuffer(const float durationseconds);
        void initialiseSamplePlayingBuffer(const float durationseconds, unsigned int sampleRate, unsigned int framesPerBuffer, unsigned int numChannels);

        void setSamplePlaying(const Sample &sample);
        const Sample getSamplePlaying() const;

        void recordSample();
        void playSample();

        const bool isRecording() const;
        const bool isPlaying() const;

        private:
        const bool _initialisePa();
        const bool _freePa();

        Sample _samplePlaying;
        Sample _sampleRecording;

        std::atomic<bool> _recording = false;
        std::atomic<bool> _playing = false;
        std::atomic<bool> _initialised = false;
    };
}
