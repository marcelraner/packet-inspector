#ifndef DEVICE_HPP
#define DEVICE_HPP

#include <string>
#include <vector>

/**
 * Holds application settings
 * 
 * This class holds all the application settings. It initializes the settings
 * with default values and offers a method to load the settings from a file.
 */
class Settings
{
private:
    std::string device = "eth0";
    bool promiscuous_mode = false;
    std::vector<std::vector<unsigned char>> patterns;
public:
    /** Specifies return values for methods form class Settings */ 
    enum ErrorCode
    {
        Ok,
        NoSuchFile
    };
    enum ErrorCode load_settings_from_file(std::string filename);
    std::string get_device();
    bool get_promiscuous_mode();
    std::vector<std::vector<unsigned char>>& get_patterns();
};

#endif // DEVICE_HPP
