#ifndef DEVICE_HPP
#define DEVICE_HPP

#include <string>

class Settings {
private:
    std::string device = "eth0";
    bool promiscuous_mode = false;
public:
    enum ErrorCode {
        Ok,
        NoSuchFile
    };
public:
    enum ErrorCode load_settings_from_file(std::string filename);
    std::string get_device();
    bool get_promiscuous_mode();
};

#endif // DEVICE_HPP
