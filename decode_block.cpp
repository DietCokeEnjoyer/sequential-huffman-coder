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
 * @param original_size
 * @param decoded_data
 */
void decodeBlock(const DataBlock& block, uint32_t original_size, std::vector<uint8_t>& decoded_data) {
    // Reuse decoded_data vector, make sure it has enough room for the block.
    decoded_data.clear();
    decoded_data.reserve(original_size);

    int current_node = block.root_index;

    // If the block has only repeating byte, its tree will only have one node.
    if (block.local_tree[current_node].left_child == -1 && block.local_tree[current_node].right_child == -1) {
        decoded_data.assign(original_size, block.local_tree[current_node].symbol);
        return;
    }

    uint32_t bytes_recovered = 0;

    // Decode all bytes in the encoded data
    for (uint8_t byte : block.encoded_data) {
        // Decode the byte bit-by-bit, from Most Significant Bit (7) to Least (0)
        for (int i = 7; i >= 0; --i) {
            int bit = (byte >> i) & 1;

            // Traverse the tree
            if (bit == 0) {
                current_node = block.local_tree[current_node].left_child;
            } else { //bit == 1
                current_node = block.local_tree[current_node].right_child;
            }

            // Found a leaf?
            if (block.local_tree[current_node].left_child == -1 && block.local_tree[current_node].right_child == -1) {
                // output the decoded symbol
                decoded_data.push_back(block.local_tree[current_node].symbol);
                bytes_recovered++;

                // jump back to the root for the next symbol
                current_node = block.root_index;

                // Check if all bytes have been decoded
                if (bytes_recovered == original_size) {
                    return;
                }
            }
        }
    }
}
