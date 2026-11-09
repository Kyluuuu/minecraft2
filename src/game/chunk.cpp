#include <cstdint>
#include <memory>
#include <vector>
#include "block.cpp"
#include "FastNoiseLite.h"
#include <algorithm>
#include "consts.hpp"
#include "chunk.hpp"

//constructer
Chunk::Chunk(uint32_t x, uint32_t y, uint32_t z) : x{x}, y{y}, z{z}
{

}

void Chunk::generateChunk()
{

}

void Chunk::generateMesh() {
    
}

    // void regenBlockBitData()
    // {
    //     std::vector<uint64_t> blockBitTemp;
    //     for (int i = 0; i <)
    //     // blockBitTemp.push_back();
    // }

// everytime a block is added have to check if in palette already?
