#pragma once

#if SONYA_LINUX
#include "linux_utils.h"
#elif SONYA_WINDOWS
#include "win_utils.h"
#endif

namespace SonyaUtils {
    void makeWindowClickThrough(SDL_Window* window);
}
