/**
 * decode_block.h
 */

#ifndef DECODE_BLOCK_H
#define DECODE_BLOCK_H
#include <cstdint>
#include <vector>

#include "data_block.h"


void decodeBlock(const DataBlock& block, uint32_t original_size, std::vector<uint8_t>& decoded_data);

#endif //DECODE_BLOCK_H
