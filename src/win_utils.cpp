#include "win_utils.h"
#if SONYA_WINDOWS
#include <SDL3/SDL.h>
#include <windows.h>

void WinUtils::makeWindowClickThrough(SDL_Window *window) {
    const SDL_PropertiesID WindowProps = SDL_GetWindowProperties(window);

    HWND hwnd = static_cast<HWND>(SDL_GetPointerProperty(WindowProps, SDL_PROP_WINDOW_WIN32_HWND_POINTER, nullptr));

    // Make the window layered and transparent to mouse input
    LONG exStyle = GetWindowLong(hwnd, GWL_EXSTYLE);
    exStyle |= WS_EX_LAYERED | WS_EX_TRANSPARENT;
    SetWindowLong(hwnd, GWL_EXSTYLE, exStyle);

    // Optional: improve redraw quality
    SetLayeredWindowAttributes(hwnd, RGB(0, 0, 0), 255, LWA_ALPHA);
}
#endif