/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** RealMain.cpp
*/

/**
 * @file RealMain.cpp
 *
 * @brief Entry point for processing command-line arguments and running the main application logic.
 */

#include "RealMain.hpp"

 /**
 * @brief Extracts the flag and value from a command-line argument.
 *
 * This function parses a command-line argument to split it into a flag and value.
 * For example, if the argument is `--key=value`, it will return a tuple `("key", "value")`.
 * If there is no `=` sign, it returns the flag with an empty value.
 *
 * @param arg The command-line argument as a C-style string.
 * @return A vector containing the flag (as the first element) and the value (as the second element).
 */
std::vector<std::string> extract_argument(char *arg)
{
    PRETTY_INFO << "Extracting arguments" << std::endl;
    std::string arg_str(arg);
    size_t pos = arg_str.find('=');
    std::string flag = "";
    std::string value = "";
    std::vector<std::string> resp;

    if (pos != std::string::npos) {
        flag = arg_str.substr(0, pos);
        value = arg_str.substr(pos + 1);
    } else {
        flag = arg_str;
        value = "";
    }

    if (flag.find("--") == 0) {
        flag = flag.substr(2);
    } else if (flag.find("-") == 0) {
        flag = flag.substr(1);
    } else if (flag.find("/") == 0) {
        flag = flag.substr(1);
    }

    resp.push_back(flag);
    resp.push_back(value);

    return resp;
}

/**
 * @brief Process the single argument that is provided.
 *
 * @param main The main class, initialised.
 * @param args The current argument.
 * @param binName The name of the program binary.
 *
 * @throws CustomExceptions::HelpFound This is an information that allows the program to know that the help flag was passed.
 * @throws CustomExceptions::VersionFound This is an information that allows the program to know that the version flag was passed.
 * @throws CustomExceptions::InvalidPort This is an error informing the user that the port value they passed is invalid.
 * @throws CustomExceptions::NoFlagParameter This is an error informing the user that a parameter was expected for the flag but was not found.
 * @throws CustomExceptions::UnknownArgument This is an error informing the user that the flag they passed is unknown.
 * @throws CustomExceptions::InvalidFrameLimit This is an error informing the user that the frame limit that was passed is invalid.
 * @throws CustomExceptions::InvalidWindowWidth This is an error informing the user that the value for the window's width is invalid.
 * @throws CustomExceptions::InvalidWindowHeight This is an error informing the user the the value for the window's height is invalid.
 */
void process_given_argument(Main &main, const std::vector<std::string> &args, std::string const &binName)
{
    if (args[0] == "help" || args[0] == "h" || args[0] == "?") {
        DisplayHelp(binName);
        throw CustomExceptions::HelpFound();
    } else if (args[0] == "version" || args[0] == "v") {
        DisplayVersion(false);
        throw CustomExceptions::VersionFound();
    } else if (args[0] == "ip" || args[0] == "i") {
        PRETTY_SUCCESS << "Ip is provided: '" << args[1] << "'" << std::endl;
        if (args[1].empty()) {
            PRETTY_CRITICAL << "Error: Ip value is required" << std::endl;
            std::cerr << "Error: Ip value is required" << std::endl;
            throw CustomExceptions::NoFlagParameter(args[0]);
        }
        main.setIp(args[1]);
    } else if (args[0] == "port" || args[0] == "p") {
        PRETTY_SUCCESS << "Port is provided: '" << args[1] << "'" << std::endl;
        unsigned int port = 0;
        if (args[1].empty()) {
            PRETTY_CRITICAL << "Error: Port number is required" << std::endl;
            std::cerr << "Error: Port number is required" << std::endl;
            throw CustomExceptions::NoFlagParameter(args[0]);
        }
        try {
            port = static_cast<unsigned int>(std::stoul(args[1]));
        }
        catch (const std::invalid_argument &e) {
            PRETTY_CRITICAL << "Invalid argument: '" << args[1] << "' is not a valid number." << std::endl;
            std::cerr << "Invalid argument: '" << args[1] << "' is not a valid number." << std::endl;
            throw CustomExceptions::InvalidPort(args[1]);
        }
        catch (const std::out_of_range &e) {
            PRETTY_CRITICAL << "Out of range: '" << args[1] << "' is too large for an unsigned int." << std::endl;
            std::cerr << "Out of range: '" << args[1] << "' is too large for an unsigned int." << std::endl;
            throw CustomExceptions::InvalidPort(args[1]);
        }
        main.setPort(port);
    } else if (args[0] == "chunk-length" || args[0] == "cl" || args[0] == "chunklength") {
        PRETTY_SUCCESS << "chunk length is provided: '" << args[1] << "'" << std::endl;
        unsigned int chunkLength = MIN_RECORDING_LENGTH;
        if (args[1].empty()) {
            const std::string errMsg = "Error: Chunk length is required but not provided, defaulting de minimum length";
            PRETTY_WARNING << errMsg << std::endl;
            std::cerr << errMsg << std::endl;
            main.setDuration(chunkLength);
            return;
        }
        try {
            chunkLength = static_cast<unsigned int>(std::stoul(args[1]));
        }
        catch (const std::invalid_argument &e) {
            const std::string errMsg = "Invalid argument: '" + args[1] + "' is not a valid number.";
            PRETTY_CRITICAL << errMsg << std::endl;
            std::cerr << errMsg << std::endl;
            throw CustomExceptions::InvalidDuration(args[1], Recoded::myToString(MIN_RECORDING_LENGTH), Recoded::myToString(MAX_RECORDING_LENGTH));
        }
        catch (const std::out_of_range &e) {
            const std::string errMsg = "Out of range: '" + args[1] + "' is too large for an unsigned int.";
            PRETTY_CRITICAL << errMsg << std::endl;
            std::cerr << errMsg << std::endl;
            throw CustomExceptions::InvalidDuration(args[1], Recoded::myToString(MIN_RECORDING_LENGTH), Recoded::myToString(MAX_RECORDING_LENGTH));
        }
        main.setDuration(chunkLength);
    } else if (args[0] == "debug" || args[0] == "d") {
        main.setLog(true);
        main.setDebug(true);
        PRETTY_INFO << "Debug is True" << std::endl;
    } else if (args[0] == "echo" || args[0] == "e") {
        main.setEcho(true);
        PRETTY_INFO << "Echoing is True" << std::endl;
    } else if (args[0] == "config-file" || args[0] == "cf" || args[0] == "configfile") {
        PRETTY_INFO << "Config file is provided: '" << args[1] << "'" << std::endl;
        if (args[1].empty()) {
            std::cerr << "Error: TOML config file is required." << std::endl;
            throw CustomExceptions::NoFlagParameter(args[0]);
        }
        main.setConfigFile(args[1]);
    } else {
        throw CustomExceptions::UnknownArgument(args[0]);
    }
}

/**
 * @brief Processes the command-line arguments and applies them to the main application object.
 *
 * This function iterates through the provided command-line arguments, parses them using
 * `extract_argument`, and applies relevant changes to the application state.
 *
 * @param main A reference to the main application object.
 * @param argc The number of command-line arguments.
 * @param argv The array of command-line arguments as C-style strings.
 */
void process_arguments(Main &main, int argc, char **argv)
{
    unsigned int index = 1;
    PRETTY_INFO << "Dumping arguments" << std::endl;
    std::string binName(argv[0]);
    while (index < argc) {
        std::vector<std::string> arg = extract_argument(argv[index]);
        PRETTY_INFO << "Flag: '" << arg[0] << "', Value: '" << arg[1] << "'." << std::endl;
        process_given_argument(main, arg, binName);
        index++;
    }
}

/**
 * @brief The main function for initializing and running the application.
 *
 * This function serves as the entry point for the R-Type GUI application. It initializes the
 * main application object, processes command-line arguments, and starts the application's
 * execution loop. Exceptions are caught and logged, and an error code is returned if any
 * issues occur.
 *
 * @param argc The number of command-line arguments.
 * @param argv The array of command-line arguments as C-style strings.
 *
 * @return An integer status code: MY_SUCCESS (0) on successful execution, MY_ERROR (non-zero) on failure.
 */
int RealMain(int argc, char **argv)
{
    int status = MY_SUCCESS;
    bool help_found = false;
    bool version_found = false;

    Main MyMain("0.0.0.0", 9000, "Jon Doe", false, false);

    if (argc > 1) {
        try {
            process_arguments(MyMain, argc, argv);
        }
        catch (const CustomExceptions::HelpFound &e) {
            status = MY_SUCCESS;
            help_found = true;
            PRETTY_SUCCESS << "Help was found: '" << e.what() << "'." << std::endl;
        }
        catch (const CustomExceptions::VersionFound &e) {
            status = MY_SUCCESS;
            version_found = true;
            PRETTY_SUCCESS << "Version was found: '" << e.what() << "'." << std::endl;
        }
        catch (const std::exception &e) {
            status = MY_ERROR;
            PRETTY_CRITICAL << "An error occurred: '" << e.what() << "'." << std::endl;
            std::cerr << "An error occurred: '" << e.what() << "'." << std::endl;
        }
    }

    if (help_found || version_found || status == MY_ERROR) {
        PRETTY_INFO << "The program exited with status: " << status << std::endl;
        std::cout << RESET_COL << std::endl;
        return status;
    }

    if (!MyMain.getConfigFilePath().empty()) {
        try {
            MyMain.setConfigFile(MyMain.getConfigFilePath());
        }
        catch (const std::exception &e) {
            std::cerr << e.what() << std::endl;
            PRETTY_CRITICAL << "Failed to load the config file, aborting program." << std::endl;
            std::cout << RESET_COL << std::endl;
            return MY_ERROR;
        }
    }

    try {
        MyMain.takeOff();
    }
    catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        status = MY_ERROR;
    }
    PRETTY_INFO << "Exit status : '" << status << "'." << std::endl;
    std::cout << RESET_COL << std::endl;
    return status;
}
