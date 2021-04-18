#ifndef PACKET_PARSER_HPP
#define PACKET_PARSER_HPP

#include "packet.hpp"
#include <memory>
#include <vector>

/**
 * Implementation of packet parsing operation(s)
 * 
 * Until now, this class holds just one method that searches for patterns 
 * within a captured packet.
 */
class PacketParser
{
private:
    PacketParser();
public:
    static bool search_for_patterns(std::unique_ptr<Packet>&, std::vector<std::vector<unsigned char>>);
};

#endif // PACKET_PARSER_HPP
