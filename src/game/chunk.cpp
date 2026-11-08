#include <cstdint>
#include <memory>
#include <vector>
#include "block.cpp"

constexpr uint8_t CHUNK_SIZE = 16;
constexpr int VOLUME = CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE;

class Chunk
{
    uint32_t x;
    uint32_t y;

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
    void regenBlockBitData()
    {
        std::vector<uint64_t> blockBitTemp;
        for (int i = 0; i <)
            blockBitTemp.push_back();
    }
};

// everytime a block is added have to check if in palette already?