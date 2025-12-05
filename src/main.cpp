#define SDL_MAIN_HANDLED true
#include <cstdlib>
#include <fmt/base.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_hints.h>
#include "sonya_utils.h"

int main(int argc, char** argv) {
#if SONYA_LINUX
    const char* env = getenv("SDL_VIDEODRIVER");
    setenv("SDL_VIDEODRIVER", "x11", 1);
#endif

    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("test", 100, 100, SDL_WINDOW_ALWAYS_ON_TOP | SDL_WINDOW_BORDERLESS | SDL_WINDOW_TRANSPARENT);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, nullptr);

    SonyaUtils::makeWindowClickThrough(window);

    SDL_Event e;
    bool quit = false;
    while (!quit){
        while (SDL_PollEvent(&e)){
            if (e.type == SDL_EVENT_QUIT){
                quit = true;
            }
        }

        SDL_SetRenderDrawColor(renderer, 255, 2, 200, 10);
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
        SDL_Delay(0);
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
    setenv("SDL_VIDEODRIVER", env, 1);

    return 0;
}
