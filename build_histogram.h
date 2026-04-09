/**
 *
 */

#ifndef BUILD_HISTOGRAM_H
#define BUILD_HISTOGRAM_H

#include <cstdint>
#include <vector>

/// Creates a histogram of 8-bit symbol frequencies from a data vector.
std::vector<uint32_t> buildHistogram(const std::vector<uint8_t>& data);


#endif //BUILD_HISTOGRAM_H
