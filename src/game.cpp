#include "Game.h"

#include <iostream>

Matrix4x4 projMat;
Matrix4x4 matRotZ, matRotX;
float theta = 0;

void Init()
{
   int cube = g_ecs.GetIDs().CreateId();
   g_ecs.GetMeshes().Add(cube);
   g_ecs.GetTransforms().Add(cube);
}

void Update(Uint32 deltaTime)
{
   // Set up rotation matrices
    theta += 0.001f * deltaTime;

    // Rotation Z
    matRotZ(0,0) = cosf(theta);
    matRotZ(0,1) = sinf(theta);
    matRotZ(1,0) = -sinf(theta);
    matRotZ(1,1) = cosf(theta);
    matRotZ(2,2) = 1;
    matRotZ(3,3) = 1;

    // Rotation X
    matRotX(0,0) = 1;
    matRotX(1,1) = cosf(theta * 0.5f);
    matRotX(1,2) = sinf(theta * 0.5f);
    matRotX(2,1) = -sinf(theta * 0.5f);
    matRotX(2,2) = cosf(theta * 0.5f);
    matRotX(3,3) = 1;
}

void Render(SDL_Renderer *renderer)
{
    // RENDER ALL THINGS THAT NEED RENDERING
    // TODO: Have each object that is rendered set the colour
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    MeshComponent *mesh = g_ecs.GetMeshes().Get(0);
    TransformComponent *transform = g_ecs.GetTransforms().Get(0);
    
    for(auto f : mesh->cube)
    {
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

        // Translate face away from camera
        Face faceTranslated = faceRotatedZX;
        faceTranslated.points[0].z += 3.0f;
        faceTranslated.points[1].z += 3.0f;
        faceTranslated.points[2].z += 3.0f;
        faceTranslated.points[0].x += 3.0f;
        faceTranslated.points[1].x += 3.0f;
        faceTranslated.points[2].x += 3.0f;

        // Project the face into screen space
        Face faceProjected;
        faceProjected.points[0] = g_renderer.projMat*faceTranslated.points[0];
        faceProjected.points[1] = g_renderer.projMat*faceTranslated.points[1];
        faceProjected.points[2] = g_renderer.projMat*faceTranslated.points[2];

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

void Shutdown()
{
    return;
}