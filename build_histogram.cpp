/**
 *
 */

#include "build_histogram.h"

#include <cstdint>

#include "data_block.h"

void buildHistogram(DataBlock& block) {

    // Ensure the histogram is exactly 256 elements, all 0-initialized
    block.local_histogram.assign(256, 0);

    // Calculate frequencies
    for (uint8_t byte : block.data) {
        block.local_histogram[byte]++;
    }
}
