/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** Log.hpp
*/

/**
 * @file Log.hpp
 * @brief This file contains the Log class responsible for outputting information only when requested.
 */

#pragma once
#include <ctime>
#include <mutex>
#include <string>
#include <chrono>
#include <sstream>
#include <iomanip>
#include <iostream>
#ifdef _WIN32
    #include <io.h>
    #include <windows.h>
    #define isatty _isatty
    #define fileno _fileno
#else
    #include <unistd.h>
#endif
#include "Utilities/OperatorRebind.hpp"

namespace Logging
{
    /**
     * @class Log
     * @brief A singleton class that provides thread-safe logging capabilities
     * with timestamps, active only when logging and debug outputs only when debugging and logging is enabled.
     */
    class Log {
        public:
        /**
         * @brief Provides access to the singleton instance of the `Log` class.
         *
         * @param debug A variable to indicate whether the string that is passed is a debug string.
         * @return Reference to the `Log` instance.
         */
        static Log &getInstance(const bool debug = false);

        /**
         * @brief Generates a formatted debug information string with file, line, and function details.
         *
         * @param file The name of the file where the debug information is generated.
         * @param line The line number where the debug information is generated.
         * @param func The name of the function where the debug information is generated.
         * @return A formatted string containing the debug information.
         */
        std::string getLogLocation(const char *file, int line, const char *func);

        /**
         * @brief Enables or disables logging.
         *
         * @param enabled Set to `true` to enable logging; `false` to disable.
         */
        void setLogEnabled(bool enabled);

        /**
         * @brief Enables or disables debug logging.
         *
         * @param enabled Set to `true` to enable debugging; `false` to disable.
         */
        void setDebugEnabled(bool enabled);

        /**
         * @brief Checks if logging is enabled.
         *
         * @return `true` if logging is enabled; `false` otherwise.
         */
        const bool getLogEnabled() const;

        /**
         * @brief Checks if debug logging is enabled.
         *
         * @return `true` if debug logging is enabled; `false` otherwise.
         */
        const bool getDebugEnabled() const;

        /**
         * @brief Logs a message if logging is enabled.
         *
         * @param message The message to log.
         */
        void log(const std::string &message);

        /**
         * @brief Logs a message if logging is enabled.
         *
         * @param message A C-string containing the message to log.
         */
        void log(const char *message);

        /**
         * @brief Appends a message to the log if logging is enabled.
         *
         * @tparam T The type of the message.
         * @param message The message to log.
         * @return Reference to the `Log` instance for chaining.
         *
         * @warning Do not try to initialize it outside of the header file
         * or compilation issues will occur.
         */
        template <typename T>
        Log &operator<<(const T &message)
        {
            if (_logEnabled) {
                std::lock_guard<std::mutex> lock(_mtx);
                _buffer << message;
            }
            return *this;
        };

        /**
         * @brief Appends a string message to the log if logging is enabled.
         *
         * @param message The string message to log.
         * @return Reference to the `Log` instance for chaining.
         *
         * @warning Do not try to initialize it outside of the header file
         * or compilation issues will occur.
         */
        Log &operator<<(const std::string &message)
        {
            if (_logEnabled) {
                std::lock_guard<std::mutex> lock(_mtx);
                _buffer << message;
            }
            return *this;
        };

        /**
         * @brief Handles special stream manipulators (e.g., `std::endl`)
         * for logging with timestamps if logging is enabled.
         *
         * @param os The stream manipulator to apply.
         * @return Reference to the `Log` instance for chaining.
         *
         * @warning Do not try to initialize it outside of the header file
         * or compilation issues will occur.
         */
        Log &operator<<(std::ostream &(*os)(std::ostream &))
        {
            if (_logEnabled) {
                std::lock_guard<std::mutex> lock(_mtx);
                if (os == static_cast<std::ostream & (*)(std::ostream &)>(std::endl)) {
                    log(_buffer.str());
                    _buffer.str("");
                    _buffer.clear();
                } else {
                    os(_buffer);
                }
            }
            return *this;
        };

        /**
         * @brief Retrieves the current date and time as a formatted string.
         *
         * @return The current date and time in "YYYY-MM-DD HH:MM:SS" format.
         */
        std::string getCurrentDateTime();

        /**
         * @brief Sets the internal boolean `_stringDebug`.
         *
         * @note This variable indicates whether the current string is a debug string.
         *
         * @param stringDebug Set to `true` if the string is a debug string; `false` otherwise.
         */
        void setStringAsDebug(const bool stringDebug = false);

        private:
        bool _stringDebug = false;                //!< Indicates whether the current instance is for a debug string.
        bool _logEnabled = false;                 //!< Indicates whether logging is enabled.
        bool _debugEnabled = false;               //!< Indicates whether debugging is enabled.
        std::mutex _mtx;                          //!< Ensures thread-safe access to the logging buffer from within the operators.
        std::mutex _mtxLog;                       //!< Ensures thread-safe access to the logging buffer from within the log function.
        std::ostringstream _buffer;               //!< Buffer for accumulating messages before output.

        /**
         * @brief Private constructor for singleton pattern. Logging is disabled by default.
         */
        Log() : _debugEnabled(false) {}

        Log(const Log &) = delete;            //!< Deleted copy constructor.
        Log &operator=(const Log &) = delete; //!< Deleted assignment operator.

    };

    /**
     * @brief Checks if the output is being redirected to a file.
     *
     * @return `true` if the output is being redirected to a file; `false` otherwise.
     */
    inline bool isRedirected()
    {
        return !isatty(fileno(stdout));
    }
}
