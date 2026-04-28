/**
 *
 */

#include "decode_block.h"

#include <cstdint>
#include <vector>

#include "data_block.h"

/**
 *
 * @param block
 * @param originalSize
 * @param decodedData
 */
void decodeBlock(const DataBlock& block, uint32_t originalSize, std::vector<uint8_t>& decodedData) {
    decodedData.clear();
    decodedData.reserve(originalSize);

    int currentNode = block.root_index;

    // If the block has only repeating byte, its tree will only have one node.
    if (block.local_tree[currentNode].left_child == -1 && block.local_tree[currentNode].right_child == -1) {
        decodedData.assign(originalSize, block.local_tree[currentNode].symbol);
        return;
    }

    uint32_t bytesRecovered = 0;

    // Decode all bytes in the encoded data
    for (uint8_t byte : block.encoded_data) {
        // Decode the byte bit-by-bit, from Most Significant Bit (7) to Least (0)
        for (int i = 7; i >= 0; --i) {
            int bit = (byte >> i) & 1;

            // Traverse the tree
            if (bit == 0) {
                currentNode = block.local_tree[currentNode].left_child;
            } else { //bit == 1
                currentNode = block.local_tree[currentNode].right_child;
            }

            // Found a leaf?
            if (block.local_tree[currentNode].left_child == -1 && block.local_tree[currentNode].right_child == -1) {
                // output the decoded symbol
                decodedData.push_back(block.local_tree[currentNode].symbol);
                bytesRecovered++;

                // jump back to the root for the next symbol
                currentNode = block.root_index;

                // Check if all bytes have been decoded
                if (bytesRecovered == originalSize) {
                    return;
                }
            }
        }
    }
}
