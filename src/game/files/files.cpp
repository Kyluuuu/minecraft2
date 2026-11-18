#pragma once

#include <windows.h>
#include <shlobj.h>
#include <iostream>
#include <fstream>
#include "files.hpp"
#include <format>

std::filesystem::path minecraftDirectory;
std::filesystem::path globalSettings;
std::filesystem::path worldsDirectory;

// Can throw error while create folders
void Files::initFiles()
{
    PWSTR homeDir = nullptr;
    HRESULT hr = SHGetKnownFolderPath(FOLDERID_Profile, 0, NULL, &homeDir);

    if (FAILED(hr))
    {
        throw std::runtime_error(std::format(
            "Failed to get home folder: ERROR: 0x{:08X}",
            static_cast<unsigned long>(hr)));
    }

    minecraftDirectory =
        static_cast<std::filesystem::path>(homeDir) / "Appdata" / "Roaming" / ".minecraft2";
    CoTaskMemFree(homeDir);

    globalSettings = minecraftDirectory / "Settings" / "settings.json";
    worldsDirectory = minecraftDirectory / "Worlds";

    std::filesystem::create_directories(globalSettings.parent_path());
    std::filesystem::create_directories(worldsDirectory);
}

// can throw exception
Json Files::getJsonFile(std::filesystem::path &file)
{
    std::ifstream fileToRead(file);
    if (!fileToRead.is_open())
    {
        throw std::runtime_error(std::format(
            "Failed to open file {}",
            file.string()));
    }

    return Json::parse(fileToRead);
}

//Hard code variables and types in definition table
//have case switch that will read each var in json and store as appropriate type
//store all settings and then watch for updates and update data as it changes
//when chnages happen, send data to appriopriate places
// to do this either have pub sub system or hard code the pub sub basically
// hard code can read from a config file or just a coded config basically

// how does data from fileLoader get to world for example?
// if new settngs are added that will be touched by world how to add this easily?

// get a value
// std::string username = settings["username"];
// get a value with default
// int volume = settings.value("volume", 100);
// set a value
// settings["volume"] = 50;
// settings["fullscreen"] = false;
// settings["username"] = "NewUser";
// add a value
// settings["vsync"] = true;

// write back to file
// std::ofstream file("settings.json");
// file << settings.dump(4);