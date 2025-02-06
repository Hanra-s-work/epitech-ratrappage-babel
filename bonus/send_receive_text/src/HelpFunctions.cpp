/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** HelpFunctions.cpp
*/

/**
 * @file HelpFunctions.cpp
 *
 * @brief This is the file in charge of displaying the help message.
 */

#include <iostream>
#include "RealMain.hpp"

 /**
  * @brief Display the Usage section of the help prompt.
  *
  * @param binName Name of the executable binary.
  */
static void displayUsageSummary(const std::string binName)
{
    std::cout << "USAGE:\n";
    std::cout << "\t" << binName << " [--server-ip] [--server-port]";
    std::cout << " [--log] [--debug]";
    std::cout << " [--help] [--version]";
    std::cout << " [--username] [--echo]";
    // std::cout << " [--config-file]";
    std::cout << std::endl;
}

/**
 * @brief Display the Options section of the help prompt.
 */
static void displayDetailedUsage()
{
    std::cout << "OPTIONS:\n";
    std::cout << "\t--ip=\"" << Recoded::myToString(DEFAULT_IP) << "\"              \tSet the IP address for the server. (Default value: " << Recoded::myToString(DEFAULT_IP) << ")\n";
    std::cout << "\t--port=\"" << Recoded::myToString(DEFAULT_PORT) << "\"                 \tSet the port number for the server. (Default value: " << Recoded::myToString(DEFAULT_PORT) << ")\n";
    std::cout << "\t--log                           \tEnable logging.\n";
    std::cout << "\t--debug                         \tEnable debug logging. (if this option is provided, the --log flag becomes forced regardless of it being provided or not)\n";
    std::cout << "\t--help                          \tDisplay this help message and exit.\n";
    std::cout << "\t--version                       \tDisplay the version of the program and exit.\n";
    std::cout << "\t--username=\"" << Recoded::myToString(DEFAULT_USERNAME) << "\"         \tSet the name of the caller that is going to connect (Default value: \"" << Recoded::myToString(DEFAULT_USERNAME) << "\")\n";
    std::cout << "\t--echo                          \tEnable echoing of the user's input in the prompt.\n";
    // std::cout << "\t--config-file=\"config.toml\"   \tSet the path to the TOML file that contains the same configuration as what you could pass as the flags to load. (Default value: client_config.toml)\n";
    std::cout << std::endl;
}

/**
 * @brief Display the Author section of the help prompt.
 */
static void displayAuthors()
{
    std::cout << "AUTHORS:\n";
    std::cout << "This program was created for an Epitech ";
    std::cout << "project by students of the Epitech school.\n";
    std::cout << "This binary (babel) ";
    std::cout << "was written by:\n";
    std::cout << "\t-\tHenry Letellier              : https://github.com/HenraL\n";
    std::cout << std::endl;
}

/**
 * @brief Displays version information for the program.
 *
 * @param helpMode If true, will prepend a 'VERSION:\\n' string to the output (default: false).
 */
void DisplayVersion(bool helpMode)
{
    if (helpMode) {
        std::cout << "VERSION:\n";
    }
    std::cout << "The program's version is: " << VERSION << std::endl;
}

/**
 * @brief The main function of the help display.
 *
 * @param binName Name of the executable binary.
 */
void DisplayHelp(const std::string binName)
{
    displayUsageSummary(binName);
    std::cout << std::endl;
    displayDetailedUsage();
    std::cout << std::endl;
    displayAuthors();
    std::cout << std::endl;
    DisplayVersion(true);
}
