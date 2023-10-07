#include "boulder.h"

int main(int argc, char* argv[])
{
    if (SDL_InitSubSystem(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0)
    {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow("Boulder",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          SCREEN_WIDTH,
                                          SCREEN_HEIGHT,
                                          0);
    if (window == NULL)
    {
        SDL_Log("Unable to create window: %s", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window,
                                                -1,
                                                SDL_RENDERER_SOFTWARE);
    if (renderer == NULL)
    {
        SDL_Log("Unable to create renderer: %s", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Game specific init
    Init();

    // Main Game Loop
    SDL_Event event;
    bool running = true;
    Uint32 lastTime = SDL_GetTicks();
    Uint32 deltaTime, currentTime;
    while (running)
    {
        // Input and window events
        while (SDL_PollEvent(&event))
        {
            // TODO: Process events like input, etc.
            if (event.type == SDL_QUIT)
            {
                running = false;
            }
        }

        // Game systems
        currentTime = SDL_GetTicks();
        deltaTime = currentTime - lastTime;
        Update(deltaTime);
        lastTime = currentTime;

        // Draw visuals
        Render(renderer);
    }

    // Game specific cleanup
    Shutdown();
    
    // Cleanup before exit
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
