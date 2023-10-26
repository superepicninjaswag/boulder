#pragma once

#include <vector>

#include "../Boulder.h"
#include "../ECS/Pool.h"
#include "../Components/Components.h"
#include "./Geometry.h"


extern Matrix4x4 g_projectionMatrix;

void drawLine(SDL_Renderer *renderer, int x1, int y1, int x2, int y2);
void drawTriangle(SDL_Renderer *renderer, const Face &triangle, const Colour c);
void drawFilledTriangle(SDL_Renderer *renderer, const Face &triangle, const Colour c);