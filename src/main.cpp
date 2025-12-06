#define SDL_MAIN_HANDLED true
#include <cstdlib>
#include <vector>
#include <fmt/base.h>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include "sonya_utils.h"

enum move_type {
    MOVE,
    SHIFT
};

int main(int argc, char** argv) {
#if SONYA_LINUX
    const char* env = getenv("SDL_VIDEODRIVER");
    setenv("SDL_VIDEODRIVER", "x11", 1);
#endif

    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* main_window = SDL_CreateWindow("sonya", 144, 96, SDL_WINDOW_ALWAYS_ON_TOP | SDL_WINDOW_BORDERLESS | SDL_WINDOW_TRANSPARENT);
    SDL_DisplayID current_display = SDL_GetDisplayForWindow(main_window);
    auto *display_bounds = new SDL_Rect;
    SDL_GetDisplayBounds(current_display, display_bounds);
    SDL_Renderer* renderer = SDL_CreateRenderer(main_window, nullptr);
    SDL_Surface * image = IMG_Load("spritesheet.png");
    SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_SetTextureScaleMode(texture, SDL_SCALEMODE_NEAREST);

    SonyaUtils::makeWindowClickThrough(main_window);

    int Y_POSITION = display_bounds->h - 200;
    int MOVEMENT_DELAY = 5000;
    int MOVEMENT_SPEED = 16;
    std::vector<move_type> moves = { SHIFT, MOVE };
    int current_move = 0;
    int curr_time = 0;
    int *prev_x = new int;
    bool moving_forward = true;
    SDL_SetWindowPosition(main_window, 0, Y_POSITION);

    SDL_FRect srcrect = { 0, 0, 48, 32 };
    SDL_FRect dstrect = { 0, 0, 96, 64 };
    int FRAME_COUNT = 2;

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 1);
    SDL_RenderClear(renderer);

    SDL_Event event;
    bool quit = false;
    while (!quit){
        while (SDL_PollEvent(&event)){
            if (event.type == SDL_EVENT_KEY_DOWN){
                if (event.key.key == SDLK_ESCAPE) {
                    quit = true;
                }
            }
        }

        if (curr_time == MOVEMENT_DELAY) {
            curr_time = 0;
            if (moves[current_move] == MOVE) {
                current_move = (current_move + 1) % FRAME_COUNT;
                srcrect.x = srcrect.w * current_move;
                int *old_x = new int;
                SDL_GetWindowPosition(main_window, old_x, nullptr);
                if (*prev_x == *old_x) {
                    moving_forward = !moving_forward;
                }
                int movement_dir = moving_forward ? 1 : -1;
                SDL_SetWindowPosition(main_window, *old_x + (MOVEMENT_SPEED * movement_dir), Y_POSITION);
                SDL_GetWindowPosition(main_window, prev_x, nullptr);
            } else {
                current_move = (current_move + 1) % FRAME_COUNT;
                srcrect.x = srcrect.w * current_move;
            }
        } else {
            curr_time++;
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 1);
        SDL_RenderClear(renderer);
        SDL_RenderTextureRotated(renderer, texture, &srcrect, &dstrect, 0, nullptr, moving_forward ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL);
        SDL_RenderPresent(renderer);
        SDL_Delay(0);
    }

    SDL_DestroyTexture(texture);
    SDL_DestroySurface(image);
    SDL_DestroyWindow(main_window);
    SDL_Quit();
#if SONYA_LINUX
    if (env != nullptr) {
        setenv("SDL_VIDEODRIVER", env, 1);
    } else {
        setenv("SDL_VIDEODRIVER", "", 1);
    }
#endif

    return 0;
}
