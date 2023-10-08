#include <SDL2/SDL.h>
#include <cstdlib>

void Init();
void Update(Uint32 deltaTime);
void Render(SDL_Renderer *renderer);
void Shutdown();

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 800;