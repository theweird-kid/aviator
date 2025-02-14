#ifndef ENTITY_MANAGER_HPP
#define ENTITY_MANAGER_HPP

#include "./entity.hpp"
#include <SDL2/SDL_events.h>
#include <random>
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

    void handleEntities(SDL_Event& event) {
        for(auto& e: m_entities) {
            e.handleEvent(event);
        }
    }

    void render(const SDL_Rect& camera)
    {
        for(auto& e: m_entities) {
            if(e.isAlive()) e.render(camera);
        }
    }

    void resetPositions(const SDL_Rect& camera)
        {
            for(auto& e: m_entities) {
                if (e.getX() < camera.x - e.getWidth()) {
                    if(e.getType() == Entity::Type::PIPE_LOWER || e.getType() == Entity::Type::PIPE_UPPER) {
                        randomizePipePosition(e, camera);
                    } else {
                        e.setX(camera.x + camera.w);
                    }
                }
            }
        }

private:
void randomizePipePosition(Entity& pipe, const SDL_Rect& camera)
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> disY(0, 100);

        int gapY = disY(gen);
        if(gapY%2) {
            pipe.setX(camera.x + camera.w);
            pipe.setAlive(true);
        }
        else {
            pipe.setAlive(false);
        }
    }

private:
    std::vector<Entity> m_entities;
};

#endif // ENTITY_MANAGER_HPP
