#pragma once

#include <cstdint>

namespace littleEndian {

uint16_t Uint16(const uint8_t* b);

void PutUint16(uint8_t* b, uint16_t v);

uint64_t Uint64(const uint8_t* b);

void PutUint64(uint8_t* b, uint64_t v);

} // namespace littleEndian
