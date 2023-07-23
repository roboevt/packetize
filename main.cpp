#include <iostream>
#include <fstream>

#include "packet.h"

int main() {
    std::vector<uint8_t> data = {1, 2, 3, 4, 5};
    Packet packet;
    std::vector<uint8_t> packetized = packet.packetize(data);
    std::vector<uint8_t> depacketized = packet.depacketize(packetized);

    std::cout << "Packetized: ";
    for (auto& byte : packetized) {
        std::cout << static_cast<int>(byte) << " ";
    }
    std::cout << std::endl;

    std::cout << "Depacketized: ";
    for (auto& byte : depacketized) {
        std::cout << static_cast<int>(byte) << " ";
    }
    std::cout << std::endl;

    // packetize local file packet.cpp

    std::ifstream file("packet.h", std::ios::binary);
    std::vector<uint8_t> file_data((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    std::vector<uint8_t> file_packetized = packet.packetize(file_data);
    std::cout << "File packetized: ";
    for (auto& byte : file_packetized) {
        std::cout << static_cast<int>(byte) << " ";
    }
    std::cout << std::endl << std::endl;
    std::vector<uint8_t> file_depacketized = packet.depacketize(file_packetized);
    std::cout << "File depacketized: ";
    for (auto& byte : file_depacketized) {
        std::cout << static_cast<int>(byte) << " ";
    }
    std::cout << std::endl;

    //Check if file_data and file_depacketized are the same
    if (file_data == file_depacketized) {
        std::cout << "File packetized and depacketized successfully" << std::endl;
    } else {
        std::cout << "File packetized and depacketized unsuccessfully" << std::endl;
    }


    return 0;
}