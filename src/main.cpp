#include <iostream>
#include <csignal>

#include "settings.hpp"
#include "capture_device.hpp"
#include "packet_reader.hpp"
#include "packet_parser.hpp"

bool signal_received = false;

/**
 * Signal handler for catching SIGINT
 */
void signal_handler(int signo)
{
    if (signo == SIGINT) {
        std::cout << "SIGINT: terminating application ..." << std::endl;
    }
    signal_received = true;
}

/**
 * Main - Entry point of the application
 */
int main()
{
    Settings settings;
    CaptureDevice device;
    enum Settings::ErrorCode rc_load_settings = Settings::ErrorCode::Ok;
    enum CaptureDevice::ErrorCode rc_open_device = CaptureDevice::ErrorCode::Ok;

    std::cout << "packet-inspector v0.1" << std::endl;

    // Register a signal handler to be able to terminate
    // the application from the infinite loop.
    std::signal(SIGINT, signal_handler);

    // Loading settings from settings.conf file
    rc_load_settings = settings.load_settings_from_file("settings.conf");
    switch (rc_load_settings) {
    case Settings::ErrorCode::Ok:
        break;
    case Settings::ErrorCode::NoSuchFile:
        std::cout << "Error: No such file! Could not open settings file: " << "settings.conf" << std::endl;
        return EXIT_FAILURE;
    }

    // Open capture device for reading packets.
    rc_open_device = device.open_device(settings.get_device(), settings.get_promiscuous_mode());
    switch (rc_open_device) {
    case CaptureDevice::ErrorCode::Ok:
        break;
    case CaptureDevice::ErrorCode::NoSuchDevice:
        std::cout << "Error: No such device! Could not open device: " << settings.get_device() << std::endl;
        return EXIT_FAILURE;
    case CaptureDevice::ErrorCode::PermissionDenied:
        std::cout << "Error: Permission denied! Could not open device: " << settings.get_device() << std::endl;
        return EXIT_FAILURE;
    }

    // Checking if search patterns was configured. If no patterns was
    // configured, the application will end here.
    if (settings.get_patterns().size() == 0) {
        std::cout << "Error: No search patterns was configured." << std::endl;
        return EXIT_FAILURE;
    }

    // Printing search patterns
    std::cout << "Searching for patterns:" << std::endl;
    for (auto pattern: settings.get_patterns())
    {
        std::cout << "   ";
        for (unsigned int i = 0; i < pattern.size(); i++)
        {
            printf(" %02X", pattern[i]);
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    // Starting loop that reads and handles packets. Can be 
    // interrupted by sending SIGINT.
    while(!signal_received)
    {
        auto packet = PacketReader::read_next_packet(device);
        bool pattern_found = false;

        // Evaluate return code of read_next_packet().
        switch (packet.second) {
        case PacketReader::ErrorCode::Ok:
            break;
        case PacketReader::ErrorCode::DeviceNotOpen:
            std::cout << "Error: Device is not open! Could not use device handle." << std::endl;
            return EXIT_FAILURE;
        case PacketReader::ErrorCode::Timeout:
            std::cout << "Timeout" << std::endl;
            continue;
        }

        // Search for the configured patterns within the packet. If one of the
        // patterns matches, then the packet will be printed.
        pattern_found = PacketParser::search_for_patterns(packet.first, settings.get_patterns());
        if (pattern_found) {
            packet.first.get()->print();
        }
    }

    return EXIT_SUCCESS;
}
