#include "Game.h"

#include <iostream>

Matrix4x4 matRotZ, matRotX;
float theta = 0;

void Init(SDL_Renderer *renderer)
{
    g_renderer.Init(renderer);

    int cube = g_ecs.GetIDs().CreateId();
    g_ecs.GetMeshes().Add(cube);
    g_ecs.GetTransforms().Add(cube, -1.0f, -1.0f, 6.0f);

    int cube2 = g_ecs.GetIDs().CreateId();
    g_ecs.GetMeshes().Add(cube2);
    g_ecs.GetTransforms().Add(cube2, 5.0f, 5.0f, 12.0f);
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

void Render()
{
    // RENDER ALL THINGS THAT NEED RENDERING
    // TODO: Have each object that is rendered set the colour

    Pool<MeshComponent> *meshes = &g_ecs.GetMeshes();
    Pool<TransformComponent> *transforms = &g_ecs.GetTransforms();
    
    g_renderer.Render(meshes, transforms);
}

void Shutdown()
{
    return;
}