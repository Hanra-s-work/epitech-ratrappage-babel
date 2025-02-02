/*
** EPITECH PROJECT, 2024
** epitech-ratrappage-babel (Workspace)
** File description:
** Manager.hpp
*/

#pragma once

#include "Logging.hpp"
#include "CustomExceptions.hpp"

#include "Network/AddressHolder.hpp"

#include "Audio/Manager.hpp"
#include "Audio/Network.hpp"

namespace Network
{
    class Manager {
        public:
        Manager();
        ~Manager();

        /**
         * @brief Updates the AddressHolder by copying another AddressHolder.
         *
         * @param copy The AddressHolder to copy data from.
         */
        void update(const Network::Manager &copy);

        /**
         * @brief Dumps the current state of the variables for debugging purposes.
         * It will dump them for itself and any of its underlying classes.
         *
         * @param indent The level to which the class should be indented in the dump.
         * @return The formatted output.
         */
        const std::string getInfo(const unsigned int indent = 0) const;

        /**
         * @brief Overloads the assignment operator to copy from another Manager.
         *
         * @param copy The Manager to copy data from.
         * @return A reference to the updated instance.
         */
        Manager &operator =(const Network::Manager &copy);

        private:
    };

    /**
     * @brief Outputs the Manager's info to a stream.
     *
     * @param os The output stream.
     * @param item The Manager to output.
     * @return The modified output stream.
     */
    std::ostream &operator<<(std::ostream &os, const Manager &item);
}
