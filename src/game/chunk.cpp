#include <cstdint>
#include <memory>
#include <vector>
#include "block.cpp"
#include "FastNoiseLite.h"
#include <algorithm>

constexpr uint8_t CHUNK_SIZE = 16;
constexpr int VOLUME = CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE;
constexpr uint8_t WORLD_H = 255;
constexpr uint8_t SEA_LEVEL = 62;

class Chunk
{
    uint32_t x, y, z;

    std::vector<Block> palette;
    std::vector<uint16_t> blockCount;
    std::vector<uint64_t> blockBitData;

    uint8_t bits{0};

    bool dirty = false;

    // Mesh mesh;

    Chunk()
    {
    }

    void generateChunk()
    {
    }

private:
    // void regenBlockBitData()
    // {
    //     std::vector<uint64_t> blockBitTemp;
    //     for (int i = 0; i <)
    //     // blockBitTemp.push_back();
    // }
};

// everytime a block is added have to check if in palette already?
