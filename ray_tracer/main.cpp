
#include <SDL.h>

#include "main_trace.hpp"
#include <random>
#include <time.h>

const int SCREEN_WIDTH = 768;
const int SCREEN_HEIGHT = 768;

int WinMain(int argc, char* argv[])
{
    srand(time(NULL));

    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow("Ray Tracer",
                            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                    SCREEN_WIDTH, SCREEN_HEIGHT,
                                        SDL_WINDOW_BORDERLESS);

    SDL_Surface* window_surface = SDL_GetWindowSurface(window);
    SDL_Surface* our_surface = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32, 0, 0, 0, 0);

    // Main tracing function
    for (size_t i = 0; i < 1; i++) {
        trace((uint32_t*)our_surface->pixels, SCREEN_WIDTH, SCREEN_HEIGHT);
    }

    SDL_BlitSurface(our_surface, NULL, window_surface, NULL);
    SDL_UpdateWindowSurface(window);

    SDL_Event eve;
    while (true) {
        if (SDL_PollEvent(&eve)) {
            if (eve.type == SDL_KEYDOWN) {
                break;
            } else {
                SDL_Delay(100);
            }
        }
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}