#include "packet_parser.hpp"

#include "logging.hpp"

#include <iostream>
#include <algorithm>
#include <iterator>

/**
 * Search for patterns in a captured packet.
 * 
 * @param packet The network packet that includes the packet data.
 * @param patterns A list of patterns that are searched within the packet data.
 * @return True if one of the patterns was found. Else false.
 */
bool PacketParser::search_for_patterns(std::unique_ptr<Packet>& packet, std::vector<std::vector<unsigned char>> patterns)
{
    bool pattern_found = false;

    for (auto pattern: patterns)
    {
        auto result = std::search(std::begin(packet.get()->get_data()), 
                                  std::end(packet.get()->get_data()),
                                  std::begin(pattern),
                                  std::end(pattern));
        if (result != std::end(packet.get()->get_data())) {
            //TRACE("found pattern");
            pattern_found = true;
        }
    }

    return pattern_found;
}
