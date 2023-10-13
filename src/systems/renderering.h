#include <SDL2/SDL.h>
#include <vector>

#include "gmath.h"

extern Matrix4x4 projMat;  // Projection matrix

struct colour
{
    Uint8 r, g, b, a;
};

struct face
{
    vector3 points[3];
};

struct mesh
{
    std::vector<face> faces;
};


void drawLine(SDL_Renderer *renderer, int x1, int y1, int x2, int y2);
void drawTriangle(SDL_Renderer *renderer, const face &triangle);