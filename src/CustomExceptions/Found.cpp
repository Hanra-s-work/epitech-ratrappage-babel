/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** Found.cpp
*/

/**
 * @file Found.cpp
 *
 * @brief Implementation of custom exceptions to inform the user about found elements.
 */

#include "CustomExceptions/Found.hpp"

namespace CustomExceptions
{
    /**
     * @brief Construct a new HelpFound object.
     * Sets the message indicating that the help option was found.
     */
    HelpFound::HelpFound()
    {
        _msg = "Info: The Help option was found, exiting.";
        _buffer = _msg.c_str();
    }

    /**
     * @brief Destroy the HelpFound object.
     */
    HelpFound::~HelpFound() {}

    /**
     * @brief Retrieves the message for HelpFound exception.
     * @return A C-style string representing the message.
     */
    const char *HelpFound::what() const noexcept
    {
        return _buffer;
    }

    /**
     * @brief Construct a new VersionFound object.
     * Sets the message indicating that the version option was found.
     */
    VersionFound::VersionFound()
    {
        _msg = "Info: The Version option was found, exiting.";
        _buffer = _msg.c_str();
    }

    /**
     * @brief Destroy the VersionFound object.
     */
    VersionFound::~VersionFound() {}

    /**
     * @brief Retrieves the message for VersionFound exception.
     * @return A C-style string representing the message.
     */
    const char *VersionFound::what() const noexcept
    {
        return _buffer;
    }

    /**
     * @brief Construct a new ThreadFound object.
     * Sets the message indicating that a thread was found and terminated.
     */
    ThreadFound::ThreadFound()
    {
        _msg = "Info: The thread was found and was thus forcibly terminated.";
        _buffer = _msg.c_str();
    }

    /**
     * @brief Destroy the ThreadFound object.
     */
    ThreadFound::~ThreadFound() {}

    /**
     * @brief Retrieves the message for ThreadFound exception.
     * @return A C-style string representing the message.
     */
    const char *ThreadFound::what() const noexcept
    {
        return _buffer;
    }

}
