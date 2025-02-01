/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** No.cpp
*/

/**
 * @file No.cpp
 *
 * @brief File in charge of containing the code for the classes 'No'
 */

#include "CustomExceptions/No.hpp"

namespace CustomExceptions
{

    NoFlagParameter::NoFlagParameter(const std::string &error)
    {
        _msg = "Error: There is no parameter passed to the flag.\n";
        _msg += "The concerned flag is: ";
        _msg += error;
        _buffer = _msg.c_str();
    };

    NoFlagParameter::~NoFlagParameter() {};

    const char *NoFlagParameter::what() const noexcept
    {
        return _buffer;
    }

    NoTOML::NoTOML(const std::string &tomlPath)
    {
        _msg = "Error: There is no configuration for the default font in the toml's configuration file ";
        if (!tomlPath.empty()) {
            _msg += "path " + tomlPath + " ";
        }
        _msg += "that is set to be used.";
        _buffer = _msg.c_str();
    };

    NoTOML::~NoTOML() {};

    const char *NoTOML::what() const noexcept
    {
        return _buffer;
    }

    NoTOMLKey::NoTOMLKey(const std::string &tomlPath, const std::string &tomlKey)
    {
        _msg = "Error: There is no toml ";
        if (!tomlKey.empty()) {
            _msg += "key '" + tomlKey + "'";
            if (!tomlPath.empty()) {
                _msg += " in the toml path " + tomlPath + " ";
            }
        }
        _msg += "set to be used.";
        _buffer = _msg.c_str();
    };

    NoTOMLKey::~NoTOMLKey() {};

    const char *NoTOMLKey::what() const noexcept
    {
        return _buffer;
    }

    NoActiveNetwork::NoActiveNetwork(const std::string &exceptionDetails)
    {
        _msg = "Error: There is no running network  to use for the function you called.\n";
        if (!exceptionDetails.empty()) {
            _msg += "Additional details: (" + exceptionDetails + ")";
        }
        _buffer = _msg.c_str();
    };

    NoActiveNetwork::~NoActiveNetwork() {};

    const char *NoActiveNetwork::what() const noexcept
    {
        return _buffer;
    }

    NoAddressManager::NoAddressManager(const std::string &exceptionDetails)
    {
        _msg = "Error: There is no active address manager class to hold the connection information of the program.\n";
        if (!exceptionDetails.empty()) {
            _msg += "Additional details: (" + exceptionDetails + ")";
        }
        _buffer = _msg.c_str();
    };

    NoAddressManager::~NoAddressManager() {};

    const char *NoAddressManager::what() const noexcept
    {
        return _buffer;
    }

    NoNetworkClass::NoNetworkClass(const std::string &exceptionDetails)
    {
        _msg = "Error: There is no network class to be passed\n";
        if (!exceptionDetails.empty()) {
            _msg += "Additional details: (" + exceptionDetails + ")";
        }
        _buffer = _msg.c_str();
    };

    NoNetworkClass::~NoNetworkClass() {};

    const char *NoNetworkClass::what() const noexcept
    {
        return _buffer;
    }
}
