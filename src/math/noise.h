#pragma once

#include <vector>
#include <functional>

#define PERM_LENGTH 256

typedef std::function<float(float, float)> NoiseSampler;

class INoise {

public:
    virtual ~INoise() = default;
    virtual float genNoise(float u, float v) = 0;
};

class PerlinNoise: virtual public INoise {

public:
    explicit PerlinNoise(uint32_t inSeed);
    float genNoise(float u, float v) override;

private:
    uint32_t seed;
    int p[PERM_LENGTH * 2];
};

class CompositePerlin: virtual public INoise {

public:
    CompositePerlin(uint32_t seed, uint8_t layers, float inPow);
    float genNoise(float u, float v) override;

private:
    std::vector<PerlinNoise> octaves;
    float persistence;
};
