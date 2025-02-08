/*
** EPITECH PROJECT, 2024
** record_compress_decompress_play
** File description:
** Compressor.cpp
*/

/**
 * @file Manager.cpp
 * @brief This file contains the implementation of the Manager class, which handles audio compression and decompression using Opus.
 */

#include "Compressor/Manager.hpp"

Compressor::Manager::Manager()
{
    PRETTY_INFO << "Initialising the Opus manager" << std::endl;
    PRETTY_INFO << "Initialising the encoder..." << std::endl;
    _encoder = opus_encoder_create(
        static_cast<opus_int32>(48000),
        1,
        OPUS_APPLICATION_AUDIO,
        &_error
    );
    if (_error != OPUS_OK) {
        PRETTY_ERROR << "Opus encoder initialization error: " << opus_strerror(_error) << std::endl;
        handleOpusError(_error, "Opus encoder initialization");
    }
    PRETTY_SUCCESS << "Encoder initialised" << std::endl;

    PRETTY_INFO << "Initialising the decoder..." << std::endl;

    _decoder = opus_decoder_create(
        static_cast<opus_int32>(48000),
        1,
        &_error
    );
    if (_error != OPUS_OK) {
        handleOpusError(_error, "Opus decoder initialization");
    }
    PRETTY_SUCCESS << "Decoder initialised" << std::endl;
    PRETTY_SUCCESS << "Opus manager initialised" << std::endl;
}

Compressor::Manager::Manager(const Audio::Sample &sample)
{
    PRETTY_INFO << "Initialising the Opus manager" << std::endl;
    PRETTY_INFO << "Checking arguments" << std::endl;
    if (sample.sampleRate != 24000 && sample.sampleRate != 48000) {
        throw std::invalid_argument("Invalid sample rate, supported values are 24000 and 48000.");
    }

    if (sample.numChannelsPlayback != 1 && sample.numChannelsPlayback != 2) {
        throw std::invalid_argument("Invalid number of channels, supported values are 1 (mono) or 2 (stereo).");
    }
    PRETTY_SUCCESS << "Arguments are valid" << std::endl;

    PRETTY_INFO << "Initialising the encoder..." << std::endl;
    _encoder = opus_encoder_create(
        static_cast<opus_int32>(sample.sampleRate),
        static_cast<int>(sample.numChannelsPlayback),
        OPUS_APPLICATION_AUDIO,
        &_error
    );
    if (_error != OPUS_OK) {
        handleOpusError(_error, "Opus encoder initialization");
    }
    PRETTY_SUCCESS << "Encoder initialised" << std::endl;

    PRETTY_INFO << "Initialising the decoder..." << std::endl;

    _decoder = opus_decoder_create(
        static_cast<opus_int32>(sample.sampleRate),
        static_cast<int>(sample.numChannelsPlayback),
        &_error
    );
    if (_error != OPUS_OK) {
        handleOpusError(_error, "Opus decoder initialization");
    }
    PRETTY_SUCCESS << "Decoder initialised" << std::endl;
    PRETTY_SUCCESS << "Opus manager initialised" << std::endl;
}

Compressor::Manager::~Manager()
{
    PRETTY_INFO << "Destroying the Opus manager" << std::endl;
    if (_encoder) {
        PRETTY_INFO << "Destroying the encoder..." << std::endl;
        opus_encoder_destroy(_encoder);
        PRETTY_SUCCESS << "Encoder destroyed" << std::endl;
    }
    PRETTY_INFO << "Checking if the decoder exists..." << std::endl;
    if (_decoder) {
        PRETTY_INFO << "Destroying the decoder..." << std::endl;
        opus_decoder_destroy(_decoder);
        PRETTY_SUCCESS << "Decoder destroyed" << std::endl;
    }
    PRETTY_SUCCESS << "Opus manager destroyed" << std::endl;
}

/**
 * @brief Sets the maximum packet size for compression.
 *
 * @param maxPacketSize The maximum packet size.
 */
void Compressor::Manager::setMaxPacketSize(const unsigned int maxPacketSize)
{
    PRETTY_INFO << "Setting the maximum packet size to " << maxPacketSize << std::endl;
    _maxPacketSize = maxPacketSize;
    PRETTY_SUCCESS << "Maximum packet size set" << std::endl;
}

/**
 * @brief Gets the maximum packet size for compression.
 *
 * @return The maximum packet size.
 */
const unsigned int Compressor::Manager::getMaxPacketSize() const
{
    PRETTY_INFO << "Fetching the maximum packet size" << std::endl;
    return _maxPacketSize;
}

/**
 * @brief Compresses the audio stream.
 */
void Compressor::Manager::compress()
{
    PRETTY_INFO << "Checking materials before compressing..." << std::endl;
    if (!_rawStreamSet) {
        PRETTY_ERROR << "Uncompressed stream not set" << std::endl;
        std::cerr << "Uncompressed stream not set" << std::endl;
        throw std::runtime_error("Uncompressed stream not set");
    }

    PRETTY_DEBUG << "Checking if the encoder exists..." << std::endl;
    if (!_encoder) {
        PRETTY_ERROR << "Encoder not set" << std::endl;
        std::cerr << "Encoder not set" << std::endl;
        throw std::runtime_error("Encoder not set");
    }

    PRETTY_INFO << "Locking the mutex..." << std::endl;
    std::lock_guard<std::mutex> lock(_mutex);

    PRETTY_INFO << "Initialising the compressed stream..." << std::endl;
    const int maxPacketSize = _maxPacketSize;
    int frameSize = _uncompressedStream.framesPerBuffer * (_uncompressedStream.numChannelsRecording == 2 ? 2 : 1);

    PRETTY_DEBUG << "Check if the uncompressed stream has enough data" << std::endl;
    if (_uncompressedStream.sample.size() < frameSize * _uncompressedStream.numChannelsRecording) {
        PRETTY_ERROR << "Uncompressed stream size is insufficient for encoding" << std::endl;
        std::cerr << "Uncompressed stream size is insufficient for encoding" << std::endl;
        return;
    }
    PRETTY_DEBUG << "Max packet size: " << maxPacketSize << ", frameSize: " << frameSize << std::endl;
    _compressedStream.data.resize(maxPacketSize);

    PRETTY_DEBUG << "Compressed stream size: " << _compressedStream.data.size() << std::endl;
    PRETTY_DEBUG << "Uncompressed sample data size: " << _uncompressedStream.sample.size() << std::endl;

    PRETTY_INFO << "Compressing the stream..." << std::endl;
    int compressedSize = opus_encode_float(_encoder, _uncompressedStream.sample.data(), frameSize, _compressedStream.data.data(), maxPacketSize);
    PRETTY_DEBUG << "Compressed size: " << compressedSize << std::endl;
    if (compressedSize < 0) {
        PRETTY_ERROR << "Opus encode error: " << opus_strerror(compressedSize) << std::endl;
        std::cerr << "Opus encode error: " << opus_strerror(compressedSize) << std::endl;
        return;
    }

    PRETTY_INFO << "Setting the compressed stream size..." << std::endl;
    _compressedStream.size = compressedSize;
    _compressedStream.data.resize(compressedSize);
    _hasBeenCompressed = true;
    PRETTY_SUCCESS << "Stream compressed" << std::endl;
}

/**
 * @brief Decompresses the audio stream.
 */
void Compressor::Manager::decompress()
{
    PRETTY_INFO << "Decompressing the stream..." << std::endl;
    if (!_hasBeenCompressed) {
        PRETTY_ERROR << "Compressed stream not set" << std::endl;
        std::cerr << "Compressed stream not set" << std::endl;
        throw std::runtime_error("Compressed stream not set");
    }

    PRETTY_INFO << "Locking the mutex..." << std::endl;
    std::lock_guard<std::mutex> lock(_mutex);

    PRETTY_INFO << "Initialising the uncompressed stream..." << std::endl;
    int frameSize = _uncompressedStream.framesPerBuffer;
    _uncompressedStream.sample.resize(frameSize * _uncompressedStream.numChannelsPlayback);

    PRETTY_INFO << "Decompressing the stream..." << std::endl;
    int decodedSamples = opus_decode_float(_decoder, _compressedStream.data.data(), _compressedStream.size, _uncompressedStream.sample.data(), frameSize, 0);
    if (decodedSamples < 0) {
        PRETTY_ERROR << "Opus decode error: " << opus_strerror(decodedSamples) << std::endl;
        std::cerr << "Opus decode error: " << opus_strerror(decodedSamples) << std::endl;
        return;
    }

    _rawStreamSet = true;
    PRETTY_SUCCESS << "Stream has been decompressed" << std::endl;
}

/**
 * @brief Gets the compressed audio stream.
 *
 * @return The compressed audio stream.
 */
const Compressor::Packet &Compressor::Manager::getCompressedStream() const
{
    PRETTY_INFO << "Fetching the compressed stream" << std::endl;
    if (!_hasBeenCompressed) {
        PRETTY_ERROR << "Compressed stream not set" << std::endl;
        std::cerr << "Compressed stream not set" << std::endl;
        throw std::runtime_error("Compressed stream not set");
    }
    PRETTY_SUCCESS << "Compressed stream fetched" << std::endl;
    return _compressedStream;
}

/**
 * @brief Sets the compressed audio stream.
 *
 * @param data The compressed audio stream.
 */
void Compressor::Manager::setCompressedStream(const Compressor::Packet &data)
{
    PRETTY_INFO << "Setting the compressed stream" << std::endl;
    std::lock_guard<std::mutex> lock(_mutex);
    _compressedStream = data;
    _hasBeenCompressed = true;
    PRETTY_SUCCESS << "Compressed stream set" << std::endl;
}

/**
 * @brief Gets the uncompressed audio stream.
 *
 * @return The uncompressed audio stream.
 */
const Audio::Sample &Compressor::Manager::getUncompressedStream() const
{
    PRETTY_INFO << "Fetching the uncompressed stream" << std::endl;
    if (!_rawStreamSet) {
        PRETTY_ERROR << "Uncompressed stream not set" << std::endl;
        std::cerr << "Uncompressed stream not set" << std::endl;
        throw std::runtime_error("Uncompressed stream not set");
    }
    PRETTY_SUCCESS << "Uncompressed stream fetched" << std::endl;
    return _uncompressedStream;
}

/**
 * @brief Sets the uncompressed audio stream.
 *
 * @param data The uncompressed audio stream.
 */
void Compressor::Manager::setUncompressedStream(const Audio::Sample &data)
{
    PRETTY_INFO << "Setting the uncompressed stream" << std::endl;
    PRETTY_INFO << "Checking arguments" << std::endl;
    if (data.sampleRate != 24000 && data.sampleRate != 48000) {
        throw std::invalid_argument("Invalid sample rate, supported values are 24000 and 48000.");
    }

    if (data.numChannelsPlayback != 1 && data.numChannelsPlayback != 2) {
        throw std::invalid_argument("Invalid number of channels, supported values are 1 (mono) or 2 (stereo).");
    }
    PRETTY_SUCCESS << "Arguments are valid" << std::endl;
    std::lock_guard<std::mutex> lock(_mutex);
    _uncompressedStream = data;
    _rawStreamSet = true;
    PRETTY_SUCCESS << "Uncompressed stream set" << std::endl;
}

/**
 * @brief Encodes the audio data.
 *
 * @param sound The input audio data.
 * @param output The encoded audio data.
 */
void Compressor::Manager::encode(std::vector<float> &sound, std::vector<unsigned char> &output)
{
    PRETTY_INFO << "Encoding the sound..." << std::endl;
    int nbBytes = 0;
    const int framesPerBuffer = 480;
    std::array<unsigned char, 4000> cbits;

    if (sound.empty()) {
        PRETTY_WARNING << "The sound is empty, skipping" << std::endl;
        return;
    }
    nbBytes = opus_encode_float(_encoder, sound.data(), framesPerBuffer, cbits.data(), 4000);
    if (nbBytes <= 1) {
        PRETTY_ERROR << "Failed to encode float" << std::endl;
        handleOpusError(nbBytes, "failed to encode float ");
    }
    for (int i = 0; i != nbBytes; i++) {
        output.push_back(cbits[i]);
    }
    PRETTY_SUCCESS << "Sound encoded" << std::endl;
}

// void Compressor::Manager::encode(std::vector<float> &sound, std::vector<unsigned char> &output)
// {
//     PRETTY_INFO << "Encoding the sound..." << std::endl;
//     int nbBytes = 0;
//     const int cbits_length = 4000;
//     std::array<unsigned char, cbits_length> cbits;
//     std::vector<float> croppedSound;


//     if (sound.empty()) {
//         PRETTY_WARNING << "Sound is empty" << std::endl;
//         return;
//     }
//     if (sound.size() > cbits_length) {
//         PRETTY_WARNING << "Sound is too big, size is: " << sound.size() << ", reducing" << std::endl;
//         for (int i = 0; i < cbits_length - 1; i++) {
//             croppedSound.push_back(sound[i]);
//         }
//     } else {
//         croppedSound = sound;
//     }
//     PRETTY_INFO << "Sound size is " << croppedSound.size() << std::endl;
//     nbBytes = opus_encode_float(_encoder, croppedSound.data(), 256, cbits.data(), cbits_length);
//     if (nbBytes <= 1) {
//         PRETTY_ERROR << "Failed to encode float" << std::endl;
//         handleOpusError(nbBytes, "failed to encode float ");
//     }
//     for (int i = 0; i != nbBytes; i++) {
//         PRETTY_DEBUG << "Encoded sound: " << cbits[i] << std::endl;
//         output.push_back(cbits[i]);
//     }
//     PRETTY_INFO << "Sound encoded" << std::endl;
// }

/**
 * @brief Decodes the audio data.
 *
 * @param sound The input encoded audio data.
 * @param output The decoded audio data.
 */
void Compressor::Manager::decode(std::vector<unsigned char> &sound, std::vector<float> &output)
{
    PRETTY_INFO << "Decoding the sound..." << std::endl;
    int nbBytes = 0;
    const int cbit_length = 4000;
    std::array<float, cbit_length> cbits;

    if (sound.empty()) {
        PRETTY_WARNING << "Sound is empty" << std::endl;
        return;
    }
    nbBytes = opus_decode_float(_decoder, sound.data(), sound.size(), cbits.data(), cbit_length, 0);
    if (nbBytes <= 1) {
        PRETTY_ERROR << "Failed to decode float" << std::endl;
        handleOpusError(nbBytes, "failed to decode float ");
    }
    for (int i = 0; i != nbBytes; i++) {
        PRETTY_DEBUG << "Decoded sound: " << cbits[i] << std::endl;
        output.push_back(cbits[i]);
    }
    PRETTY_INFO << "Sound decoded" << std::endl;
}

/**
 * @brief Handles Opus errors.
 *
 * @param errorCode The Opus error code.
 * @param context The context in which the error occurred.
 */
void Compressor::Manager::handleOpusError(int errorCode, const std::string &context) const
{
    PRETTY_INFO << "Handling Opus error..." << std::endl;
    if (errorCode != OPUS_OK) {
        throw std::runtime_error(context + " failed: " + opus_strerror(errorCode));
    }
}
