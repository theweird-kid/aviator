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
        // Load Background Texture
        m_backgroundTexture = std::make_unique<Texture>("assets/background.bmp", SCREEN_WIDTH, SCREEN_HEIGHT, m_renderer);

        // Add Player Entity
        m_entityManager->addEntity(Entity(Entity::Type::PLAYER, "assets/airplane.bmp", 10, 300, 200, 100, m_renderer));
        // Add Upper Pipe Entity
        m_entityManager->addEntity(Entity(Entity::Type::PIPE_UPPER, "assets/upper_pipe.bmp", 600, 0, 60, 300, m_renderer));
        // Add Lower Pipe Entity
        m_entityManager->addEntity(Entity(Entity::Type::PIPE_LOWER, "assets/lower_pipe.bmp", 1200, SCREEN_HEIGHT-300, 60, 300, m_renderer));
    }

    void handleEvents(SDL_Event& event)
    {
        m_entityManager->handleEntities(event);
    }

    void update()
    {
        // Update the camera position
        m_camera.update();

        // Reset positions of elements when they move off-screen
        m_entityManager->resetPositions(m_camera.getViewPort());
    }

    void render()
    {
        // Set the viewport based on the camera's position
        SDL_RenderSetViewport(m_renderer, &m_camera.getViewPort());

        // Render the background
        renderBackground();

        // Render the entities
        m_entityManager->render(m_camera.getViewPort());
    }

private:
    void renderBackground()
    {
        int bgWidth = SCREEN_WIDTH;
        int bgHeight = SCREEN_HEIGHT;
        int cameraX = m_camera.getViewPort().x;

        // Calculate the number of background tiles needed to cover the screen
        int numTiles = (SCREEN_WIDTH / bgWidth) + 5;

        for (int i = 0; i < numTiles; ++i)
        {
            int x = (i * bgWidth) - (cameraX % bgWidth);
            m_backgroundTexture->render(x, 0);
        }
    }

private:
    std::unique_ptr<EntityManager> m_entityManager;
    SDL_Renderer* m_renderer;
    Camera m_camera;
    std::unique_ptr<Texture> m_backgroundTexture;
};

#endif // GAME_HPP
