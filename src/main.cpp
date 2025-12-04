#define SDL_MAIN_HANDLED true
#include <print>
#include <SDL3/SDL.h>
#include <SDL3/SDL_hints.h>
#include <X11/Xlib.h>
#include <X11/extensions/shape.h>
#include <X11/extensions/Xfixes.h>

void makeWindowClickThrough(SDL_Window *window) {
    SDL_PropertiesID WindowProps = SDL_GetWindowProperties(window);

    auto* display = static_cast<Display *>(SDL_GetPointerProperty(WindowProps, SDL_PROP_WINDOW_X11_DISPLAY_POINTER, nullptr));
    Window window_id = SDL_GetNumberProperty(WindowProps, SDL_PROP_WINDOW_X11_WINDOW_NUMBER, 0);

    XRectangle rect;
    rect.x = 0;
    rect.y = 0;
    rect.width = 0;
    rect.height = 0;

    XserverRegion region = XFixesCreateRegion(display, &rect, 1);
    XFixesSetWindowShapeRegion(display, window_id, ShapeInput, 0, 0, region);
    XFixesDestroyRegion(display, region);

    XFlush(display);
}

int main(int argc, char** argv) {
    const char* env = getenv("SDL_VIDEODRIVER");
    setenv("SDL_VIDEODRIVER", "x11", 1);

    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("test", 100, 100, SDL_WINDOW_ALWAYS_ON_TOP | SDL_WINDOW_BORDERLESS | SDL_WINDOW_TRANSPARENT);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, nullptr);

    makeWindowClickThrough(window);


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
