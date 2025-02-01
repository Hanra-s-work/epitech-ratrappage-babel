/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** Log.cpp
*/

/**
 * @file Log.cpp
 *
 * @brief This is the file in charge of managing the functions for the debug class
 */

#include "Logging/Log.hpp"

 /**
  * @brief Provides access to the singleton instance of the `Log` class.
  *
  * @param debug A variable to indicate whether the string that is passed is a debug string.
  * @return Reference to the `Log` instance.
  */
Logging::Log &Logging::Log::getInstance(const bool debug)
{
    static Logging::Log instance;
    // std::ios_base::sync_with_stdio(true); // Enable synchronization with C stdio
    std::ios_base::sync_with_stdio(false); // Disable synchronization with C stdio
    instance.setStringAsDebug(debug);
    return instance;
}

/**
 * @brief Private constructor for singleton pattern. Logging is disabled by default.
 */
Logging::Log::Log() : _debugEnabled(false) {}

/**
 * @brief Generates a formatted debug information string with file, line, and function details.
 *
 * @param file The name of the file where the debug information is generated.
 * @param line The line number where the debug information is generated.
 * @param func The name of the function where the debug information is generated.
 * @return A formatted string containing the debug information.
 */
std::string Logging::Log::getLogLocation(const char *file, int line, const char *func)
{
    std::ostringstream oss;
    oss << file << ":" << line << " " << func << "()";
    return oss.str();
}

/**
 * @brief Enables or disables logging.
 *
 * @param enabled Set to `true` to enable logging; `false` to disable.
 */
void Logging::Log::setLogEnabled(bool enabled)
{
    _logEnabled = enabled;
}

/**
 * @brief Enables or disables debug logging.
 *
 * @param enabled Set to `true` to enable debugging; `false` to disable.
 */
void Logging::Log::setDebugEnabled(bool enabled)
{
    _debugEnabled = enabled;
}

/**
 * @brief Checks if logging is enabled.
 *
 * @return `true` if logging is enabled; `false` otherwise.
 */
const bool Logging::Log::getLogEnabled() const
{
    return _logEnabled;
}

/**
 * @brief Checks if debug logging is enabled.
 *
 * @return `true` if debug logging is enabled; `false` otherwise.
 */
const bool Logging::Log::getDebugEnabled() const
{
    return _debugEnabled;
}

/**
 * @brief Logs a message if logging is enabled.
 *
 * @param message The message to log.
 */
void Logging::Log::log(const std::string &message)
{
    if (!_logEnabled) {
        return;
    }

    if (_stringDebug && !_debugEnabled) {
        return;
    }

    std::lock_guard<std::mutex> lock(_mtxLog);
    std::cout << getCurrentDateTime() << message << std::endl;
}

/**
 * @brief Logs a message if logging is enabled.
 *
 * @param message A C-string containing the message to log.
 */
void Logging::Log::log(const char *message)
{
    log(std::string(message));
}

/**
 * @brief Sets the internal boolean `_stringDebug`.
 *
 * @note This variable indicates whether the current string is a debug string.
 *
 * @param stringDebug Set to `true` if the string is a debug string; `false` otherwise.
 */
void Logging::Log::setStringAsDebug(const bool stringDebug)
{
    _stringDebug = stringDebug;
}

/**
 * @brief Retrieves the current date and time as a formatted string.
 *
 * @return The current date and time in "YYYY-MM-DD HH:MM:SS" format.
 */
std::string Logging::Log::getCurrentDateTime()
{
    auto now = std::chrono::system_clock::now();
    std::time_t currentTime = std::chrono::system_clock::to_time_t(now);
    auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(
        now.time_since_epoch()
    ).count() % 1000;

    std::tm *tm = std::localtime(&currentTime);

    std::stringstream ss;
    ss << "[" << (tm->tm_year + 1900) << "-"
        << (tm->tm_mon + 1) << "-"
        << tm->tm_mday << " "
        << tm->tm_hour << ":"
        << tm->tm_min << ":"
        << tm->tm_sec << "."
        << std::setfill('0') << std::setw(3) << millis << "]";
    return ss.str();
}
