#ifndef APPLICATION_ENTITYSYSTEM_H
#define APPLICATION_ENTITYSYSTEM_H

#include <string>
#include <functional>
#include <vector>
#include "NameContainer.h"
#include "Window.h"

/**
 * Defining the entity system of the application
 * An entity is simply an object that responds to events and has callbacks
 * used by different parts of the application
 */
namespace EntitySystem {
    using Action = std::function<void()>;

    struct Event {
        std::string name;
        std::vector<Action> actions;

        explicit Event(std::string name, const std::vector<Action> &actions = {});
        void raise();
    };

    class Entity {
    protected:
        Container::NameContainer<Event> eventContainer;

    public:
        std::string name;

        explicit Entity(std::string name);

        [[nodiscard]] const Container::NameContainer<Event>& getEventContainer() const {
            return eventContainer;
        }

        virtual void update(double deltaTime) = 0;
    };

    class GraphicsEntity: public Entity {
    public:
        explicit GraphicsEntity(std::string name);

        virtual void render(Graphics::Window& window) = 0;
    };
} // EntitySystem

#endif //APPLICATION_ENTITYSYSTEM_H
