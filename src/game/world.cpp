#include <cstdint>
#include <memory>
#include <vector>
#include "chunk.cpp"
#include <FastNoiseLite.h>

std::vector<Chunk> worldChunks;

int seed = 0;

int posx = 0;
int posy = 0;

FastNoiseLite continent;
FastNoiseLite hills;
FastNoiseLite caves;
FastNoiseLite trees;

float continentFreq = 0.002f, hillsFreq = 0.010f, cavesFreq = 0.030f, treesFreq = ;
int continentOct = 1, continentOct = 1, continentOct = 1, continentOct = 1;

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
    float freq = 0.002f;
    int octaves = 3;
    createNoise(continent, seed, freq, octaves);
    freq = ;
    octaves = ;
    createNoise(hills, seed, freq, octaves);
    createNoise(caves, seed, freq, octaves);
    createNoise(trees, seed, freq, octaves);
}

// when starting game

// pick work or start new world new

// seed
// file to read and write chunks fast
// player pos
// render distance
