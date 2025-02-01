/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** Invalid.cpp
*/

/**
 * @file Invalid.cpp
 * @brief This file contains the implementation of custom exception classes used to inform the user about various invalid inputs.
 */

#include "CustomExceptions/Invalid.hpp"

namespace CustomExceptions
{

    InvalidIp::InvalidIp(const std::string &error)
    {
        _msg = "Error: The ip you provided '";
        _msg += error;
        _msg += "' is incorrect, it should be of type ipV4.\n";
        _msg += "Hint: An IpV4 is:\n";
        _msg += "-\tComposed of 4 whole numbers\n";
        _msg += "-\tEach whole number ranges from 0 to 255\n";
        _msg += "-\tEach whole number is connected to the next one by a '.'\n";
        _msg += "-\tHere is a typical example of an IpV4 address: '127.0.0.1";
        _buffer = _msg.c_str();
    };

    InvalidIp::~InvalidIp() {};

    const char *InvalidIp::what() const noexcept
    {
        return _buffer;
    }

    InvalidPort::InvalidPort(const std::string &error)
    {
        _msg = "Error: The port you provided '";
        _msg += error;
        _msg += "' is incorrect.\n";
        _msg += "Hint: The port should be a whole number in the range between 0 and 65535";
        _buffer = _msg.c_str();
    };

    InvalidPort::~InvalidPort() {};

    const char *InvalidPort::what() const noexcept
    {
        return _buffer;
    }

    InvalidType::InvalidType(const std::string &extraDetails)
    {
        _msg = "Error: The content present in std::any does not match ";
        _msg += "the provided type (or is just missing).";
        if (!extraDetails.empty()) {
            _msg += "\n(" + extraDetails + ")";
        }
        _buffer = _msg.c_str();
    };

    InvalidType::~InvalidType() {};

    const char *InvalidType::what() const noexcept
    {
        return _buffer;
    }

    InvalidUsername::InvalidUsername(const std::string &error)
    {
        _msg = "Error: The username you provided '";
        _msg += error;
        _msg += "' is incorrect.\n";
        _msg += "Hint1/3: The Username should not be empty or contain special characters like emojis.\n";
        _msg += "Hint2/3: The Username should not exceed '" + Recoded::myToString(USERNAME_MAX_LENGTH) + "' characters and only be made of printable ascii characters as well as the ' ' character.\n";
        _msg += "Hint3/3: The Username should not be below '" + Recoded::myToString(USERNAME_MIN_LENGTH) + "' characters or be composed of only whitespaces.";
        _buffer = _msg.c_str();
    };

    InvalidUsername::~InvalidUsername() {};

    const char *InvalidUsername::what() const noexcept
    {
        return _buffer;
    }

    InvalidOperation::InvalidOperation(const std::string &error)
    {
        _msg = "Error: The operation you tried to perform did not succeed.\n";
        if (!error.empty()) {
            _msg += "The operation provided the following message: '" + error + "'.\n";
        }
        _buffer = _msg.c_str();
    };

    InvalidOperation::~InvalidOperation() {};

    const char *InvalidOperation::what() const noexcept
    {
        return _buffer;
    }

    InvalidChoice::InvalidChoice(const std::string &error)
    {
        _msg = "Error: The option you chose is invalid.\n";
        if (!error.empty()) {
            _msg += "The function in charge of processing your choice provided the following message: '" + error + "'.\n";
        }
        _buffer = _msg.c_str();
    };

    InvalidChoice::~InvalidChoice() {};

    const char *InvalidChoice::what() const noexcept
    {
        return _buffer;
    }

    InvalidDuration::InvalidDuration(const std::string &duration, const std::string &min, const std::string &max)
    {
        _msg = "Error: The duration you provided is invalid.\n";
        if (!min.empty() && !max.empty()) {
            _msg += "The duration must be in the range '" + min + "' to '" + max + "'.\n";
        } else if (!min.empty() && max.empty()) {
            _msg += "The duration must be greater than or equal to '" + min + "'.\n";
        } else if (min.empty() && !max.empty()) {
            _msg += "The duration must be less than or equal to '" + max + "'.\n";
        } else {
            _msg += "The duration must be a valid number.\n";
        }
        _msg += "The duration was: '";
        _msg += duration;
        _msg += "'.";
        _buffer = _msg.c_str();
    };

    InvalidDuration::~InvalidDuration() {};

    const char *InvalidDuration::what() const noexcept
    {
        return _buffer;
    }

    InvalidTOML::InvalidTOML(const std::string &path, const std::string &error)
    {
        _msg = "Error: The TOML file you provided is invalid\n";
        _msg += "The filepath you provided is '" + path + "'.\n";
        _msg += "The detailed error is '" + error + "'.";
        _buffer = _msg.c_str();
    };

    InvalidTOML::~InvalidTOML() {};

    const char *InvalidTOML::what() const noexcept
    {
        return _buffer;
    }

    InvalidTOMLKeyType::InvalidTOMLKeyType(const std::string &tomlPath, const std::string &tomlKey, const std::string &currentType, const std::string &expectedType)
    {
        _msg = "Error: The type of the key '";
        _msg += tomlKey;
        _msg += "' is '";
        _msg += currentType;
        _msg += "' but '";
        _msg += expectedType;
        _msg += "' type was expected for the configuration file '";
        _msg += tomlPath;
        _msg += "'.";
        _buffer = _msg.c_str();
    };

    InvalidTOMLKeyType::~InvalidTOMLKeyType() {};

    const char *InvalidTOMLKeyType::what() const noexcept
    {
        return _buffer;
    }

}
