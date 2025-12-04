#include "linux_utils.h"
#include <SDL3/SDL.h>
#include <X11/Xlib.h>
#include <X11/extensions/shape.h>
#include <X11/extensions/Xfixes.h>

void LinuxUtils::makeWindowClickThrough(SDL_Window *window) {
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


