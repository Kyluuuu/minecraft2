#include <windows.h>
#include <shlobj.h>
#include <iostream>
#include <filesystem>
#include "settings.hpp"

std::filesystem::path homeDirectory;
std::filesystem::path 

int setUpFiles()
{
    PWSTR homeDir = nullptr;
    HRESULT hr = SHGetKnownFolderPath(FOLDERID_Profile, 0, NULL, &homeDir);

    if (FAILED(hr))
    {
        std::cerr << "Failed to get home directory." << std::endl;
        return 1;
    }

    homeDirectory = homeDir;
    CoTaskMemFree(homeDir);


    return 0;
}
