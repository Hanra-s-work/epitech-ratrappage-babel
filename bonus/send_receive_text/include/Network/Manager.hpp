/*
** EPITECH PROJECT, 2024
** epitech-ratrappage-babel (Workspace)
** File description:
** Manager.hpp
*/

#pragma once

#include <optional>

#include "Logging.hpp"
#include "CustomExceptions.hpp"

#include "Network/Packet.hpp"
#include "Network/Tcp.hpp"
#include "Network/Udp.hpp"
#include "Network/AddressHolder.hpp"

#include "Audio/Manager.hpp"
#include "Audio/Networker.hpp"

namespace Network
{
    class Manager {
        public:
        Manager();
        ~Manager();

        void setTcpAddress(const Network::AddressHolder &addressHolder);
        void setUdpAddress(const Network::AddressHolder &addressHolder);
        void setServerAddress(const Network::AddressHolder &addressHolder);

        void startTcp();
        void startUdp();

        void stopTcp();
        void stopUdp();

        const std::vector<Packet> getUdpReceivedData();
        const std::vector<Packet> getTcpReceivedData();

        void sendUdpData(const std::vector<Packet> &data);
        void sendTcpData(const std::vector<Packet> &data);

        const bool isTcpOpen() const;
        const bool isUdpOpen() const;
        const bool isServerOpen() const;

        void connectToServer();

        void disconnectFromServer();

        const std::vector<std::string> getCommunicationLinks() const;

        /**
         * @brief Dumps the current state of the variables for debugging purposes.
         * It will dump them for itself and any of its underlying classes.
         *
         * @param indent The level to which the class should be indented in the dump.
         * @return The formatted output.
         */
        const std::string getInfo(const unsigned int indent = 0) const;

        const AddressHolder getTcpAddress() const;
        const AddressHolder getUdpAddress() const;
        const AddressHolder getServerAddress() const;

        /**
         * @brief Overloads the assignment operator to copy from another Manager.
         *
         * @param copy The Manager to copy data from.
         * @return A reference to the updated instance.
         */
        Manager &operator =(const Network::Manager &copy);

        private:
        bool _hostingCall = false;
        Network::AddressHolder _serverAddress;
        Network::AddressHolder _targetAddress;
        Network::AddressHolder _listeningAddress;
        std::optional<Network::Tcp> _server;
        std::optional<Network::Tcp> _sender;
        std::optional<Network::Udp> _listener;
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
