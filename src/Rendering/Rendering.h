#pragma once

#include <vector>

#include "../Boulder.h"
#include "../ECS/Pool.h"
#include "../Components/Components.h"
#include "./Geometry.h"

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

    Matrix4x4 projMat;
    Renderer();
    void Init(SDL_Renderer *renderer);
    void Render(Pool<MeshComponent> *meshes, Pool<TransformComponent> *transforms);
};

void drawLine(SDL_Renderer *renderer, int x1, int y1, int x2, int y2);
void drawTriangle(SDL_Renderer *renderer, const Face &triangle);
void drawFilledTriangle(SDL_Renderer *renderer, const Face &triangle, const Colour c);