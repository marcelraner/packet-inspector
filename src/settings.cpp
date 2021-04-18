#include "settings.hpp"

#include "logging.hpp"

#include <fstream>
#include <string>
#include <iostream>

/**
 * A method for loading settings from a file.
 * 
 * @param filename Path of the settings file.
 * 
 * @return Return/Error code.
 */
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

        if (parameter == "pattern")
        {
            if (value.size() > 0)
            {
                //TRACE(value);
                std::vector<unsigned char> pattern(value.begin(), value.end());
                /*for (unsigned int i = 0; i < pattern.size(); i++)
                {
                    TRACE(std::to_string(pattern[i]));
                }*/
                this->patterns.push_back(pattern);
            }
        }
    }

    settings_ifstream.close();

    return Settings::ErrorCode::Ok;
}

/**
 * Getter for the device name
 * 
 * @return Device name
 */
std::string Settings::get_device()
{
    return this->device;
}

/**
 * Getter for the promiscuous mode
 * 
 * @return Promiscuous mode
 */
bool Settings::get_promiscuous_mode()
{
    return this->promiscuous_mode;
}

/**
 * Getter for the patterns
 * 
 * @return Patterns vector
 */
std::vector<std::vector<unsigned char>>& Settings::get_patterns()
{
    return this->patterns;
}
