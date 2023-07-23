// g++ main.cpp packet.cpp -o packet

#include <cstddef>
#include <cstdint>
#include <vector>

struct Header {
    uint32_t length;
    uint32_t checksum;
};

class Packet {
    int m_validNum, m_invalidNum;

   public:
    Packet() : m_validNum(0), m_invalidNum(0) {}

    std::vector<uint8_t> packetize(const std::vector<uint8_t> &data) const;
    std::vector<uint8_t> depacketize(const std::vector<uint8_t> &packet);
    int getValidNum() const { return m_validNum; }
    int getInvalidNum() const { return m_invalidNum; }
};