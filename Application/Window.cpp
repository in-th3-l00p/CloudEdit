#include <string>
#include <stdexcept>
#include "Window.h"

namespace Graphics {
    Window::Window(const char *title, const int width, const int height) {
        SDL_CreateWindowAndRenderer(
                width, height,
                SDL_WINDOW_RESIZABLE,
                &window, &renderer
                );
        if (window == nullptr || renderer == nullptr)
            throw std::runtime_error(
                    std::string("Failed to initialize window or renderer ") +
                    SDL_GetError()
                    );
        SDL_SetWindowTitle(window, title);
    }

    Window::~Window() {
        SDL_DestroyWindow(window);
        SDL_DestroyRenderer(renderer);
    }

    void Window::clear() {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
    }

    void Window::update() {
        SDL_RenderPresent(renderer);
    }
} // Graphics