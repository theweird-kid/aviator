#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <SDL2/SDL_rect.h>

class Camera
{
public:
    Camera(int screenWidth, int screenHeight)
        : m_screenWidth(screenWidth), m_screenHeight(screenHeight)
    {
        m_viewPort = {0, 0, m_screenWidth, m_screenHeight};
        m_velocity = 5.0f;
    }

    ~Camera() = default;

    void update()
    {
        // Moving the camera horizontally based on the player position
        m_viewPort.x += m_velocity;

        // Clamp the camera position to the bounds of the world
        if (m_viewPort.x < 0)
        {
            m_viewPort.x = 0;
        }
        if(m_viewPort.x > WORLD_WIDTH - m_screenWidth) {
            m_viewPort.x = WORLD_WIDTH - m_screenWidth;
        }
    }

    const SDL_Rect& getViewPort() const { return m_viewPort; }

private:
    int m_screenWidth;
    int m_screenHeight;
    float m_velocity;
    SDL_Rect m_viewPort;

    static constexpr int WORLD_WIDTH = 1280;
    static constexpr int WORLD_HEIGHT = 720;
};

#endif // CAMERA_HPP
