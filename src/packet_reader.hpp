#ifndef PACKET_READER_HPP
#define PACKET_READER_HPP

#include "packet.hpp"
#include "capture_device.hpp"

/**
 * Implementation of packet reader operation(s)
 * 
 * Until now, this class holds just one method that works as a wrapper for
 * pcap's pcap_next_ex() function.
 */
class PacketReader
{
private:
    PacketReader();
public:
    /** Specifies return values for methods form class PacketReader */ 
    enum ErrorCode
    {
        Ok,
        DeviceNotOpen,
        Timeout
    };
    static std::pair<std::unique_ptr<Packet>, enum PacketReader::ErrorCode> read_next_packet(CaptureDevice&);
};

#endif // PACKET_READER_HPP
