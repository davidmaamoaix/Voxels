#include "generator.h"

#include <iostream>

#include "world/blocks.h"

Generator::Generator() = default;

std::shared_ptr<Chunk> Generator::genChunk(World &w, ChunkPos x, ChunkPos z) {
    std::shared_ptr<Chunk> chunk = std::make_shared<Chunk>(w, x, z);

    //TODO: better cache locality
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 16; j++) {

            for (int h = 0; h < 20; h++) {
                chunk->blocks[h << 8 | i << 4 | j] = BLOCK_DIRT;
            }
        }
    }

    return chunk;
}
