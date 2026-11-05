// Glad needs to be included first
#include <glad/glad.h>  //opengl api
#include <GLFW/glfw3.h> //window and operating system api
#include <iostream>
#include <format>
#include "files/files.hpp"
#include "../logger/Logger.hpp"

// ui includes
void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

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

int main(int argc, char *argv[])
{
#ifndef _WIN32
    std::cerr << "Not running windows!" << std::endl;
    return 1;
#endif

    try
    {
        for (int i = 1; i < argc; i++)
        {
            std::string arg = argv[i];
            std::cout << arg << std::endl;
        }
        Files::initFiles();
        Logger::init();
    }
    catch (const std::runtime_error &e)
    {
        std::cerr << "Failed to initialise: " << e.what() << std::endl;
        return 1;
    }
    Logger::info("Initialised logger");

    if (!glfwInit())
    {
        Logger::error("Failed to init glfw");
        return 1;
    }
    Logger::info("Initialised glfw");

    int w = 1020;
    int h = 720;

    // sets opengl window version to 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // want core opengl profile
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwSetErrorCallback(error_callback);

    GLFWwindow *window = glfwCreateWindow(w, h, "game", nullptr, nullptr);
    if (!window)
    {
        Logger::error("Failed to init window");
        return 1;
    }
    Logger::info("Initialised window");
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        Logger::error("Failed to initialise GLAD");
        return 1;
    }
    Logger::info("Initialised GLAD");

    glfwGetFramebufferSize(window, &w, &h); // is called in the callBack but might not have been called yet
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glViewport(0, 0, w, h);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    while (!glfwWindowShouldClose(window))
    {
        // get os events like mouse shit
        glfwPollEvents();

        // clears the previous frame
        glClear(GL_COLOR_BUFFER_BIT);

        // this is the buffer to load the window
        //  once the frame is loaded then we swap the buffer to the monitor to display it
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    Logger::info("Terminated glfw");
    return 0;
}
