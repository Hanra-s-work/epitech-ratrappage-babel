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

Logging::Log &Logging::Log::getInstance(const bool debug)
{
    static Logging::Log instance;
    instance.setStringAsDebug(debug);
    return instance;
}

std::string Logging::Log::getLogLocation(const char *file, int line, const char *func)
{
    std::ostringstream oss;
    oss << file << ":" << line << " " << func << "()";
    return oss.str();
}

void Logging::Log::setLogEnabled(bool enabled)
{
    _logEnabled = enabled;
}

void Logging::Log::setDebugEnabled(bool enabled)
{
    _debugEnabled = enabled;
}

const bool Logging::Log::getLogEnabled() const
{
    return _logEnabled;
}

const bool Logging::Log::getDebugEnabled() const
{
    return _debugEnabled;
}

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

void Logging::Log::log(const char *message)
{
    log(std::string(message));
}

void Logging::Log::setStringAsDebug(const bool stringDebug)
{
    _stringDebug = stringDebug;
}

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
