// Glad needs to be included first
#include <iostream>
#include <format>

#include "files/files.hpp"
#include "../logger/Logger.hpp"

#include <RmlUi/Core.h>
#include "RmlUi_Backend.h"

#define WINDOWNAME "window"

enum shutdownLevel
{
    BACKEND,
    RML,
    CONTEXT
};

uint8_t shutdown(shutdownLevel level)
{
    switch (level)
    {
    case shutdownLevel::CONTEXT:
        Rml::RemoveContext(WINDOWNAME);
        [[fallthrough]];
    case shutdownLevel::RML:
        Rml::Shutdown();
        [[fallthrough]];
    case shutdownLevel::BACKEND:
        Backend::Shutdown();
    }
    Logger::info("Shut down application");
    return 1;
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

    // TODO load from settings file
    constexpr int width = 1020;
    constexpr int height = 720;

    // handles window and opengl
    if (!Backend::Initialize("minecraft", width, height, true))
    {
        Logger::error("Failed to initialise RmlUi backend");
        return 1;
    }
    Logger::info("Initialised RmlUi Backend");

    // Connect RmlUi to the backend's system and rendering interfaces.
    Rml::SetSystemInterface(Backend::GetSystemInterface());
    Rml::SetRenderInterface(Backend::GetRenderInterface());

    if (!Rml::Initialise())
    {
        Logger::error("Failed to initialise RmlUi");
        return shutdown(shutdownLevel::BACKEND);
        return 1;
    }
    Logger::info("Initialised RmlUi");

    // Create the UI context.
    Rml::Context *context = Rml::CreateContext(
        "main",
        Rml::Vector2i(width, height));

    if (!context)
    {
        Logger::error("Failed to create RmlUi context");
        return shutdown(shutdownLevel::RML);
    }
    Logger::info("Created RmlUi context");

    Rml::ElementDocument *crosshair = context->LoadDocument("../assets/ui/hud.rml");
    if (!crosshair)
    {
        Logger::error("Failed to create crosshair");
        return 1;
    }
    crosshair->Show();

    Files fileLoader;
    World world(seed, fileLoader);

    // Main application loop.
    while (Backend::ProcessEvents(context))
    {


        context->Update();
        Backend::BeginFrame();
        context->Render();
        Backend::PresentFrame();
    }

    shutdown(shutdownLevel::CONTEXT);
    return 0;
}
