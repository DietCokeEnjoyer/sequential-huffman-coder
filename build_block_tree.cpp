//
// Created by umpah on 4/9/2026.
//

//#include "build_block_tree.h"

#include<queue>

#include "huffman_node.h"
#include "data_block.h"

constexpr int kMaxLeafNodes = 256;
constexpr int kMaxTreeNodes = 511;

void buildLocalTree(DataBlock &block)
{
    // Create the Min-Heap
    std::priority_queue<
        std::pair<int, uint32_t>,
        std::vector<std::pair<int, uint32_t> >,
        CompareFrequency
    > minHeap;

    // Clear old data for block reuse.
    block.local_tree.clear();

    // Pre-allocate tree
    block.local_tree.reserve(kMaxTreeNodes);

    // Create Leaf Nodes for every
    for (int i = 0; i < kMaxLeafNodes; ++i)
    {
        if (block.local_histogram[i] > 0)
        {
            HuffmanNode leaf;
            leaf.frequency = block.local_histogram[i];
            leaf.left_child = -1; // -1 denotes no child
            leaf.right_child = -1;
            leaf.symbol = static_cast<uint8_t>(i);

            // The index of this new node in our vector
            int nodeIndex = block.local_tree.size();
            block.local_tree.push_back(leaf);

            // Push {index, frequency} to the min-heap
            minHeap.push({nodeIndex, leaf.frequency});
        }
    }

    // Empty
    if (minHeap.empty())
    {
        return;
    }
    // Only one symbol in the block
    if (minHeap.size() == 1)
    {
        block.root_index = minHeap.top().first;
        return;
    }

    // Build the tree by merging heap nodes until only the root is left.
    while (minHeap.size() > 1)
    {
        // Pop the two nodes with the lowest frequencies
        auto left = minHeap.top();
        minHeap.pop();
        auto right = minHeap.top();
        minHeap.pop();

        // Create a new internal parent node
        HuffmanNode parent;
        parent.frequency = left.second + right.second; // Combined frequency
        parent.left_child = left.first; // Point to left child's array index
        parent.right_child = right.first; // Point to right child's array index
        parent.symbol = 0; // Internal nodes don't have symbols

        // Add parent to the flattened tree
        int parentIndex = block.local_tree.size();
        block.local_tree.push_back(parent);

        // Push the new parent back into the heap
        minHeap.push({parentIndex, parent.frequency});
    }

    // The last node in the heap is the root
    block.root_index = minHeap.top().first;
}
