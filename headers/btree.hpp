#pragma once

#include <cstdint>
#include <vector>

#include "bnode.hpp"

class BTree {
public:
    uint64_t new_node(BNode);
    BNode get_node(uint64_t);
    void delete_node(uint64_t);

    uint16_t nodeLookupLE(BNode node, std::vector<uint8_t>& key);
    void leafInsert(BNode new_node, BNode old_node, uint16_t index,
        std::vector<uint8_t>& key, std::vector<uint8_t>& val);
    void nodeAppendRange(BNode new_node, BNode old_node, uint16_t dstNew,
        uint16_t srcOld, uint16_t n);
    void nodeAppendKV(BNode new_node, uint16_t index, uint64_t ptr,
        std::vector<uint8_t>& key, std::vector<uint8_t>& val);

private:
    uint64_t root;
};
