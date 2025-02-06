/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** Failed.cpp
*/

/**
 * @file Failed.cpp
 *
 * @brief File in charge of containing the code in charge of filling the exception classes Failed
 */

#include "CustomExceptions/Failed.hpp"

namespace CustomExceptions
{

    ConnectionFailed::ConnectionFailed(const std::string &address)
    {
        _msg = "Error: The provided address is unreachable.\n";
        _msg += "The address was: '";
        _msg += address;
        _msg += "'.";
        _buffer = _msg.c_str();
    };

    ConnectionFailed::~ConnectionFailed() {};

    const char *ConnectionFailed::what() const noexcept
    {
        return _buffer;
    }

}
