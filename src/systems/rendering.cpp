#include "rendering.h"

void drawLine(SDL_Renderer *renderer, int x1, int y1, int x2, int y2)
{
    SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
}

void drawTriangle(SDL_Renderer *renderer, const face &triangle) {
    drawLine(renderer, triangle.points[0].x, triangle.points[0].y, triangle.points[1].x, triangle.points[1].y);
    drawLine(renderer, triangle.points[1].x, triangle.points[1].y, triangle.points[2].x, triangle.points[2].y);
    drawLine(renderer, triangle.points[2].x, triangle.points[2].y, triangle.points[0].x, triangle.points[0].y);
}