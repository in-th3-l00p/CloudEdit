#ifndef APPLICATION_WINDOW_H
#define APPLICATION_WINDOW_H

#include <SDL2/SDL.h>
#include "Configuration.h"

namespace Graphics {
    struct Window {
        SDL_Window* window;
        SDL_Renderer* renderer;

        explicit Window(
            const char* title = Config::windowTitle,
            int width = Config::windowWidth,
            int height = Config::windowHeight
            );
        ~Window();

        void clear();
        void update();
    };

} // Graphics

#endif //APPLICATION_WINDOW_H
