/**
 *
 *
 */

#ifndef HUFFMAN_NODE_H
#define HUFFMAN_NODE_H

#include <cstdint>
#include <queue>

/**
 *
 */
struct HuffmanNode {
    uint32_t frequency; // of the symbol in the file
    int16_t left_child;  // -1 if leaf
    int16_t right_child; // -1 if leaf
    uint8_t symbol;     // Only valid if leaf
};

/// For comparing HuffmanNode frequencies in a priority queue
struct CompareFrequency {
    bool operator()(const std::pair<int, uint32_t> &a, const std::pair<int, uint32_t> &b) const
    {
        return a.second > b.second; // Min-heap based on frequency
    }
};
#endif //HUFFMAN_NODE_H
