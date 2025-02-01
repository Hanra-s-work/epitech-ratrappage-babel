/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** NotFound.cpp
*/

/**
 * @file NotFound.cpp
 *
 * @brief File in charge of containing the code that will fill the classes NotFound
 */

#include "CustomExceptions/NotFound.hpp"

namespace CustomExceptions
{
    FileNotFound::FileNotFound(const std::string &error)
    {
        _msg = "Error: The file provided was not found or readable.\n";
        _msg += "The file path you provided is: ";
        _msg += error;
        _buffer = _msg.c_str();
    };

    FileNotFound::~FileNotFound() {};

    const char *FileNotFound::what() const noexcept
    {
        return _buffer;
    }

}
