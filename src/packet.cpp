#include "packet.hpp"

#include <iostream>

Packet::Packet(uint32_t length, struct timespec timestamp, std::unique_ptr<unsigned char[]> data)
{
    this->length = length;
    this->timestamp = timestamp;
    this->data = std::move(data);
}

Packet::~Packet()
{
    std::cout << "~Packet()" << std::endl;
}

void Packet::print()
{
    std::cout << "Packet {" << std::endl;
    std::cout << "    timestamp: " << this->timestamp.tv_sec << "." << this->timestamp.tv_nsec << std::endl;
    std::cout << "    length:    " << this->length << std::endl;
    std::cout << "    content:   ";
    for (unsigned int i = 0; i < this->length; i++)
    {
        printf(" %X", this->data[i]);
    }
    std::cout << std::endl;
    std::cout << "}" << std::endl;
}
