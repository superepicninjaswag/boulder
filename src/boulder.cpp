#include "Boulder.h"

int g_actualWidth = 0;
int g_actualHeight = 0;

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

    // Text library setup
    if (TTF_Init() == -1)
    {
        SDL_Log("Unable to init fonts: %s", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    TTF_Font *font = TTF_OpenFont("../Fonts/Lato/Lato-Regular.ttf", 16);
    if (font == nullptr)
    {
        SDL_Log("Unable to load fonts: %s", SDL_GetError());
        TTF_Quit();
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    SDL_Color fpsColour = {255, 255, 255};

    // Game specific init
    Init(renderer);

    // FPS and other times
    int frameCount = 0;
    float alpha = 0.8f;
    float oldFps = 0.0f;
    float newFps = 0.0f;
    float rawFps;
    float startTime = SDL_GetTicks();
    SDL_Surface* surfaceMessage;
    SDL_Texture* message;
    SDL_Rect textRect;

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

        // Clear screen and render
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        Render();
        frameCount += 1;

        // FPS and other time displays
        if (currentTime - startTime >= 1000)
        {
            // FPS
            rawFps = frameCount / ((currentTime - startTime) / 1000);
            newFps = alpha*rawFps + (1.0f - alpha)*oldFps;
            oldFps = newFps;

            startTime = currentTime;
            frameCount = 0;

            // Draw text to screen
            std::stringstream ss;
            ss << "FPS: " << newFps << " | deltaTime: " << (1000/newFps);

            surfaceMessage = TTF_RenderText_Solid(font, ss.str().c_str(), fpsColour);
            message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

            textRect.x = 10; // E.g., 10 pixels from the left of the window
            textRect.y = 10; // E.g., 10 pixels from the top of the window
            textRect.w = surfaceMessage->w;
            textRect.h = surfaceMessage->h;
        }

        // Update screen with newly rendered frame
        SDL_RenderCopy(renderer, message, NULL, &textRect); // Fps counter
        SDL_RenderPresent(renderer);
    }

    // Game specific cleanup
    Shutdown();
    
    // Cleanup SDL before exit
    SDL_FreeSurface(surfaceMessage);
    SDL_DestroyTexture(message);
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
