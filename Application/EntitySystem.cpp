#include <utility>
#include <stdexcept>
#include "EntitySystem.h"

namespace EntitySystem {
    Event::Event(std::string name, const std::vector<Action> &actions)
        : name(std::move(name)), actions(actions)
        {}

    void Event::raise() {
        for (const auto& action: actions)
            action();
    }

    Entity::Entity(std::string name) {
        this->name = std::move(name);
    }

    GraphicsEntity::GraphicsEntity(std::string name) : Entity(std::move(name)) {

    }
} // EntitySystem