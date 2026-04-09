/**
 *
 */

#include "build_histogram.h"

#include <cstdint>
#include <vector>


std::vector<uint32_t> buildHistogram(const std::vector<uint8_t>& data) {
    std::vector<uint32_t> histogram(256, 0);
    for (const uint8_t byte : data) {
        histogram[byte]++;
    }
    return histogram;
}
