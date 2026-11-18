#pragma once

#include <nlohmann/json.hpp>
#include <filesystem>

using Json = nlohmann::json;

class Files
{
public:
    static void initFiles();
    static Json getJsonFile(std::filesystem::path &file);

private:
};


//What needs file data?
//if changing settings like 