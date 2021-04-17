#include <iostream>
#include <csignal>

#include "settings.hpp"
#include "capture_device.hpp"
#include "packet_reader.hpp"

void signal_handler(int)
{
    std::cout << "received SIGINT => terminating application ..." << std::endl;
    exit(EXIT_SUCCESS);
}

void handle_packet(std::unique_ptr<Packet> packet)
{
    packet.get()->print();
}

int main()
{
    std::cout << "packet-inspector v0.1" << std::endl;

    std::signal(SIGINT, signal_handler);

    Settings settings;
    CaptureDevice device;

    enum Settings::ErrorCode rc_load_settings = Settings::ErrorCode::Ok;
    rc_load_settings = settings.load_settings_from_file("settings.conf");
    switch (rc_load_settings) {
    case Settings::ErrorCode::Ok:
        break;
    case Settings::ErrorCode::NoSuchFile:
        std::cout << "Error: No such file! Could not open settings file: " << "settings.conf" << std::endl;
        return EXIT_FAILURE;
    }

    enum CaptureDevice::ErrorCode rc_open_device = CaptureDevice::ErrorCode::Ok;
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

    for (int i = 0; i < 25; i++)
    {
        auto packet = PacketReader::read_next_packet(device);

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

        std::cout << "Handle paket" << std::endl;
        handle_packet(std::move(packet.first));
    }

    device.close_device();

    return EXIT_SUCCESS;
}
