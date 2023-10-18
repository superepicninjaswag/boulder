#pragma once

#include <SDL2/SDL.h>
#include "../Util/GameMath.h"

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