#include "packet.h"

#include <numeric>
#include <stdexcept>
#include <string>
#include <iostream>

namespace {
uint32_t checksum(const std::vector<uint8_t>& data) {
    return std::accumulate(data.begin(), data.end(), static_cast<uint32_t>(0));
}
}  // namespace

std::vector<uint8_t> Packet::packetize(const std::vector<uint8_t>& data) const {
    std::vector<uint8_t> packet(data.size() + sizeof(Header));

    uint32_t sum = checksum(data);
    Header header = {static_cast<uint32_t>(data.size()), sum};
    std::copy(reinterpret_cast<uint8_t*>(&header),
              reinterpret_cast<uint8_t*>(&header) + sizeof(Header), packet.begin());

    std::copy(data.begin(), data.end(), packet.begin() + sizeof(Header));

    return packet;
}

std::vector<uint8_t> Packet::depacketize(const std::vector<uint8_t>& packet){
    if (packet.size() < sizeof(Header)) {
        std::string msg = "Invalid packet length: " + std::to_string(packet.size()) +
                          ", expected: " + std::to_string(sizeof(Header));
        std::cout << msg << std::endl;
        m_invalidNum++;
        return {};
    }

    Header header;
    std::copy(packet.begin(), packet.begin() + sizeof(Header), reinterpret_cast<uint8_t*>(&header));

    if (header.length != packet.size() - sizeof(Header)) {
        std::string msg = "Invalid packet length while depacketizing: " + std::to_string(header.length) +
                          ", expected: " + std::to_string(packet.size() - sizeof(Header));
        std::cout << msg << std::endl;
        m_invalidNum++;
        return {};
    }

    std::vector<uint8_t> data(header.length);
    std::copy(packet.begin() + sizeof(Header), packet.end(), data.begin());

    int32_t sum = checksum(data);
    if (sum != header.checksum) {
        std::cout << "Invalid checksum while depacketizing" << std::endl;
        m_invalidNum++;
        return {};
    }
    m_validNum++;
    return data;
}
