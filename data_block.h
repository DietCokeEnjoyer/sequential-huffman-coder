/**
 *
 */
#ifndef DATA_BLOCK_H
#define DATA_BLOCK_H

#include <vector>
#include <cstdint>

#include "huffman_node.h"

struct DataBlock
{
    std::vector<uint8_t> data;
    std::vector<uint32_t> localHistogram;
    std::vector<HuffmanNode> localTree;
    int rootIndex = -1;
};

#endif //DATA_BLOCK_H
