#pragma once

#include <array>

#include "gl.h"
#include "render/view/buffer_builder.h"
#include "math/blockpos.h"
#include "render/world/blockface.h"
#include "util/specs.h"

class Chunk;

typedef int32_t ChunkPos;

class Vertex {

public:
    Vertex(BlockPos, glm::vec2 uv, glm::vec3 normal);

private:
    GLfloat x, y, z;
    GLfloat u, v;
    GLfloat normX, normY, normZ;
};


class RenderChunk {

public:
    RenderChunk();
    RenderChunk(Chunk *c, ChunkPos inX, ChunkPos inY, ChunkPos inZ);
    ~RenderChunk();

    /*
     * Called pre-rendering since GL calls can only be accessed
     * from the main thread.
     */
    void tryInitGL();

    void refresh(); // reloads the VBO, etc
    void bufferChunk();
    void setDead();

private:
    bool initialized;

    int x, y, z;
    Chunk *chunk;
    std::array<GLuint, RENDER_LAYERS> vao;
    std::array<GLuint, RENDER_LAYERS> buffer;
    std::array<GLuint, RENDER_LAYERS> idxBuf;

    bool loaded;
    bool notEmpty; // for dummy render chunks
    /*
     * When deactivated and waits for GL clean up from
     * main thread.
     */
    bool dead;
    GLsizei vertCount;

    void loadBuffer();
    bool shouldRenderFace(BlockPos pos, BlockFace::Facing face);
    void addFace(
        int block, const BlockPos &pos, BlockFace::Facing face,
        std::vector<Vertex> &verts, std::vector<GLsizei> &idxs
    );
};
