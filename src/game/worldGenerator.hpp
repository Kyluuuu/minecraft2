#include <FastNoiseLite.h>

class WorldGenerator
{
private:
    FastNoiseLite continent;
    FastNoiseLite hills;
    FastNoiseLite caves;
    FastNoiseLite trees;

    static constexpr float continentFreq = 0.002f, hillsFreq = 0.010f, cavesFreq = 0.030f, treesFreq = 0.003f;
    static constexpr int continentOct = 1, hillsOct = 1, cavesOct = 1, treesOct = 1;

    void createNoise(FastNoiseLite &noise, int &seed, float freq, int octaves)
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

public:
    WorldGenerator(int &seed)
    {
        createNoise(continent, seed, continentFreq, continentOct);
        createNoise(hills, seed, hillsFreq, hillsOct);
        createNoise(caves, seed, cavesFreq, cavesOct);
        createNoise(trees, seed, treesFreq, treesOct);
    }

    
};