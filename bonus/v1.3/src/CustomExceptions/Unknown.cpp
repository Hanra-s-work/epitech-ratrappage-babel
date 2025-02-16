/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** Unknown.cpp
*/

/**
 * @file Unknown.cpp
 *
 * @brief This file contains the implementation of the Unknown class.
 */

#include "CustomExceptions/Unknown.hpp"

namespace CustomExceptions
{

    UnknownArgument::UnknownArgument(const std::string &argument)
    {
        _msg = "Error: The argument you provided is unknown.\n";
        _msg += "The argument was: '";
        _msg += argument;
        _msg += "'.";
        _buffer = _msg.c_str();
    };

    UnknownArgument::~UnknownArgument() {};

    const char *UnknownArgument::what() const noexcept
    {
        return _buffer;
    }

}
