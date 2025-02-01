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

void Network::Manager::update(const Network::Manager &copy)
{
    PRETTY_WARNING << "Network Manager update is not implemented yet." << std::endl;
}

const std::string Network::Manager::getInfo(const unsigned int indent) const
{
    std::string indentation = "";
    for (unsigned int i = 0; i < indent; ++i) {
        indentation += "\t";
    }
    std::string result = indentation + "Network Manager:\n";

    return result;
}


Network::Manager &Network::Manager::operator =(const Network::Manager &copy)
{
    update(copy);
    return *this;
}


std::ostream &Network::operator<<(std::ostream &os, const Network::Manager &item)
{
    os << item.getInfo();
    return os;
}
