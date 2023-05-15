#ifndef APPLICATION_APPLICATION_H
#define APPLICATION_APPLICATION_H

#include <memory>
#include <SDL2/SDL.h>
#include "Window.h"
#include "EntitySystem.h"
#include "NameContainer.h"

class Application {
private:
    std::unique_ptr<Graphics::Window> window;
    bool running = true;

    Container::NameContainer<EntitySystem::Entity> entities;
    Container::NameContainer<EntitySystem::GraphicsEntity> graphicsEntities;

    void addEntity(EntitySystem::Entity* entity);
    void addGraphicsEntity(EntitySystem::GraphicsEntity* entity);

public:
    Application();
    ~Application();

    void run();
};


#endif //APPLICATION_APPLICATION_H
