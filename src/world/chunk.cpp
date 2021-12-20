#include "chunk.h"

Chunk::Chunk(World &inWorld, ChunkPos inX, ChunkPos inZ)
: blocks{}, world(inWorld), x(inX), z(inZ) {
    for (int i = 0; i < CHUNK_HEIGHT >> 4; i++) {
        renderChunks[i] = std::make_unique<RenderChunk>(*this, x, i, z);
    }
}

void Chunk::renderChunk() {
    for (auto &i: renderChunks) {
        i->bufferChunk();
    }
}

int Chunk::getBlockRel(const BlockPos &pos) {
    return blocks[pos.y() << 8 | pos.x() << 4 | pos.z()];
}

World &Chunk::getWorld() {
    return world;
}

void Chunk::updateRenderChunk(ChunkPos pos) {
    renderChunks[pos]->refresh();
}

void Chunk::setBlockRel(int block, const BlockPos &pos) {
    blocks[pos.y() << 8 | pos.x() << 4 | pos.z()] = block;

}
