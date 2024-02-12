#include "btree.hpp"
#include "bnode.hpp"
#include "littleEndian.hpp"
#include <cassert>
#include <cstdint>
#include <cstring>

uint16_t BTree::nodeLookupLE(BNode node, std::vector<uint8_t>& key)
{
    auto nkeys = node.nkeys();
    uint16_t found { 0 };

    for (uint16_t i = 1; i < nkeys; i++) {
        auto cmp = std::memcmp(node.getKey(i).data(), key.data(), key.size());

        if (cmp <= 0) {
            found = i;
        } else if (cmp >= 0) {
            break;
        }
    }

    return found;
}

void BTree::leafInsert(BNode new_node, BNode old_node, uint16_t index,
    std::vector<uint8_t>& key, std::vector<uint8_t>& val)
{
    new_node.setHeader(
        static_cast<uint16_t>(BNODE_TYPE::BNODE_LEAF), old_node.nkeys() + 1);
    nodeAppendRange(new_node, old_node, 0, 0, index);
    nodeAppendKV(new_node, index, 0, key, val);
    nodeAppendRange(
        new_node, old_node, index + 1, index, old_node.nkeys() - index);
}

void BTree::nodeAppendRange(BNode new_node, BNode old_node, uint16_t dstNew,
    uint16_t srcOld, uint16_t n)
{
    assert(srcOld + n <= old_node.nkeys());
    assert(dstNew + n <= new_node.nkeys());

    if (n == 0)
        return;

    // pointers
    for (uint16_t i = 0; i < n; i++) {
        new_node.setPtr(dstNew + i, old_node.getPtr(srcOld + i));
    }

    // Offsets
    auto dstBegin = new_node.getOffset(dstNew);
    auto srcBegin = old_node.getOffset(srcOld);
    for (uint16_t i = 1; i < n; i++) {
        auto offset = dstBegin + old_node.getOffset(srcOld + i) - srcBegin;
        new_node.setOffset(dstNew + i, offset);
    }

    // KVs
    auto begin = old_node.kvPos(srcOld);
    auto end = old_node.kvPos(srcOld + n);
    std::memcpy(new_node.data + new_node.kvPos(dstNew), old_node.data + begin,
        end - begin);
}

void BTree::nodeAppendKV(BNode new_node, uint16_t index, uint64_t ptr,
    std::vector<uint8_t>& key, std::vector<uint8_t>& val)
{
    // ptrs
    new_node.setPtr(index, ptr);

    // KV
    auto pos = new_node.kvPos(index);

    littleEndian::PutUint16(
        new_node.data + pos, static_cast<uint16_t>(key.size()));
    littleEndian::PutUint16(
        new_node.data + pos + 2, static_cast<uint16_t>(val.size()));

    std::memcpy(new_node.data + pos + 4, key.data(), key.size());
    std::memcpy(new_node.data + pos + 4 + key.size(), val.data(), val.size());

    new_node.setOffset(index + 1,
        new_node.getOffset(index) + 4
            + static_cast<uint16_t>(key.size() + val.size()));
}
