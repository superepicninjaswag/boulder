#include <SDL2/SDL.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <cstdlib>
#include <sstream>

void Init();
void Update(Uint32 deltaTime);
void Render(SDL_Renderer *renderer);
void Shutdown();

const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 768;

extern int actualWidth;
extern int actualHeight;