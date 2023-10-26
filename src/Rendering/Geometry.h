#pragma once

#include <SDL2/SDL.h>
#include "../Util/GameMath.h"

struct Colour
{
    Uint8 r = 255;
    Uint8 g = 255;
    Uint8 b = 255;
    Uint8 a = 255;
};

struct Face
{
public:
    Vec3 points[3];
    Colour colour;

    bool operator<(const Face &b) const;
};