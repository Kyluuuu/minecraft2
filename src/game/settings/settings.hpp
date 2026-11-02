#pragma once
#include <string>

class Files
{
public:
    static int setUpFiles();
    inline static constexpr std::string_view logFolder = "../../../logs";

private:
};