#include <cstdint>
#include <memory>
#include <vector>
#include <unordered_map>
#include "chunk.hpp"
#include <FastNoiseLite.h>
#include "consts.hpp"
#include "../utils/threadpool.hpp"
#include "world.hpp"
#include "files/files.hpp"

World::World(int seed, Files& fileLoader)
    : world_generator(seed)
{
    fileLoader.sub(
        Settings::RENDER_DISTANCE, [this] (int render_d) {
            cout << "render distance changed!";
            render_distance = render_d;
        }
    );
    fileLoader.sub(
        Settings::CHUNK_SIZE, [this] () {

        }
    );
    fileLoader.sub(
        Settings::TICK_RATE, [this] () {

        }
    );
}

void updateRenderDistance() {
    //removed further distance chunks from world_chunks if smaller
    //if larger doent have to do anything wth world_chunks?
    //clear chunk_thread_pool
    //
}


void World::generateChunks()
{
    // render distance maximum low will be 4 so dont need to worry about going to zero or -1
    // Get odd render distance, as we will be a chunk so we do diameter is the render distance
    int render_distance_odd = (render_distance % 2 == 0) ? render_distance - 1 : render_distance;
    int xLeft = pos_x % Consts::CHUNKSIZE - ((Consts::CHUNKSIZE * render_distance_odd) / 2);
    int yLeft = pos_y % Consts::CHUNKSIZE - ((Consts::CHUNKSIZE * render_distance_odd) / 2);
    for (int xc = 0; xc < render_distance_odd; xc++)
    {
        for (int yc = 0; yc < render_distance_odd; yc++)
        {
            for (int zc = 0; zc < Consts::WORLD_HEIGHT_DIVISIBLE / Consts::CHUNKSIZE; zc++)
                if (chunk not exists)
                {
                    worldChunks.emplace(xLeft, Chunk(xc, yc, zc));
                    worldChunks.at(xLeft).generateChunk();
                    if (tick rate last >= tick_rate)
                    {
                    }
                }
        }
    }
}

Chunk *World::getChunkFromPos(int x, int y)
{
    x %= Consts::CHUNKSIZE;
    y %= Consts::CHUNKSIZE;
    return world_chunks.at(x + y);
}

void meshChunks()
{
}

void renderChunks()
{
}

// when starting game

// pick work or start new world new

// seed
// file to read and write chunks fast
// player pos
// render distance
