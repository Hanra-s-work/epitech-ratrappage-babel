/*
** EPITECH PROJECT, 2024
** epitech-ratrappage-babel (Workspace)
** File description:
** main.cpp
*/

#include <vector>
#include <optional>
#include <iostream>
#include <portaudio.h>

// Defining the sample rate and number of frames to capture
const int SAMPLE_RATE = 44100;
const int FRAMES_PER_BUFFER = 256;
const int NUM_CHANNELS = 1;
const int NUM_SECONDS = 5;
// const float NUM_SECONDS = 1;

const bool initialisePa()
{
    std::cout << "Initializing PortAudio..." << std::endl;
    PaError err = Pa_Initialize();
    if (err != paNoError) {
        std::cerr << "PortAudio initialization error: " << Pa_GetErrorText(err) << std::endl;
        return false;
    }
    std::cout << "PortAudio initialized" << std::endl;
    return true;
}

const bool freePa()
{
    std::cout << "Terminating PortAudio..." << std::endl;
    PaError err = Pa_Terminate();
    if (err != paNoError) {
        std::cerr << "PortAudio termination error: " << Pa_GetErrorText(err) << std::endl;
        return false;
    }
    std::cout << "PortAudio terminated" << std::endl;
    return true;
}

const std::vector<float> initialiseSampleBuffer()
{
    std::cout << "Initialising sample buffer..." << std::endl;
    std::vector<float> sampleBuffer(SAMPLE_RATE * NUM_SECONDS);
    std::cout << "Sample buffer initialised" << std::endl;
    return sampleBuffer;
}

const std::optional<std::vector<float>> recordSample(std::vector<float> &sampleBuffer)
{
    std::cout << "Recording audio..." << std::endl;
    PaError err;
    PaStream *stream;

    err = Pa_OpenDefaultStream(&stream,
        NUM_CHANNELS,       // Input channels
        0,                  // No Output channels for recording
        paFloat32,          // Sample format
        SAMPLE_RATE,        // Sample rate
        FRAMES_PER_BUFFER,  // Frames per buffer
        nullptr,            // Input callback (null for simple read/write)
        nullptr             // User data (here is null)
    );                      // Output callback (null for simple read/write)

    if (err != paNoError) {
        std::cerr << "PortAudio stream open error: " << Pa_GetErrorText(err) << std::endl;
        return std::nullopt;
    }

    // Starting the stream
    err = Pa_StartStream(stream);
    if (err != paNoError) {
        std::cerr << "PortAudio stream start error: " << Pa_GetErrorText(err) << std::endl;
        return std::nullopt;
    }

    std::cout << "Recording for " << NUM_SECONDS << " seconds..." << std::endl;

    // Recording audio
    err = Pa_ReadStream(stream, sampleBuffer.data(), sampleBuffer.size() / NUM_CHANNELS);
    if (err != paNoError) {
        std::cerr << "PortAudio read stream error: " << Pa_GetErrorText(err) << std::endl;
        return std::nullopt;
    }

    // Stoping the stream
    err = Pa_StopStream(stream);
    if (err != paNoError) {
        std::cerr << "PortAudio stop stream error: " << Pa_GetErrorText(err) << std::endl;
    }

    // Closing the stream
    err = Pa_CloseStream(stream);
    if (err != paNoError) {
        std::cerr << "PortAudio close stream error: " << Pa_GetErrorText(err) << std::endl;
    }

    std::cout << "Audio recorded" << std::endl;

    return std::make_optional(sampleBuffer);
}

const int play_sample(std::vector<float> &sampleBuffer)
{
    std::cout << "Playing audio..." << std::endl;
    PaError err;
    PaStream *stream;

    err = Pa_OpenDefaultStream(&stream,
        0,                  // No Input channels required
        NUM_CHANNELS,       // Output channels
        paFloat32,          // Sample format
        SAMPLE_RATE,        // Sample rate
        FRAMES_PER_BUFFER,  // Frames per buffer
        nullptr,            // Input callback (null for simple read/write)
        nullptr             // User data (here is null)
    );                      // Output callback (null for simple read/write)

    if (err != paNoError) {
        std::cerr << "PortAudio stream open error: " << Pa_GetErrorText(err) << std::endl;
        return 1;
    }

    err = Pa_StartStream(stream);
    if (err != paNoError) {
        std::cerr << "PortAudio stream start error: " << Pa_GetErrorText(err) << std::endl;
        return 1;
    }

    err = Pa_WriteStream(stream, sampleBuffer.data(), sampleBuffer.size() / NUM_CHANNELS);
    if (err != paNoError) {
        std::cerr << "PortAudio write stream error: " << Pa_GetErrorText(err) << std::endl;
        return 1;
    }

    // Stoping the stream
    err = Pa_StopStream(stream);
    if (err != paNoError) {
        std::cerr << "PortAudio stop stream error: " << Pa_GetErrorText(err) << std::endl;
        // return 1;
    }

    // Closing the stream
    err = Pa_CloseStream(stream);
    if (err != paNoError) {
        std::cerr << "PortAudio close stream error: " << Pa_GetErrorText(err) << std::endl;
        // return 1;
    }
    std::cout << "Audio played" << std::endl;
    return 0;
}

const int mainLoop(const int &loops = 200)
{
    std::cout << "Starting main loop..." << std::endl;
    int loop = 0;

    while (loop < loops) {
        loop++;
        std::cout << "Iteration: " << loop << std::endl;

        std::vector<float> recordedSamples = initialiseSampleBuffer(); // Storing the recorded samples

        // Initialize PortAudio
        std::optional<std::vector<float>> sampleBuffer = recordSample(recordedSamples);

        if (!sampleBuffer.has_value()) {
            std::cerr << "Error in recording" << std::endl;
            return 1;
        }

        std::cout << "Playback recorded audio..." << std::endl;
        if (play_sample(sampleBuffer.value()) != 0) {
            std::cerr << "Error in playing" << std::endl;
            return 1;
        };

    }
    std::cout << "Main loop ended" << std::endl;
    return 0;

}

int main()
{
    std::cout << "PortAudio record and play" << std::endl;
    if (!initialisePa()) {
        std::cerr << "PortAudio initialization error" << std::endl;
        return 1;
    }

    if (mainLoop(200) != 0) {
        std::cerr << "Error in main loop" << std::endl;
        freePa();
        return 1;
    }

    std::cout << "Freeing Pa" << std::endl;
    if (!freePa()) {
        std::cerr << "PortAudio termination error" << std::endl;
        return 1;
    }
    std::cout << "PortAudio terminated" << std::endl;
    return 0;
}
