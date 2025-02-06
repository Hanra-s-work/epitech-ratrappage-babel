#include "Network/Translator.hpp"

namespace Network
{
    Translator::Translator() {}

    Translator::~Translator() {}

    // Serialize the packet to a byte stream (for sending)
    std::vector<uint8_t> Translator::serialize(const Packet &packet) const
    {
        std::vector<uint8_t> byte_stream;

        // Serialize the PacketType (1 byte)
        byte_stream.push_back(static_cast<uint8_t>(packet.type));

        // Serialize the size of the name and the name itself
        uint32_t name_size = static_cast<uint32_t>(packet.name.size());
        byte_stream.insert(byte_stream.end(), reinterpret_cast<uint8_t *>(&name_size), reinterpret_cast<uint8_t *>(&name_size) + sizeof(name_size));
        byte_stream.insert(byte_stream.end(), packet.name.begin(), packet.name.end());

        // Serialize the protocol (1 byte)
        byte_stream.push_back(static_cast<uint8_t>(packet.protocol));

        // Serialize the size of the data and the data itself
        uint32_t data_size = static_cast<uint32_t>(packet.data.size());
        byte_stream.insert(byte_stream.end(), reinterpret_cast<uint8_t *>(&data_size), reinterpret_cast<uint8_t *>(&data_size) + sizeof(data_size));
        byte_stream.insert(byte_stream.end(), packet.data.begin(), packet.data.end());

        return byte_stream;
    }

    // Deserialize a byte stream into a Packet object (for receiving)
    Packet Translator::deserialize(const std::vector<uint8_t> &byte_stream) const
    {
        Packet packet;
        size_t index = 0;

        // Deserialize the PacketType (1 byte)
        packet.type = static_cast<PacketType>(byte_stream[index++]);

        // Deserialize the name size (4 bytes) and the name itself
        uint32_t name_size;
        std::memcpy(&name_size, &byte_stream[index], sizeof(name_size));
        index += sizeof(name_size);
        packet.name.assign(byte_stream.begin() + index, byte_stream.begin() + index + name_size);
        index += name_size;

        // Deserialize the protocol (1 byte)
        packet.protocol = static_cast<Protocol>(byte_stream[index++]);

        // Deserialize the data size (4 bytes) and the data itself
        uint32_t data_size;
        std::memcpy(&data_size, &byte_stream[index], sizeof(data_size));
        index += sizeof(data_size);
        packet.data.assign(byte_stream.begin() + index, byte_stream.begin() + index + data_size);

        return packet;
    }
}
