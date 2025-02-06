/*
** EPITECH PROJECT, 2024
** epitech-ratrappage-babel (Workspace)
** File description:
** Manager.cpp
*/

#include "Network/Manager.hpp"

Network::Manager::Manager()
{
}

Network::Manager::~Manager()
{
}

void Network::Manager::setTcpAddress(const Network::AddressHolder &addressHolder)
{
    _targetAddress = addressHolder;
}

void Network::Manager::setUdpAddress(const Network::AddressHolder &addressHolder)
{
    _listeningAddress = addressHolder;
}

void Network::Manager::startUdp()
{
    if (_listener.has_value()) {
        _listener.reset();
    }
    _listener.emplace(_listeningAddress);
}

void Network::Manager::startTcp()
{
    if (_sender.has_value()) {
        _sender.reset();
    }
    _sender.emplace(_targetAddress);
}

void Network::Manager::startUdp()
{
    if (_listener.has_value()) {
        _listener.reset();
    }
    _listener.emplace(_listeningAddress);
}

void Network::Manager::stopTcp()
{
    if (_sender.has_value()) {
        _sender.reset();
    }
}

void Network::Manager::stopUdp()
{
    if (_listener.has_value()) {
        _listener.reset();
    }
}

void Network::Manager::setServerAddress(const Network::AddressHolder &addressHolder)
{
    _serverAddress = addressHolder;
}

void Network::Manager::connectToServer()
{
    if (_server.has_value()) {
        _server.reset();
    }
    _server.emplace(_serverAddress);
}

const bool Network::Manager::isServerOpen() const
{
    if (_server.has_value()) {
        return true;
    }
    return false;
}

const std::vector<std::string> Network::Manager::getCommunicationLinks() const
{
    std::vector<std::string> links;
    if (_sender.has_value()) {
        links.push_back("TCP");
    }
    if (_listener.has_value()) {
        links.push_back("UDP");
    }
    return links;
}

const std::vector<Network::Packet> Network::Manager::getUdpReceivedData()
{
    if (_listener.has_value()) {
        return _listener->getPackets();
    }
    return {};
}

const std::vector<Network::Packet> Network::Manager::getTcpReceivedData()
{
    if (_sender.has_value()) {
        return _sender->getPackets();
    }
    return {};
}

void Network::Manager::sendUdpData(const std::vector<Network::Packet> &data)
{
    if (_listener.has_value()) {
        _listener->send(data);
    }
}

void Network::Manager::sendTcpData(const std::vector<Network::Packet> &data)
{
    if (_sender.has_value()) {
        _sender->send(data);
    }
}

const bool Network::Manager::isTcpOpen() const
{
    if (_sender.has_value()) {
        return true;
    }
    return false;
}

const bool Network::Manager::isUdpOpen() const
{
    if (_listener.has_value()) {
        return true;
    }
    return false;
}


const std::string Network::Manager::getInfo(const unsigned int indent) const
{
    std::string indentation = "";
    for (unsigned int i = 0; i < indent; ++i) {
        indentation += "\t";
    }
    std::string result = indentation + "Network Manager:\n";
    result += indentation + "\tTCP Address: " + _targetAddress.getInfo(indent + 1) + "\n";
    result += indentation + "\tUDP Address: " + _listeningAddress.getInfo(indent + 1) + "\n";
    if (_sender.has_value()) {
        result += indentation + "\tTCP Open: Yes\n";
    } else {
        result += indentation + "\tTCP Open: No\n";
    }
    if (_listener.has_value()) {
        result += indentation + "\tUDP Open: Yes\n";
    } else {
        result += indentation + "\tUDP Open: No\n";
    }
    return result;
}

const Network::AddressHolder Network::Manager::getTcpAddress() const
{
    return _targetAddress;
}

const Network::AddressHolder Network::Manager::getUdpAddress() const
{
    return _listeningAddress;
}

std::ostream &Network::operator<<(std::ostream &os, const Network::Manager &item)
{
    os << item.getInfo();
    return os;
}
