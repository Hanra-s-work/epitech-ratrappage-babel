/*
** EPITECH PROJECT, 2024
** epitech-ratrappage-babel (Workspace)
** File description:
** RealMain.hpp
*/


/**
 * @file RealMain.hpp
 * @brief This is the file in charge of containing the main class and other ressources at the root of the program
 */

#include <string>
#include <iostream>
#include <vector>
#include "Logging.hpp"
#include "MainClass.hpp"
#include "Constants.hpp"
#include "CustomExceptions.hpp"

int RealMain(int argc, char **argv);
void DisplayHelp(const std::string binName);
void DisplayVersion(bool helpMode = false);
