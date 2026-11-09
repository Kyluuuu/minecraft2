#include <cstdint>
#include <memory>
#include <vector>
#include "block.cpp"
#include "FastNoiseLite.h"
#include <algorithm>
#include "consts.hpp"

constexpr int VOLUME = CHUNKSIZE * CHUNKSIZE * CHUNKSIZE;

class Chunk {
    private:
        uint32_t x, y, z;

        std::vector<Block> palette;
        std::vector<uint16_t> blockCount;
        std::vector<uint64_t> blockBitData;

        uint8_t bits{0};

        // Mesh mesh;

        bool dirty = false;
    public:
        Chunk(uint32_t x, uint32_t y, uint32_t z);
        void generateChunk();
        void generateMesh();
};