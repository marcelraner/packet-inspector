#ifndef PACKET_HPP
#define PACKET_HPP

#include <ctime>
#include <cstdint>
#include <memory>
#include <cstdint>

class Packet
{
private:
    uint32_t length;
    struct timespec timestamp;
    std::unique_ptr<unsigned char[]> data;
public:
    void print();
    Packet(uint32_t, struct timespec, std::unique_ptr<unsigned char[]>);
    ~Packet();
};

#endif // PACKET_HPP
