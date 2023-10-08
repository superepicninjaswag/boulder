#include <SDL2/SDL.h>
#include <cmath>
#include "boulder.h"
#include "renderering.h"


mesh cube;
Matrix4x4 projMat;
Matrix4x4 matRotZ, matRotX;
float theta;

void Init()
{
    std::vector<face> tempFaces = {
        // SOUTH
        { 0.0f, 0.0f, 0.0f,    0.0f, 1.0f, 0.0f,    1.0f, 1.0f, 0.0f },
        { 0.0f, 0.0f, 0.0f,    1.0f, 1.0f, 0.0f,    1.0f, 0.0f, 0.0f },

        // EAST                                                      
        { 1.0f, 0.0f, 0.0f,    1.0f, 1.0f, 0.0f,    1.0f, 1.0f, 1.0f },
        { 1.0f, 0.0f, 0.0f,    1.0f, 1.0f, 1.0f,    1.0f, 0.0f, 1.0f },

        // NORTH                                                     
        { 1.0f, 0.0f, 1.0f,    1.0f, 1.0f, 1.0f,    0.0f, 1.0f, 1.0f },
        { 1.0f, 0.0f, 1.0f,    0.0f, 1.0f, 1.0f,    0.0f, 0.0f, 1.0f },

        // WEST                                                      
        { 0.0f, 0.0f, 1.0f,    0.0f, 1.0f, 1.0f,    0.0f, 1.0f, 0.0f },
        { 0.0f, 0.0f, 1.0f,    0.0f, 1.0f, 0.0f,    0.0f, 0.0f, 0.0f },

        // TOP                                                       
        { 0.0f, 1.0f, 0.0f,    0.0f, 1.0f, 1.0f,    1.0f, 1.0f, 1.0f },
        { 0.0f, 1.0f, 0.0f,    1.0f, 1.0f, 1.0f,    1.0f, 1.0f, 0.0f },

        // BOTTOM                                                    
        { 1.0f, 0.0f, 1.0f,    0.0f, 0.0f, 1.0f,    0.0f, 0.0f, 0.0f },
        { 1.0f, 0.0f, 1.0f,    0.0f, 0.0f, 0.0f,    1.0f, 0.0f, 0.0f },
    };
    cube.faces = tempFaces;

    // Projection matrix init
    float pi = 3.14159265358979323846264338327950288419716939937510;
    float aspectRatio = SCREEN_WIDTH/SCREEN_HEIGHT;
    float fov = pi/2;   // 90 Degrees
    float zFar = 1000;
    float zNear = 0.1;
    projMat(0, 0) = aspectRatio * fov;
    projMat(1, 1) = fov;
    projMat(2, 2) = zFar/(zFar - zNear);
    projMat(3, 2) = (-zFar * zNear) / (zFar - zNear);
    projMat(2, 3) = 1;
    projMat(3, 3) = 0;
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
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    // RENDER ALL THINGS THAT NEED RENDERING
    // TODO: Have each object that is rendered set the colour
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    for(auto f : cube.faces)
    {
        // Rotate
        face faceRotatedZ, faceRotatedZX;

        // Rotate in Z-Axis
        faceRotatedZ.points[0] = matRotZ * f.points[0];
        faceRotatedZ.points[1] = matRotZ * f.points[1];
        faceRotatedZ.points[2] = matRotZ * f.points[2];

        // Rotate in X-Axis
        faceRotatedZX.points[0] = matRotX * faceRotatedZ.points[0];
        faceRotatedZX.points[1] = matRotX * faceRotatedZ.points[1];
        faceRotatedZX.points[2] = matRotX * faceRotatedZ.points[2];


        // Translate face away from camera
        face &faceTranslated = faceRotatedZX;
        faceTranslated.points[0].z += 3.0f;
        faceTranslated.points[1].z += 3.0f;
        faceTranslated.points[2].z += 3.0f;

        // Project the face into screen space
        face faceProjected;
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

void Shutdown()
{
    return;
}