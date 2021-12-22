#pragma once

#include "render/world/world_renderer.h"
#include "world/world.h"

class Voxels {

public:
    static Voxels &get();
    void init();
    void drawFrame(float deltaTime);
    Camera &camera();
    World &getWorld();
    RayResult &getMouseOver();
    bool playerAttack();
    bool playerPlace();
    void end();

private:
    Voxels();
    World world;
    WorldRenderer renderer;
    RayResult mouseOver;
};
