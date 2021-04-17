#include "settings.hpp"

#include <fstream>
#include <string>
#include <iostream>

enum Settings::ErrorCode Settings::load_settings_from_file(const std::string filename)
{
    std::ifstream settings_ifstream(filename);

    if (!settings_ifstream.is_open())
    {
        return Settings::ErrorCode::NoSuchFile;
    }

    std::string line;
    while (std::getline(settings_ifstream, line))
    {
        size_t delimiter_position = line.find('=');
        if (delimiter_position == std::string::npos)
        {
            std::string error_message = "Invalid settings file";
            throw std::runtime_error(error_message);
        }
        std::string parameter = line.substr(0, delimiter_position);
        std::string value = line.substr(delimiter_position + 1, line.length());

        if (parameter == "device")
        {
            this->device = value;
        }

        if (parameter == "promiscuous_mode")
        {
            if (value == "0")
            {
                this->promiscuous_mode = false;
            }
            else if (value == "1")
            {
                this->promiscuous_mode = true;
            }
        }  
    }

    settings_ifstream.close();

    return Settings::ErrorCode::Ok;
}

std::string Settings::get_device() {
    return this->device;
}
bool Settings::get_promiscuous_mode() {
    return this->promiscuous_mode;
}
