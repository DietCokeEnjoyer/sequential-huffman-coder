/**
 * decode_block.h
 */

#ifndef DECODE_BLOCK_H
#define DECODE_BLOCK_H
#include <cstdint>
#include <vector>

#include "data_block.h"

/**
 * 
 * @param block 
 * @param originalSize 
 * @param decodedData 
 */
void decodeBlock(const DataBlock& block, uint32_t originalSize, std::vector<uint8_t>& decodedData);

#endif //DECODE_BLOCK_H
