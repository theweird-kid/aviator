#ifndef GAME_HPP
#define GAME_HPP

#include "../constants.hpp"
#include "../Entity/entity_manager.hpp"
#include "../Camera/camera.hpp"
#include <SDL2/SDL_render.h>

class Game
{
public:

    // Constructor
    Game(SDL_Renderer* renderer)
        : m_renderer(renderer), m_entityManager(std::make_unique<EntityManager>()) ,
        m_camera(SCREEN_WIDTH, SCREEN_HEIGHT)
    {}

    // Destructor
    ~Game() = default;

    void init()
    {
        // Add Player Entity
        m_entityManager->addEntity(Entity(Entity::Type::PLAYER, "assets/airplane.bmp", 10, 300, 200, 100, m_renderer));
    }

    void handleEvents(SDL_Event& event)
    {
        m_entityManager->handleEntities(event);
    }

    void update()
    {
        // Update the camera position based on the player position
        auto& player = m_entityManager->getPlayer();
        m_camera.update(player.getX());

    }

    void render()
    {
        m_entityManager->render();
    }

private:
    std::unique_ptr<EntityManager> m_entityManager;
    SDL_Renderer* m_renderer;
    Camera m_camera;
};

#endif // GAME_HPP
