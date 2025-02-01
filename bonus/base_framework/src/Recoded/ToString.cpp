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

const std::string Recoded::myToString(bool value)
{
    if (value) {
        return "true";
    }
    return "false";
};
