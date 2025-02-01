/*
** EPITECH PROJECT, 2024
** epitech-ratrappage-babel (Workspace)
** File description:
** AddressHolder.cpp
*/

#include "Network/AddressHolder.hpp"


/**
 * @brief Constructor with parameters
 *
 * @param ip The IP address to set
 * @param port The port number to set
 */
Network::AddressHolder::AddressHolder(const std::string &ip, const unsigned int port)
{
    setIp(ip);
    setPort(port);
}

/**
 * @brief Sets the IP address
 * @param ip The IP address to set
 * @throws CustomExceptions::InvalidIp if the IP address is invalid
 */
void Network::AddressHolder::setIp(const std::string &ip)
{
    if (!_isIpCorrect(ip)) {
        throw CustomExceptions::InvalidIp(ip);
    }
    _ip = ip;
}

/**
 * @brief Sets the port number
 * @param port The port number to set
 * @throws CustomExceptions::InvalidPort if the port number is invalid
 */
void Network::AddressHolder::setPort(const unsigned int port)
{
    if (!_isPortCorrect(port)) {
        throw CustomExceptions::InvalidPort(std::to_string(port));
    }
    _port = port;
}

/**
 * @brief Gets the IP address
 * @return The IP address
 */
const std::string Network::AddressHolder::getIp() const
{
    return _ip;
}

/**
 * @brief Gets the port number
 * @return The port number
 */
const unsigned int Network::AddressHolder::getPort() const
{
    return _port;
}

/**
 * @brief Checks if the IP address provided is correct.
 *
 * @param ip The IP address to check
 * @return true if the IP address is correct
 * @return false if the IP address is incorrect
 */
const bool Network::AddressHolder::_isIpCorrect(const std::string &ip) const
{
    std::istringstream iss(ip);
    std::string segment;
    int count = 0;

    while (std::getline(iss, segment, '.')) {
        if (count >= 4) {
            return false;
        }
        try {
            int octet = std::stoi(segment);
            if (octet < 0 || octet > 255) {
                return false;
            }
        }
        catch (...) {
            return false;
        }
        count++;
    }

    return count == 4;
}

/**
 * @brief Checks if the provided port number is correct.
 *
 * @param port The port number to check
 * @return true if the port number is correct
 * @return false if the port number is incorrect
 */
const bool Network::AddressHolder::_isPortCorrect(const unsigned int port) const
{
    return port >= 0 && port <= 65535;
}


/**
 * @brief Updates the AddressHolder by copying another AddressHolder.
 *
 * @param copy The AddressHolder to copy data from.
 */
void Network::AddressHolder::update(const Network::AddressHolder &copy)
{
    _ip = copy.getIp();
    _port = copy.getPort();
}

/**
 * @brief Gets the information of the AddressHolder as a formatted string.
 *
 * @param indent The indentation level for formatting
 * @return A formatted string containing the AddressHolder information
 */
const std::string Network::AddressHolder::getInfo(const unsigned int indent) const
{

    std::string indentation = "";
    for (unsigned int i = 0; i < indent; ++i) {
        indentation += "\t";
    }
    std::string result = indentation + "AddressHolder:\n";
    result += indentation + "- Ip: '" + _ip + "'\n";
    result += indentation + "- Port: '" + Recoded::myToString(_port) + "'\n";
    return result;
}

/**
 * @brief Overloads the assignment operator to copy from another AddressHolder.
 *
 * @param copy The AddressHolder to copy data from.
 * @return A reference to the updated instance.
 */
Network::AddressHolder &Network::AddressHolder::operator =(const Network::AddressHolder &copy)
{
    update(copy);
    return *this;
}

/**
 * @brief Overloads the stream insertion operator to output the AddressHolder information.
 *
 * @param os The output stream
 * @param item The AddressHolder instance
 * @return The output stream with the AddressHolder information
 */
std::ostream &Network::operator<<(std::ostream &os, const Network::AddressHolder &item)
{
    os << item.getInfo();
    return os;
}
