// Glad needs to be included first
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <format>
#include "settings/settings.hpp"
#include "../logger/Logger.hpp"

void error_callback(int code, const char *desc)
{
    Logger::error(std::format(
        "ERROR: {}, with error code {}",
        desc ? desc : "unknown",
        code));
}

void thread_callback()
{
}

int main()
{
#ifndef _WIN32
    std::cerr << "Not running windows!" << std::endl;
    return 1;
#endif

    if (!Files::setUpFiles())
    {
        std::cerr << "Failed to initialise files" << std::endl;
        return 1;
    }

    try
    {
        Logger::init(std::string(Files::logFolder));
    }
    catch (const std::runtime_error &e)
    {
        std::cerr << std::format("Error starting logger, ERROR: {}", e.what());
        return 1;
    }
    Logger::info("Initialised logger");

    glfwSetErrorCallback(error_callback);
    Logger::info("Initialised glfw error callback");

    if (!glfwInit())
    {
        Logger::error("Failed to init glfw");
        return 1;
    }
    Logger::info("Initialised glfw");

    glfwTerminate();
    Logger::info("Terminated glfw");
    return 0;
}

// main enters
// settings are from the UI, but cant be started without the window but
// changes made in the ui need to restart the window
