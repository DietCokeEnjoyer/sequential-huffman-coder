/**
 *
 */

#include "encode_block.h"

#include <cstdint>

#include "data_block.h"

void encodeBlock(DataBlock& block) {
    // Clear previous data if reusing the block
    block.encoded_data.clear();

    uint64_t bit_buffer = 0;
    int bit_count = 0;

    for (uint8_t symbol : block.data) {

        // Get the code and its length
        const HuffmanCode& code = block.codebook[symbol];

        // Push the code into the buffer
        bit_buffer = (bit_buffer << code.length) | code.bits;
        bit_count += code.length;

        // Flush whole encoded bytes to the output vector
        while (bit_count >= 8) {
            bit_count -= 8;

            // Shift down to ignore the bits we haven't flushed yet,
            // and use & 0xFF to grab exactly one byte.
            uint8_t byte_out = static_cast<uint8_t>((bit_buffer >> bit_count) & 0xFF);
            block.encoded_data.push_back(byte_out);
        }
    }

    // Flush remaining data, padded with 0s on the right.
    if (bit_count > 0) {
        uint8_t byte_out = static_cast<uint8_t>((bit_buffer << (8 - bit_count)) & 0xFF);
        block.encoded_data.push_back(byte_out);
    }
}