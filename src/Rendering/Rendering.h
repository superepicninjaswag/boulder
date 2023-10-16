#pragma once

#include <SDL2/SDL.h>
#include <vector>

#include "../Util/GameMath.h"
#include "../Boulder.h"

struct colour
{
    Uint8 r, g, b, a;
};

struct Face
{
    Vec3 points[3];
};

struct mesh
{
    std::vector<Face> faces;
};

class Renderer
{
private:
    // Projection matrix init
    float pi = 3.14159265358979323846264338327950288419716939937510;
    float fovDeg = 90.0;
    float fovRad = 1.0 / tanf(fovDeg * 0.5f / 180.0f * pi);
    float zFar = 1000.0f;
    float zNear = 0.1f;
    float aspectRatio = (float) SCREEN_HEIGHT / (float) SCREEN_WIDTH;
public:
    Matrix4x4 projMat;
    Renderer();
};


void drawLine(SDL_Renderer *renderer, int x1, int y1, int x2, int y2);
void drawTriangle(SDL_Renderer *renderer, const Face &triangle);