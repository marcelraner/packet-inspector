#include "packet_reader.hpp"

#include <cstring>

/**
 * This function is a wrapper for pcap's pcap_next_ex() function. It reads and
 * returns the next packet that is received on a network interface.
 * 
 * @param device The device that is used for capturing network packets.
 * @return A result pair that includes the packet and the error/return code.
 */
std::pair<std::unique_ptr<Packet>, enum PacketReader::ErrorCode> PacketReader::read_next_packet(CaptureDevice& device)
{
    struct pcap_pkthdr *header = NULL;
    const unsigned char *packet_data = NULL;
    int rc_pcap_next = 0;

    if (device.get_ctx().get() == NULL)
    {
        return std::pair(std::unique_ptr<Packet>(), PacketReader::ErrorCode::DeviceNotOpen);
    }

    rc_pcap_next = pcap_next_ex(device.get_ctx().get(), &header, &packet_data);
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

    struct timespec timestamp;
    timestamp.tv_sec = header->ts.tv_sec;
    timestamp.tv_nsec = header->ts.tv_usec; // I want to store usec here

    // initialize new packet with packet length and timestamp
    auto packet = std::unique_ptr<Packet>(new Packet(header->caplen, timestamp));

    // and copy packet data to packet
    packet.get()->get_data().assign(packet_data, packet_data + header->caplen);

    return std::pair(std::move(packet), PacketReader::ErrorCode::Ok);
}
