/**
 * 
 */

#include "build_codebook.h"

#include "data_block.h"

void buildCodebook(DataBlock& block) {
    // If the tree is empty, do nothing
    if (block.root_index == -1 || block.local_tree.empty()) return;

    const HuffmanNode& root = block.local_tree[block.root_index];

    // Data block only contains 1 symbol
    if (root.left_child == -1 && root.right_child == -1) {
        block.codebook[root.symbol].bits = 0;
        block.codebook[root.symbol].length = 1;
        return;
    }

    // Start recursion at the root
    generateCodebookRecursive(block.local_tree, block.root_index, 0, 0, block.codebook);
}

void generateCodebookRecursive(const std::vector<HuffmanNode>& tree,
                               int current_node_index,
                               uint64_t current_bits,
                               uint8_t current_length,
                               std::vector<HuffmanCode>& codebook) {
    // Safety check
    if (current_node_index == -1) return;

    const HuffmanNode& node = tree[current_node_index];

    // Check if this node is a leaf
    if (node.left_child == -1 && node.right_child == -1) {
        codebook[node.symbol].bits = current_bits;
        codebook[node.symbol].length = current_length;
        return;
    }

    // Traverse Left: Shift bits left by 1 (append a 0)
    if (node.left_child != -1) {
        generateCodebookRecursive(tree, node.left_child,
                                  current_bits << 1,
                                  current_length + 1,
                                  codebook);
    }

    // Traverse Right: Shift bits left by 1, and bitwise OR with 1 (append a 1)
    if (node.right_child != -1) {
        generateCodebookRecursive(tree, node.right_child,
                                  (current_bits << 1) | 1,
                                  current_length + 1,
                                  codebook);
    }
}