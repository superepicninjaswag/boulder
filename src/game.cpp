#include "Game.h"

#include <iostream>



void Init(SDL_Renderer *renderer)
{
    g_renderer.Init(renderer);

    int cube = g_ecs.GetIDs().CreateId();
    g_ecs.GetMeshes().Add(cube);
    g_ecs.GetTransforms().Add(cube, -1.0f, -1.0f, 5.0f);

    int cube2 = g_ecs.GetIDs().CreateId();
    g_ecs.GetMeshes().Add(cube2);
    g_ecs.GetTransforms().Add(cube2, 3.0f, 3.0f, 7.0f);
}

void Update(Uint32 deltaTime)
{
   // Set up rotation matrices
    g_renderer.theta += 0.001f * deltaTime;

    // Rotation Z
    g_renderer.matRotZ(0,0) = cosf(g_renderer.theta);
    g_renderer.matRotZ(0,1) = sinf(g_renderer.theta);
    g_renderer.matRotZ(1,0) = -sinf(g_renderer.theta);
    g_renderer.matRotZ(1,1) = cosf(g_renderer.theta);
    g_renderer.matRotZ(2,2) = 1;
    g_renderer.matRotZ(3,3) = 1;

    // Rotation X
    g_renderer.matRotX(0,0) = 1;
    g_renderer.matRotX(1,1) = cosf(g_renderer.theta * 0.5f);
    g_renderer.matRotX(1,2) = sinf(g_renderer.theta * 0.5f);
    g_renderer.matRotX(2,1) = -sinf(g_renderer.theta * 0.5f);
    g_renderer.matRotX(2,2) = cosf(g_renderer.theta * 0.5f);
    g_renderer.matRotX(3,3) = 1;
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