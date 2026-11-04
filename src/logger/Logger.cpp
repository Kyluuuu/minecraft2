#include "Logger.hpp"
#include <iostream>
#include <filesystem>
#include <fstream>
#include <chrono>
#include <iomanip>
#include <ctime>

std::ofstream Logger::s_file;
std::mutex Logger::s_mutex;
const std::filesystem::path logPath{"logs"};

void Logger::init()
{
    std::lock_guard<std::mutex> lock(s_mutex);

    std::filesystem::create_directories(logPath);

    const auto logFile = logPath / (getTimeString() + ".txt");

    s_file.open(logFile, std::ios::out | std::ios::app);

    if (!s_file.is_open())
        throw std::runtime_error("Failed to open log file");
}

void Logger::debug(std::string_view message)
{
    log(Level::DEBUG, message);
}

void Logger::info(std::string_view message)
{
    log(Level::INFO, message);
}

void Logger::warn(std::string_view message)
{
    log(Level::WARN, message);
}

void Logger::error(std::string_view message)
{
    log(Level::ERROR, message);
}

std::string Logger::getTimeString(const char *levelName, std::string_view &message)
{
    const auto now = std::chrono::system_clock::now();
    const std::time_t time = std::chrono::system_clock::to_time_t(now);

    std::tm timestamp{};

    // ctime function converting to local time and writes into timestamp
    localtime_s(&timestamp, &time);
    std::ostringstream output;

    output << std::put_time(&timestamp, "%Y-%m-%d %H:%M:%S")
           << " [" << levelName << "] "
           << message;

    return output.str();
}

std::string Logger::getTimeString()
{
    const auto now = std::chrono::system_clock::now();
    const std::time_t time = std::chrono::system_clock::to_time_t(now);

    std::tm timestamp{};

    // ctime function converting to local time and writes into timestamp
    localtime_s(&timestamp, &time);
    std::ostringstream output;

    output << std::put_time(&timestamp, "%Y-%m-%d_%H-%M-%S");

    return output.str();
}

void Logger::log(Level level, std::string_view message)
{
    std::lock_guard<std::mutex> lock(s_mutex);

    const char *levelName = "";

    switch (level)
    {
    case Level::DEBUG:
        levelName = "DEBUG";
        break;
    case Level::INFO:
        levelName = "INFO";
        break;
    case Level::WARN:
        levelName = "WARN";
        break;
    case Level::ERROR:
        levelName = "ERROR";
        break;
    }

    if (s_file.is_open())
    {
        s_file << getTimeString(levelName, message) << '\n';
        s_file.flush();
    }
}
