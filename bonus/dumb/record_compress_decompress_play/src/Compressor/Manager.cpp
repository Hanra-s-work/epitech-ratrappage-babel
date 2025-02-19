/*
** EPITECH PROJECT, 2024
** record_compress_decompress_play
** File description:
** Compressor.cpp
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

void Compressor::Manager::setMaxPacketSize(const unsigned int maxPacketSize)
{
    PRETTY_INFO << "Setting the maximum packet size to " << maxPacketSize << std::endl;
    _maxPacketSize = maxPacketSize;
    PRETTY_SUCCESS << "Maximum packet size set" << std::endl;
}

const unsigned int Compressor::Manager::getMaxPacketSize() const
{
    PRETTY_INFO << "Fetching the maximum packet size" << std::endl;
    return _maxPacketSize;
}

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

void Compressor::Manager::setCompressedStream(const Compressor::Packet &data)
{
    PRETTY_INFO << "Setting the compressed stream" << std::endl;
    std::lock_guard<std::mutex> lock(_mutex);
    _compressedStream = data;
    _hasBeenCompressed = true;
    PRETTY_SUCCESS << "Compressed stream set" << std::endl;
}

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

void Compressor::Manager::handleOpusError(int errorCode, const std::string &context) const
{
    PRETTY_INFO << "Handling Opus error..." << std::endl;
    if (errorCode != OPUS_OK) {
        throw std::runtime_error(context + " failed: " + opus_strerror(errorCode));
    }
}
