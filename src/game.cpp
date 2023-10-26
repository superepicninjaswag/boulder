#include "Game.h"

#include <stdlib.h>

void Init(SDL_Renderer *renderer)
{
    g_renderer.Init(renderer);

    int limit = 8;
    for (int i = 0; i < limit; i++)
    {
        for(int j = 0; j < limit; j++)
        {
            float x = i - limit/2;
            float y = j - limit/2;
            float z = 12;
            if(i % 2 == 0)
            {
                z = z - 6;
            }
            
            int newEntity = g_ecs.GetIDs().CreateId();
            g_ecs.GetMeshes().Add(newEntity);
            g_ecs.GetTransforms().Add(newEntity, x, y, z);
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

    Pool<MeshComponent> *meshes = &g_ecs.GetMeshes();
    Pool<TransformComponent> *transforms = &g_ecs.GetTransforms();
    
    g_renderer.Render(meshes, transforms);
}

void Shutdown()
{
    return;
}