/**
 *
 */
#ifndef BUILD_CODEBOOK_H
#define BUILD_CODEBOOK_H

#include <cstdint>
#include <vector>

#include "huffman_node.h"
#include "data_block.h"

void buildCodebook(DataBlock & block);

void generateCodebookRecursive(const std::vector<HuffmanNode> &tree,
                               int current_node_index,
                               uint64_t current_bits,
                               uint8_t current_length,
                               std::vector<HuffmanCode> &codebook);

#endif //BUILD_CODEBOOK_H
