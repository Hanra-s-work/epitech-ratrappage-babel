/*
** EPITECH PROJECT, 2024
** epitech-ratrappage-babel (Workspace)
** File description:
** Manager.hpp
*/

#pragma once

#include <mutex>
#include <deque>
#include <thread>
#include <vector>
#include <optional>
#include <iostream>
#include <condition_variable>

#include <atomic>

#include <portaudio.h>

namespace Audio
{

    struct AStream {
        PaDeviceIndex device;
        int channelCount;
        PaSampleFormat sampleFormat;
        double suggestedLatency;
        void *hostApiSpecificStreamInfo;
    };

    typedef struct AStream InputStream;
    typedef struct AStream OutputStream;

    const InputStream getDefaultInputStream();

    const OutputStream getDefaultOutputStream();

    static const InputStream DefaultInputStream = getDefaultInputStream();

    static const OutputStream DefaultOutputStream = getDefaultOutputStream();

    struct Sample {
        bool initialised = false;
        std::vector<float> sample;
        float durationSeconds = 1;
        double sampleRate = 44100;
        unsigned long int framesPerBuffer = 256;
        InputStream channelRecording = DefaultInputStream;
        OutputStream channelPlaying = DefaultOutputStream;
    };

    class Manager {
        public:
        Manager();
        Manager(const Sample &sample);
        Manager(const float durationseconds = 5, const unsigned int sampleRate = 44100, const unsigned int framesPerBuffer = 256, const InputStream &input = DefaultInputStream, const OutputStream &output = DefaultOutputStream);

        ~Manager();

        void initialiseSampleRecordingBuffer();
        void initialiseSampleRecordingBuffer(const Sample &sample);
        void initialiseSampleRecordingBuffer(const float durationseconds);
        void initialiseSampleRecordingBuffer(const float durationseconds, const unsigned int sampleRate, const unsigned int framesPerBuffer, const InputStream &input, const OutputStream &output);

        const Sample initialiseSampleRecordingBufferNode(const Sample &sample);

        void setSampleRecording(const Sample &sample);
        const Sample getSampleRecording() const;

        void initialiseSamplePlayingBuffer();
        void initialiseSamplePlayingBuffer(const Sample &sample);
        void initialiseSamplePlayingBuffer(const float durationseconds);
        void initialiseSamplePlayingBuffer(const float durationseconds, const unsigned int sampleRate, const unsigned int framesPerBuffer, const InputStream &input, const OutputStream &output);

        const Sample initialiseSamplePlayingBufferNode(const Sample &sample);

        void setSamplePlaying(const Sample &sample);
        const Sample getSamplePlaying() const;

        void startRecording();
        void pauseRecording();
        void resumeRecording();
        void stopRecording();
        void clearRecordingBuffer();

        void startPlaying();
        void pausePlaying();
        void resumePlaying();
        void stopPlaying();
        void clearPlayingBuffer();

        void addSampleToPlayingBuffer(const Sample &sample);

        const std::vector<Sample> getRecordingBuffer();

        const bool isRecording() const;
        const bool isPlaying() const;

        private:
        const bool _initialisePa();
        const bool _freePa();

        void _continuouslyRecord();

        const std::optional<Sample> _recordChunk();

        void _continuouslyPlay();

        void _playChunk(const Sample &sample);

        const PaStreamParameters _toPaStreamParameters(const AStream &sample) const;
        // const PaStreamParameters _toPaStreamParameters(const InputStream &sample) const;
        // const PaStreamParameters _toPaStreamParameters(const OutputStream &sample) const;

        Sample _samplePlaying;
        Sample _sampleRecording;

        std::mutex _recordingMutex;
        std::vector<Sample> _recordingBuffer;

        std::mutex _playingMutex;
        std::deque<Sample> _playingBuffer;


        std::atomic<bool> _recording = false;
        std::atomic<bool> _recordingPaused = false;
        std::atomic<unsigned int> _recordPauseCheckDelay = 100;
        std::condition_variable _recorderNotifier;

        std::atomic<bool> _playing = false;
        std::atomic<bool> _playingPaused = false;
        std::atomic<unsigned int> _playPauseCheckDelay = 100;
        std::condition_variable _playerNotifier;

        std::atomic<bool> _initialised = false;

        std::thread _recordingThread;
        std::thread _playingThread;
    };
}
