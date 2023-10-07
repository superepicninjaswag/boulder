#include <SDL2/SDL.h>
#include "boulder.h"

void Init()
{
    return;
}

void Update(Uint32 deltaTime)
{
    return;
}

void Render(SDL_Renderer *renderer)
{
    // Hardware-accelerated Rendering: Draw a red diagonal line
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderDrawLine(renderer, 0, 0, rand() % SCREEN_WIDTH, rand() % SCREEN_HEIGHT);
    SDL_RenderPresent(renderer);
}

void Shutdown()
{
    return;
}