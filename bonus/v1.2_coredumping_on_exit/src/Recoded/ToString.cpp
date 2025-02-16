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

 /**
  * @brief Converts a boolean value to its string representation.
  *
  * @param value The boolean value to convert.
  * @return "true" if the value is true, otherwise "false".
  */
const std::string Recoded::myToString(bool value)
{
    if (value) {
        return "true";
    }
    return "false";
};
