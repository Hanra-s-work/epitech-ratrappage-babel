#include <iostream>
#include <vector>
#include <portaudio.h>

// Defining the sample rate and number of frames to capture
const int SAMPLE_RATE = 44100;
const int FRAMES_PER_BUFFER = 256;
const int NUM_CHANNELS = 1;
const int NUM_SECONDS = 5;

int main()
{
    PaError err;

    // Initialize PortAudio
    err = Pa_Initialize();
    if (err != paNoError) {
        std::cerr << "PortAudio initialization error: " << Pa_GetErrorText(err) << std::endl;
        return 1;
    }

    // Set up stream parameters
    PaStream *stream;
    std::vector<float> recordedSamples(SAMPLE_RATE * NUM_SECONDS); // Storing the recorded samples

    // Opening the audio stream (input and output)
    err = Pa_OpenDefaultStream(&stream,
        NUM_CHANNELS,       // Input channels
        NUM_CHANNELS,       // Output channels
        paFloat32,          // Sample format
        SAMPLE_RATE,        // Sample rate
        FRAMES_PER_BUFFER,  // Frames per buffer
        nullptr,            // Input callback (null for simple read/write)
        nullptr             // User data (here is null)
    );                      // Output callback (null for simple read/write)

    if (err != paNoError) {
        std::cerr << "PortAudio stream open error: " << Pa_GetErrorText(err) << std::endl;
        Pa_Terminate();
        return 1;
    }

    // Starting the stream
    err = Pa_StartStream(stream);
    if (err != paNoError) {
        std::cerr << "PortAudio stream start error: " << Pa_GetErrorText(err) << std::endl;
        Pa_Terminate();
        return 1;
    }

    std::cout << "Recording for " << NUM_SECONDS << " seconds..." << std::endl;

    // Recording audio
    err = Pa_ReadStream(stream, recordedSamples.data(), recordedSamples.size());
    if (err != paNoError) {
        std::cerr << "PortAudio read stream error: " << Pa_GetErrorText(err) << std::endl;
        Pa_Terminate();
        return 1;
    }

    std::cout << "Playback recorded audio..." << std::endl;

    // Playing the recorded audio
    err = Pa_WriteStream(stream, recordedSamples.data(), recordedSamples.size());
    if (err != paNoError) {
        std::cerr << "PortAudio write stream error: " << Pa_GetErrorText(err) << std::endl;
        Pa_Terminate();
        return 1;
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

    // Terminating PortAudio
    Pa_Terminate();

    return 0;
}
