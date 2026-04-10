/**
 *
 */
#ifndef DATA_BLOCK_H
#define DATA_BLOCK_H

#include <vector>
#include <cstdint>

#include "huffman_node.h"

struct HuffmanCode {
    uint64_t bits = 0;   // The binary code
    uint8_t length = 0;  // How many bits make up the code
};

struct DataBlock
{
    std::vector<uint8_t> data; // Raw file data in bytes.
    std::vector<uint32_t> local_histogram; // Holds the frequencies of symbols in the data.
    std::vector<HuffmanNode> local_tree; // Flattened Huffman Tree
    int root_index = -1;

    // Allows lookup of symbol codes by lookup rather than tree traversal.
    std::vector<HuffmanCode> codebook{256};
};

#endif //DATA_BLOCK_H
