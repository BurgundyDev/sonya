#pragma once
#if SONYA_WINDOWS
#include "SDL3/SDL.h"

namespace WinUtils {
    void makeWindowClickThrough(SDL_Window* window);
} // WinUtils
#endif