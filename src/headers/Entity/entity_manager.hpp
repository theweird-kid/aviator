#ifndef ENTITY_MANAGER_HPP
#define ENTITY_MANAGER_HPP

#include "./entity.hpp"
#include <SDL2/SDL_events.h>
#include <vector>

class EntityManager
{
public:
    EntityManager() = default;
    ~EntityManager() = default;

    void addEntity(Entity&& entity)
    {
        m_entities.push_back(std::move(entity));
    }

    Entity& getPlayer()
    {
        for(auto& e: m_entities) {
            if(e.getType() == Entity::Type::PLAYER) {
                return e;
            }
        }
    }

    void handleEntities(SDL_Event& event) {
        for(auto& e: m_entities) {
            e.handleEvent(event);
        }
    }

    void render()
    {
        for(auto& e: m_entities) {
            e.render();
        }
    }

private:
    std::vector<Entity> m_entities;
};

#endif // ENTITY_MANAGER_HPP
