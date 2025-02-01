/*
** EPITECH PROJECT, 2024
** epitech-ratrappage-babel (Workspace)
** File description:
** AddressHolder.hpp
*/

#pragma once

#include <string>
#include "Logging.hpp"
#include "CustomExceptions.hpp"

namespace Network
{
    /**
     * @brief The AddressHolder class holds an IP address and a port number.
     */
    class AddressHolder {
        public:
        /**
         * @brief Default constructor.
         */
        AddressHolder() = default;

        /**
         * @brief Constructor with parameters.
         *
         * @param ip The IP address to set.
         * @param port The port number to set.
         */
        AddressHolder(const std::string &ip, const unsigned int port);

        /**
         * @brief Default destructor.
         */
        ~AddressHolder() = default;

        /**
         * @brief Sets the IP address.
         * @param ip The IP address to set.
         * @throws CustomExceptions::InvalidIp if the IP address is invalid.
         */
        void setIp(const std::string &ip);

        /**
         * @brief Sets the port number.
         * @param port The port number to set.
         * @throws CustomExceptions::InvalidPort if the port number is invalid.
         */
        void setPort(const unsigned int port);

        /**
         * @brief Gets the IP address.
         * @return The IP address.
         */
        const std::string getIp() const;

        /**
         * @brief Gets the port number.
         * @return The port number.
         */
        const unsigned int getPort() const;

        /**
         * @brief Updates the AddressHolder by copying another AddressHolder.
         *
         * @param copy The AddressHolder to copy data from.
         */
        void update(const Network::AddressHolder &copy);

        /**
         * @brief Dumps the current state of the variables for debugging purposes.
         * It will dump them for itself and any of its underlying classes.
         *
         * @param indent The level to which the class should be indented in the dump.
         * @return The formatted output.
         */
        const std::string getInfo(const unsigned int indent = 0) const;

        /**
         * @brief Overloads the assignment operator to copy from another AddressHolder.
         *
         * @param copy The AddressHolder to copy data from.
         * @return A reference to the updated instance.
         */
        AddressHolder &operator =(const Network::AddressHolder &copy);

        private:
        /**
         * @brief Checks if the provided IP address is correct.
         * @param ip The IP address to check.
         * @return true if the IP address is correct.
         * @return false if the IP address is incorrect.
         */
        const bool _isIpCorrect(const std::string &ip) const;

        /**
         * @brief Checks if the provided port number is correct.
         * @param port The port number to check.
         * @return true if the port number is correct.
         * @return false if the port number is incorrect.
         */
        const bool _isPortCorrect(const unsigned int port) const;

        std::string _ip = "0.0.0.0"; //!< The IP address.
        unsigned int _port = 6000; //!< The port number.
    };

    /**
     * @brief Outputs the AddressHolder's info to a stream.
     *
     * @param os The output stream.
     * @param item The AddressHolder to output.
     * @return The modified output stream.
     */
    std::ostream &operator<<(std::ostream &os, const AddressHolder &item);
}
