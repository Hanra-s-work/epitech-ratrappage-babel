/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** ToString.cpp
*/

/**
 * @file ToString.cpp
 *
 * @brief This is the file that will contain the code for the ToString rebind.
 */

#include "Recoded/ToString.hpp"

const std::string Recoded::myToString(bool value, const unsigned int indent)
{
    std::string indentation(indent, '\t');
    if (value) {
        return indentation + "true";
    }
    return indentation + "false";
};

const std::string Recoded::myToString(const std::string &value, const unsigned int indent)
{
    std::string indentation(indent, '\t');
    return indentation + value;
};

const std::string Recoded::myToString(const Audio::StreamData &value, const unsigned int indent)
{
    std::string indentation(indent, '\t');
    std::string result = indentation + "Stream Data:\n";
    result += indentation + "- Duration: '" + Recoded::myToString(value.duration) + "'\n";
    result += indentation + "- Samples: {\n" + Recoded::myToString(value.samples, indent + 1) + indentation + "}\n";
    return result;
};
