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

void Renderer::Init(SDL_Renderer *renderer)
{
    this->renderer = renderer;
}

void Renderer::Render(Pool<MeshComponent> *meshes, Pool<TransformComponent> *transforms)
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    for (int i = 0; i < meshes->Size(); i++)
    {
        for(auto f : meshes->Get(i)->cube)
            {
                /*
                // Rotate
                Face faceRotatedZ, faceRotatedZX;

                // Rotate in Z-Axis
                faceRotatedZ.points[0] = matRotZ * f.points[0];
                faceRotatedZ.points[1] = matRotZ * f.points[1];
                faceRotatedZ.points[2] = matRotZ * f.points[2];

                // Rotate in X-Axis
                faceRotatedZX.points[0] = matRotX * faceRotatedZ.points[0];
                faceRotatedZX.points[1] = matRotX * faceRotatedZ.points[1];
                faceRotatedZX.points[2] = matRotX * faceRotatedZ.points[2];
                */

                // Translate face away from camera
                Face faceTranslated = f;
                int transformId = transforms->MirrorIdToEntityId(i);
                faceTranslated.points[0] = faceTranslated.points[0] + transforms->Get(transformId)->v;
                faceTranslated.points[1] = faceTranslated.points[1] + transforms->Get(transformId)->v;
                faceTranslated.points[2] = faceTranslated.points[2] + transforms->Get(transformId)->v;

                // Project the face into screen space
                Face faceProjected;
                faceProjected.points[0] = projMat*faceTranslated.points[0];
                faceProjected.points[1] = projMat*faceTranslated.points[1];
                faceProjected.points[2] = projMat*faceTranslated.points[2];

                // Scale from normalized to screen size
                faceProjected.points[0].x = (faceProjected.points[0].x + 1) * 0.5 * (float) SCREEN_WIDTH;
                faceProjected.points[1].x = (faceProjected.points[1].x + 1) * 0.5 * (float) SCREEN_WIDTH;
                faceProjected.points[2].x = (faceProjected.points[2].x + 1) * 0.5 * (float) SCREEN_WIDTH;
                faceProjected.points[0].y = (faceProjected.points[0].y + 1) * 0.5 * (float) SCREEN_HEIGHT;
                faceProjected.points[1].y = (faceProjected.points[1].y + 1) * 0.5 * (float) SCREEN_HEIGHT;
                faceProjected.points[2].y = (faceProjected.points[2].y + 1) * 0.5 * (float) SCREEN_HEIGHT;

                drawTriangle(renderer, faceProjected);
            }
    }
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