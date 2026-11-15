#include <cstdint>
#include <memory>
#include <vector>
#include <unordered_map>
#include "chunk.hpp"
#include <FastNoiseLite.h>
#include "consts.hpp"
#include "../utils/threadpool.hpp"

std::unordered_map<uint16_t, Chunk> worldChunks;

int seed = 0;

int render_distance = 64;
int chunk_size = 16;

int posx = 8;
int posy = 8;

FastNoiseLite continent;
FastNoiseLite hills;
FastNoiseLite caves;
FastNoiseLite trees;

float continentFreq = 0.002f, hillsFreq = 0.010f, cavesFreq = 0.030f, treesFreq = 0.003f;
int continentOct = 1, hillsOct = 1, cavesOct = 1, treesOct = 1;

int tick_rate = 100; //100 ms tick rate;

ThreadPool threadpool;

// TODO set up files to read seed

// in place modifies noise object
void createNoise(FastNoiseLite &noise, int seed, float freq, int octaves)
{
    noise.SetSeed(seed);
    noise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);
    noise.SetFrequency(freq);
    if (octaves > 1)
    {
        noise.SetFractalType(FastNoiseLite::FractalType_FBm);
        noise.SetFractalOctaves(octaves);
    }
}

void init()
{
    createNoise(continent, seed, continentFreq, continentOct);
    createNoise(hills, seed, hillsFreq, hillsOct);
    createNoise(caves, seed, cavesFreq, cavesOct);
    createNoise(trees, seed, treesFreq, treesOct);

    generateChunks();
    meshChunks();
    renderChunks();

}

/*
    Generates and updates chunk block data
        Builds blocks and data
        Updates blocks and data based on tick rate
*/
void generateChunks() {
    //render distance maximum low will be 4 so dont need to worry about going to zero or -1
    //Get odd render distance, as we will be a chunk so we do diameter is the render distance
    int render_distance_odd = (render_distance % 2 == 0) ? render_distance - 1 : render_distance;
    int xLeft = posx % CHUNKSIZE - ((CHUNKSIZE * render_distance_odd) / 2);
    int yLeft = posy % CHUNKSIZE - ((CHUNKSIZE * render_distance_odd) / 2);
    for (int xc = 0; xc < render_distance_odd; xc ++) {
        for (int yc = 0; yc < render_distance_odd; yc ++) {
            for (int zc = 0; zc < WORLD_HEIGHT_DIVISIBLE / CHUNKSIZE; zc++)
                if (chunk not exists) {
                    worldChunks.emplace(xLeft, Chunk(xc, yc, zc));
                    worldChunks.at(xLeft).generateChunk();
                    if (tick rate last >= tick_rate) {
                        
                    }
                }
        }
    }
}

Chunk* getChunkFromPos(int x, int y) {
    x %= CHUNKSIZE;
    y %= CHUNKSIZE;
    return &worldChunks.at(x + y);
}

void meshChunks() {

}

void renderChunks() {

}





// when starting game

// pick work or start new world new

// seed
// file to read and write chunks fast
// player pos
// render distance
