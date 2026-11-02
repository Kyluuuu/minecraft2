#pragma once

#include <string>
#include <string_view>
#include <fstream>
#include <mutex>

class Logger
{
public:
    enum class Level
    {
        DEBUG,
        INFO,
        WARN,
        ERROR
    };

    static void init(const std::string &filepath);

    static void debug(std::string_view message);
    static void info(std::string_view message);
    static void warn(std::string_view message);
    static void error(std::string_view message);

private:
    static std::ofstream s_file;
    static std::mutex s_mutex;

    static void log(Level level, std::string_view message);
};