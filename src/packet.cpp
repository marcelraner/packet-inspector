#include "packet.hpp"

#include <iostream>
#include "helper.hpp"

/**
 * Packet initializor/constructor
 * 
 * @param length Length of the packet data.
 * @param timestamp Timestamp of the packet.
 * @param data A vector that holds the data buffer of the packet.
 */
Packet::Packet(uint32_t length, struct timespec timestamp)
{
    this->length = length;
    this->timestamp = timestamp;
}

/**
 * Prints a packet in a terminal-readable format
 */
void Packet::print()
{
    std::cout << "Packet:" << std::endl;
    std::cout << "    Timestamp: " << Helper::timespec_to_string(this->timestamp) << std::endl;
    std::cout << "    Length: " << this->length << std::endl;
    std::cout << "    Data: ";
    for (auto byte: this->data)
    {
        printf(" %02X", byte);
    }
    std::cout << std::endl << std::endl;
}

/**
 * Getter for the packet length
 * 
 * @return packet length
 */
uint32_t Packet::get_length()
{
    return this->length;
}

/**
 * Getter for the packet timestamp
 * 
 * @return packet timestamp
 */
struct timespec Packet::get_timestamp()
{
    return this->timestamp;
}

/**
 * Getter for the packet data
 * 
 * @return packet data
 */
std::vector<unsigned char>& Packet::get_data()
{
    return this->data;
}
