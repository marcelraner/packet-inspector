#include "packet_reader.hpp"

#include <cstring>

std::pair<std::unique_ptr<Packet>, enum PacketReader::ErrorCode> PacketReader::read_next_packet(CaptureDevice& device)
{
    struct pcap_pkthdr *header = NULL;
    const unsigned char *packet_data = NULL;
    int rc_pcap_next = 0;

    if (device.pcap_ctx.get() == NULL)
    {
        return std::pair(std::unique_ptr<Packet>(), PacketReader::ErrorCode::DeviceNotOpen);
    }

    rc_pcap_next = pcap_next_ex(device.pcap_ctx.get(), &header, &packet_data);
    if (rc_pcap_next == 0)
    {
        return std::pair(std::unique_ptr<Packet>(), PacketReader::ErrorCode::Timeout);
    }
    else if (rc_pcap_next != 1)
    {
        std::string error_message = "Unhandled error during pcap_next_ex()";
        throw std::runtime_error(error_message);
    }

    if (packet_data == NULL) {
        std::string error_message = "Could not read paket";
        throw std::runtime_error(error_message);
    }

    

    auto packet_data_copy = std::unique_ptr<unsigned char[]>(new unsigned char[header->caplen]);

    if (packet_data_copy.get() == NULL) {
        std::string error_message = "Could not allocate memory for paket data buffer";
        throw std::runtime_error(error_message);
    }

    std::memcpy(packet_data_copy.get(), packet_data, header->caplen);

    struct timespec timestamp;
    timestamp.tv_sec = header->ts.tv_sec;
    timestamp.tv_nsec = header->ts.tv_usec * 1000;

    auto packet = std::unique_ptr<Packet>(new Packet(header->caplen, timestamp, std::move(packet_data_copy)));

    return std::pair(std::move(packet), PacketReader::ErrorCode::Ok);
}
