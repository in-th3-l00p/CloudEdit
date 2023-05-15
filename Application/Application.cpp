#include <string>
#include <SDL2/SDL_ttf.h>
#include "Application.h"
#include "Widgets.h"

Application::Application() {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
        throw std::runtime_error(
                std::string("Failed to initialize SDL2, ") +
                SDL_GetError()
                );
    if (TTF_Init() < 0)
        throw std::runtime_error(
                std::string("Failed to initialize SDL2_TTF, ") +
                TTF_GetError()
        );
    window = std::make_unique<Graphics::Window>();
    addGraphicsEntity(new UI::Label("label", {10, 10}, "Hello, World!"));
}

Application::~Application() {
    SDL_Quit();
}

void Application::run() {
    while (running) {
        // event driven programming
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    running = false;
                    break;
            }
        }

        for (auto& entity: entities)
            entity.update(0.0);

        window->clear();

        for (auto& entity: graphicsEntities)
            entity.render(*window);

        window->update();
    }
}

void Application::addEntity(EntitySystem::Entity *entity) {
    entities.add(entity);
}

void Application::addGraphicsEntity(EntitySystem::GraphicsEntity *entity) {
    addEntity(entity);
    graphicsEntities.add(entity);
}
