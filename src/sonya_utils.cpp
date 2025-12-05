#include "sonya_utils.h"

void SonyaUtils::makeWindowClickThrough(SDL_Window *window) {
#if SONYA_LINUX
    LinuxUtils::makeWindowClickThrough(window);
#elif SONYA_WINDOWS
    WinUtils::makeWindowClickThrough(window);
#endif
}
