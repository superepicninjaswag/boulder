#pragma once

#include "Rendering.h"
#include <thread>
#include <algorithm>

class Renderer
{
private:
    // Projection matrix init
    float pi = 3.14159265358979323846264338327950288419716939937510;
    float fovDeg = 70.0;
    float fovRad = 1.0 / tanf(fovDeg * 0.5f / 180.0f * pi);
    float zFar = 1000.0f;
    float zNear = 0.1f;
    float aspectRatio = SCREEN_HEIGHT / SCREEN_WIDTH;
    SDL_Renderer *renderer;
    Vec3 camera;
public:
    float theta = 0;
    Matrix4x4 matRotZ, matRotX;

    Renderer();
    void Init(SDL_Renderer *renderer);
    void Render(Pool<MeshComponent> *meshes, Pool<TransformComponent> *transforms);
};