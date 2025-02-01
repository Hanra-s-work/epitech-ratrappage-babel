/*
** EPITECH PROJECT, 2024
** epitech-ratrappage-babel (Workspace)
** File description:
** MainClass.cpp
*/

/**
 * @file MainClass.cpp
 *
 * @brief The file in charge of containing the code for the functions contained in the MainClass class
 */

#include "MainClass.hpp"

 /**
  * @brief Construct a new Main:: Main object
  */
Main::Main()
    : _toml(), _addresses()
{
};

/**
 * @brief Construct a new Main:: Main object
 *
 * @param ip The ip of the program
 * @param port The port of the program
 */
Main::Main(const std::string &ip, const unsigned int port)
{
    setIp(ip);
    setPort(port);
};

/**
 * @brief Construct a new Main:: Main object
 *
 * @param ip The ip of the program
 * @param port The port of the program
 * @param log Enable or disable logging
 * @param debug Enable or disable debugging
 */
Main::Main(const std::string &ip, const unsigned int port, const bool log, const bool debug)
    : _toml()
{
    setIp(ip);
    setPort(port);
    setLog(log);
    setDebug(debug);
};

/**
 * @brief Construct a new Main:: Main object
 *
 * @param ip The ip of the program
 * @param port The port of the program
 * @param name The username
 * @param log Enable or disable logging
 * @param debug Enable or disable debugging
 */
Main::Main(const std::string &ip, const unsigned int port, const std::string &name, const bool log, const bool debug)
    : _toml()
{
    setIp(ip);
    setPort(port);
    setUserName(name);
    setLog(log);
    setDebug(debug);
};

/**
 * @brief Set the Log object
 *
 * @param log Enable or disable logging
 */
void Main::setLog(const bool log)
{
    Logging::Log::getInstance().setLogEnabled(log);
    PRETTY_INFO << "Logging is set to " << Recoded::myToString(log) << std::endl;
};

/**
 * @brief Set the Debug object
 *
 * @param debug Enable or disable debugging
 */
void Main::setDebug(const bool debug)
{
    Logging::Log::getInstance().setDebugEnabled(debug);
    PRETTY_DEBUG << "Debugging is set to " << Recoded::myToString(debug) << std::endl;
};

/**
 * @brief Set the Ip object
 *
 * @param ip The ip of the program
 */
void Main::setIp(const std::string &ip)
{
    _addresses.setIp(ip);
};

/**
 * @brief Set the Port object
 *
 * @param port The port of the program
 */
void Main::setPort(const unsigned int port)
{
    _addresses.setPort(port);
};

/**
 * @brief Set the User Name object
 *
 * @param username The username
 */
void Main::setUserName(const std::string &username)
{
    _checkUsernameValidity(username);
    _username = username;
};

/**
 * @brief Set the Config File object
 *
 * @param path The path to the config file
 */
void Main::setConfigFile(const std::string &path)
{
    _toml.setTOMLPath(path);
};

/**
 * @brief Start the program.
 */
void Main::takeOff()
{
    std::cout << "Starting the program." << std::endl;
}

/**
 * @brief Get the Log object
 *
 * @return const bool Logging status
 */
const bool Main::getLog() const
{
    return Logging::Log::getInstance().getLogEnabled();
};

/**
 * @brief Get the Debug object
 *
 * @return const bool Debugging status
 */
const bool Main::getDebug() const
{
    return Logging::Log::getInstance().getDebugEnabled();
};

/**
 * @brief Get the Ip object
 *
 * @return const std::string IP address
 */
const std::string Main::getIp() const
{
    return _addresses.getIp();
};

/**
 * @brief Get the Port object
 *
 * @return const unsigned int Port number
 */
const unsigned int Main::getPort() const
{
    return _addresses.getPort();
};

/**
 * @brief Get the User Name object
 *
 * @return const std::string Username
 */
const std::string Main::getUserName() const
{
    return _username;
};

/**
 * @brief Get the Config File Path object
 *
 * @return const std::string Config file path
 */
const std::string Main::getConfigFilePath() const
{
    return _toml.getTOMLPath();
};

const TOMLLoader Main::getTOMLInstance() const
{
    return _toml;
}

/**
 * @brief Check if the provided string contains only whitespace characters.
 *
 * @param string The string to check.
 * @return true If the string contains only whitespace characters.
 * @return false If the string contains any non-whitespace characters.
 */
const bool Main::_isOnlyWhitespaces(const std::string &string) const
{
    return std::all_of(
        string.begin(),
        string.end(),
        [](unsigned char c) {
            return std::isspace(c);
        }
    );
}

/**
 * @brief Validate the username
 *
 * @param username The username to validate
 *
 * @throws CustomExceptions::InvalidUsername If the username is invalid
 */
void Main::_checkUsernameValidity(const std::string &username) const
{
    if (
        username.empty() ||
        username.length() > USERNAME_MAX_LENGTH || username.length() < USERNAME_MIN_LENGTH ||
        _isOnlyWhitespaces(username)
        ) {
        throw CustomExceptions::InvalidUsername(username);
    }
    for (char c : username) {
        if (!isprint(c) && (c != ' ')) {
            throw CustomExceptions::InvalidUsername(username);
        }
    }
}


/**
 * @brief Updates the sprite by copying another Main.
 *
 * @param copy The Main to copy data from.
 */
void Main::update(const Main &copy)
{
    _username = copy.getUserName();
    _toml = copy.getTOMLInstance();
    _addresses = Network::AddressHolder(copy.getIp(), copy.getPort());
}

const std::string Main::getInfo(const unsigned int indent) const
{

    std::string indentation = "";
    for (unsigned int i = 0; i < indent; ++i) {
        indentation += "\t";
    }
    std::string result = indentation + "Main:\n";
    result += indentation + "- Ip: '" + _username + "'\n";
    result += indentation + "- Addresses: {\n" + _addresses.getInfo(indent + 1) + indentation + "\n}\n";
    result += indentation + "- toml: {\n" + _toml.getTOMLString() + indentation + "\n}\n";
    return result;
}

/**
 * @brief Overloads the assignment operator to copy from another Main.
 *
 * @param copy The Main to copy data from.
 *
 * @return A reference to the updated instance.
 */
Main &Main::operator =(const Main &copy)
{
    update(copy);
    return *this;
}

std::ostream &operator<<(std::ostream &os, const Main &item)
{
    os << item.getInfo();
    return os;
}
