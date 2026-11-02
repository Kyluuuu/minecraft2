#include "Logger.hpp"
#include <iostream>
#include <filesystem>
#include <chrono>
#include <iomanip>
#include <ctime>

std::ofstream Logger::s_file;
std::mutex Logger::s_mutex;

void Logger::init(const std::string &filepath)
{
    
    std::lock_guard<std::mutex> lock(s_mutex);

    std::filesystem::path path(filepath);

    if (!path.parent_path().empty())
        std::filesystem::create_directories(path.parent_path());

    s_file.open(filepath, std::ios::out | std::ios::app);

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

void Logger::log(Level level, std::string_view message)
{
    std::lock_guard<std::mutex> lock(s_mutex);

    const auto now = std::chrono::system_clock::now();
    const std::time_t time = std::chrono::system_clock::to_time_t(now);

    std::tm timestamp{};

    localtime_s(&timestamp, &time);

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

    std::ostringstream output;

    output << std::put_time(&timestamp, "%Y-%m-%d %H:%M:%S")
           << " [" << levelName << "] "
           << message;

    const std::string entry = output.str();

    std::cout << entry << '\n';

    if (s_file.is_open())
    {
        s_file << entry << '\n';
        s_file.flush();
    }
}