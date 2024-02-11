#include <cstdint>

#include "littleEndian.hpp"

namespace littleEndian {

uint16_t Uint16(const uint8_t* b)
{
    return static_cast<uint16_t>(b[0]) | (static_cast<uint16_t>(b[1]) << 8);
}

void PutUint16(uint8_t* b, uint16_t v)
{
    b[0] = static_cast<uint8_t>(v);
    b[1] = static_cast<uint8_t>(v >> 8);
}

uint64_t Uint64(const uint8_t* b)
{
    return static_cast<uint64_t>(b[0]) | (static_cast<uint64_t>(b[1]) << 8)
        | (static_cast<uint64_t>(b[2]) << 16)
        | (static_cast<uint64_t>(b[3]) << 24)
        | (static_cast<uint64_t>(b[4]) << 32)
        | (static_cast<uint64_t>(b[5]) << 40)
        | (static_cast<uint64_t>(b[6]) << 48)
        | (static_cast<uint64_t>(b[7]) << 56);
}

void PutUint64(uint8_t* b, uint64_t v)
{
    b[0] = static_cast<uint8_t>(v);
    b[1] = static_cast<uint8_t>(v >> 8);
    b[2] = static_cast<uint8_t>(v >> 16);
    b[3] = static_cast<uint8_t>(v >> 24);
    b[4] = static_cast<uint8_t>(v >> 32);
    b[5] = static_cast<uint8_t>(v >> 40);
    b[6] = static_cast<uint8_t>(v >> 48);
    b[7] = static_cast<uint8_t>(v >> 56);
}

} // namespace littleEndian
