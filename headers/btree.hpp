#pragma once

#include <cstdint>

#include "bnode.hpp"

class BTree {
public:
    uint64_t new_node(BNode);
    BNode get_node(uint64_t);
    void delete_node(uint64_t);

private:
    uint64_t root;
};
