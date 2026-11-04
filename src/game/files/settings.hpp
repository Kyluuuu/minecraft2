#include <cstdint>
#include <vector>
#include <variant>
#include <string>

// variable data type allowed options
using T = std::variant<
    uint8_t,
    std::string,
    bool,
    float,
    >;
class Option
{
    Option(T value)
    {
    }

    Option(T min, T value, T max)
    {
    }
};

class Settings
{
public:
    // will be called by ui save event
    bool writeSettingsToFile()
    {
        // return file.good();
    }

    bool readSettingsFromFile()
    {
    }

    bool setDefaultFile()
    {
    }

    Settings()
    {
        if (!readSettingsFromFile())
        {
        }
    }

private:
    std::vector<Option> options;
};
