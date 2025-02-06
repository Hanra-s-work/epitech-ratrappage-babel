/*
** EPITECH PROJECT, 2024
** record_compress_decompress_play
** File description:
** Initialisation.cpp
*/

#include "CustomExceptions/Initialisation.hpp"

CustomExceptions::InitialisationFailed::InitialisationFailed(const std::string &address)
{
    _msg = "Failed to initialise connection to " + address;
    _buffer = _msg.c_str();
}

CustomExceptions::InitialisationFailed::~InitialisationFailed()
{
}

const char *CustomExceptions::InitialisationFailed::what() const noexcept
{
    return _buffer;
}
