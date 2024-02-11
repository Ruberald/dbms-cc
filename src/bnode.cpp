#include <cassert>
#include <cstdint>
#include <vector>

#include "bnode.hpp"
#include "littleEndian.hpp"

//
// Header
//

uint16_t BNode::btype() const { return littleEndian::Uint16(data); }

uint16_t BNode::nkeys() const { return littleEndian::Uint16(data + 2); }

void BNode::setHeader(uint16_t btype, uint16_t nkeys)
{
    littleEndian::PutUint16(data, btype);
    littleEndian::PutUint16(data + 2, nkeys);
}

//
// Pointers
//

uint64_t BNode::getPtr(uint16_t index)
{
    assert(index < nkeys());

    auto pos = Constants::HEADER + 8 * index;
    return littleEndian::Uint64(data + pos);
}

void BNode::setPtr(uint16_t index, uint64_t value)
{
    assert(index < nkeys());

    auto pos = Constants::HEADER + 8 * index;
    littleEndian::PutUint64(data + pos, value);
}

//
// Offset list
//

uint16_t BNode::offsetPos(uint16_t index)
{
    assert(1 <= index && index < nkeys());

    return Constants::HEADER + 8 * nkeys() + 2 * (index - 1);
}

uint16_t BNode::getOffset(uint16_t index)
{
    if (index == 0) {
        return 0;
    }

    return littleEndian::Uint16(data + offsetPos(index));
}

void BNode::setOffset(uint16_t index, uint16_t offset)
{
    littleEndian::PutUint16(data + offsetPos(index), offset);
}

//
// key-values
//

uint16_t BNode::kvPos(uint16_t index)
{
    assert(index < nkeys());

    return Constants::HEADER + 8 * nkeys() + 2 * nkeys() + getOffset(index);
}

std::vector<uint8_t> BNode::getKey(uint16_t index)
{
    assert(index < nkeys());

    auto pos = kvPos(index);
    auto klen = littleEndian::Uint16(data + pos);
    std::vector<uint8_t> result(data + pos + 4, data + pos + 4 + klen);
    return result;
}

std::vector<uint8_t> BNode::getVal(uint16_t index)
{
    assert(index < nkeys());

    auto pos = kvPos(index);
    auto klen = littleEndian::Uint16(data + pos);
    auto vlen = littleEndian::Uint16(data + pos + 2);
    std::vector<uint8_t> result(
        data + pos + 4 + klen, data + pos + 4 + klen + vlen);
    return result;
}

//
// node size in bytes
//

uint16_t BNode::nbytes() { return kvPos(nkeys()); }
