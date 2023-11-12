#include "Game.h"
#include "Systems/Systems.h"
#include "Util/GetModelNumber.h"

#include <stdlib.h>
#include <string>
#include <iostream>

ECS g_ecs;
Renderer g_renderer;

void Init(SDL_Renderer *renderer)
{
    g_renderer.Init(renderer);
    MeshResourceObjLoader(g_ecs);

    int limit = 8;
    for (int i = 0; i < limit; i++)
    {
        for (int j = 0; j < limit; j++)
        {
            int newEntity = g_ecs.GetIDs().CreateId();
            Pool<MeshComponent> &meshes = g_ecs.GetMeshes();
            meshes.Add(newEntity, GetModelNumber(g_ecs.GetMeshResources(), "cube"));
            g_ecs.GetTransforms().Add(newEntity);
            g_ecs.GetTransforms().Get(newEntity)->v.x = 2*(i-limit/2);
            g_ecs.GetTransforms().Get(newEntity)->v.y = 2*(j-limit/2);
            g_ecs.GetTransforms().Get(newEntity)->v.z = 25;
        }
    }
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

    Pool<MeshComponent> &meshes = g_ecs.GetMeshes();
    Pool<MeshResourceComponent> &meshResources = g_ecs.GetMeshResources();
    Pool<TransformComponent> &transforms = g_ecs.GetTransforms();

    g_renderer.Render(meshes, transforms, meshResources);
}

void Shutdown()
{
    return;
}