#ifndef PACKET_READER_HPP
#define PACKET_READER_HPP

#include "packet.hpp"
#include "capture_device.hpp"

class PacketReader
{
    private:
        PacketReader();
    public:
    enum ErrorCode {
        Ok,
        DeviceNotOpen,
        Timeout
    };
    static std::pair<std::unique_ptr<Packet>, enum PacketReader::ErrorCode> read_next_packet(CaptureDevice&);
};

#endif // PACKET_READER_HPP
