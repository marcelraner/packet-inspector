#ifndef PACKET_HPP
#define PACKET_HPP

#include <ctime>
#include <cstdint>
#include <memory>
#include <cstdint>
#include <vector>

/**
 * Holds data of a network packet
 * 
 * Packet holds data of one network packet that was received by the
 * PacketReader::read_next_packet() method.
 */
class Packet
{
private:
    uint32_t length;
    struct timespec timestamp;
    std::vector<unsigned char> data;
public:
    void print();
    Packet(uint32_t, struct timespec);
    uint32_t get_length();
    struct timespec get_timestamp();
    std::vector<unsigned char>& get_data();
};

#endif // PACKET_HPP
