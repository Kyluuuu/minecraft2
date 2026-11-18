#pragma once

#include <cstdint>
#include <memory>
#include <vector>
#include <unordered_map>
#include "chunk.hpp"
#include "consts.hpp"
#include "../utils/threadpool.hpp"
#include "worldGenerator.hpp"
#include "game/option.hpp"

class World
{
private:
    std::unordered_map<uint16_t, Chunk> world_chunks;

    // TODO load by file / settings
    int render_distance;
    int chunk_size;
    int tick_rate;

    

    WorldGenerator world_generator;

    ThreadPool chunk_thread_pool;

    // player position
    int pos_x;
    int pos_y;

public:
    World(int seed);
    World(const World &) = delete;
    World &operator=(const World &) = delete;

    void generateChunks();

};
//