/*
** EPITECH PROJECT, 2024
** epitech-ratrappage-babel (Workspace)
** File description:
** Compressor.cpp
*/

/**
 * @file Compressor.cpp
 * @brief Implementation of the Audio::Compressor class.
 */

#include "Audio/Compressor.hpp"

Audio::Compressor::Compressor()
{
}

Audio::Compressor::~Compressor()
{
}

std::optional<std::any> Audio::Compressor::compressAudio(const Node &node)
{
    PRETTY_WARNING << "Audio compression is not implemented yet." << std::endl;
    return std::nullopt;
}

const Audio::Node Audio::Compressor::decompressAudio(const std::any &stream)
{
    PRETTY_WARNING << "Audio decompression is not implemented yet." << std::endl;
    return Node();
}

void Audio::Compressor::update(const Audio::Compressor &copy)
{
    PRETTY_WARNING << "Compressor update is not implemented yet." << std::endl;
}

const std::string Audio::Compressor::getInfo(const unsigned int indent) const
{
    std::string indentation = "";
    for (unsigned int i = 0; i < indent; ++i) {
        indentation += "\t";
    }
    std::string result = indentation + "Audio Compressor:\n";

    return result;
}

Audio::Compressor &Audio::Compressor::operator =(const Audio::Compressor &copy)
{
    update(copy);
    return *this;
}

std::ostream &Audio::operator<<(std::ostream &os, const Audio::Compressor &compressor)
{
    os << compressor.getInfo();
    return os;
}
