#pragma once

#include <SDL2/SDL.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <cmath>
#include <cstdlib>
#include <sstream>

void Init(SDL_Renderer *renderer);
void Update(Uint32 deltaTime);
void Render();
void Shutdown();

const float SCREEN_WIDTH = 1024.0;
const float SCREEN_HEIGHT = 768.0;