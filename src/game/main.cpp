// Glad needs to be included first
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <format>
#include "files/files.hpp"
#include "../logger/Logger.hpp"

// ui includes
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

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

    try
    {
        Files::initFiles();
    }
    catch (const std::runtime_error &e)
    {
        std::cerr << "Failed to initialise files: " << e.what() << std::endl;
    }

    try
    {
        Logger::init();
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

    // setup imgui ui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(glfwCreateWindow(720, 1020, "game", nullptr, nullptr), true); // Second param install_callback=true will install GLFW callbacks and chain to existing ones.
    ImGui_ImplOpenGL3_Init();

    while (true)
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        _sleep(3000);
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();
    Logger::info("Terminated glfw");
    return 0;
}

// main flow
// main funciton is entered
// load
// settings are from the UI, but cant be started without the window but
// changes made in the ui need to restart the window
