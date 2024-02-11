#pragma once

#include <cstdint>
#include <vector>

namespace Constants {

constexpr int HEADER = 4;
constexpr int BTREE_PAGE_SIZE = 4096;
constexpr int BTREE_MAX_KEY_SIZE = 1000;
constexpr int BTREE_MAX_VAL_SIZE = 3000;

}

enum class BNODE_TYPE { BNODE_NODE, BNODE_LEAF };

class BNode {
public:
    // Headers
    uint16_t btype() const;
    uint16_t nkeys() const;

    void setHeader(uint16_t btype, uint16_t nkeys);

    // Pointers
    uint64_t getPtr(uint16_t index);
    void setPtr(uint16_t index, uint64_t value);

    // Offset list
    uint16_t getOffset(uint16_t index);
    void setOffset(uint16_t index, uint16_t offset);

    // key-values
    uint16_t kvPos(uint16_t index);
    std::vector<uint8_t> getKey(uint16_t index);
    std::vector<uint8_t> getVal(uint16_t index);

    // node size in bytes
    uint16_t nbytes();

private:
    uint8_t* data;

    // Offset list
    uint16_t offsetPos(uint16_t index);
};
