#include "Rendering.h"

Renderer::Renderer()
{
    projMat(0, 0) = aspectRatio * fovRad;
    projMat(1, 1) = fovRad;
    projMat(2, 2) = zFar / (zFar - zNear);
    projMat(3, 2) = (-zFar * zNear) / (zFar - zNear);
    projMat(2, 3) = 1.0f;
    projMat(3, 3) = 0.0f;
}

void drawLine(SDL_Renderer *renderer, int x1, int y1, int x2, int y2)
{
    SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
}

void drawTriangle(SDL_Renderer *renderer, const Face &triangle) {
    drawLine(renderer, triangle.points[0].x, triangle.points[0].y, triangle.points[1].x, triangle.points[1].y);
    drawLine(renderer, triangle.points[1].x, triangle.points[1].y, triangle.points[2].x, triangle.points[2].y);
    drawLine(renderer, triangle.points[2].x, triangle.points[2].y, triangle.points[0].x, triangle.points[0].y);
}