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
    }

    ~Camera() = default;

    void update(float playerX)
    {
        // Moving the camera horizontally based on the player position
        m_viewPort.x = static_cast<int>(playerX - m_screenWidth / 2);

        // Clamp the camera position to the bounds of the world
        if (m_viewPort.x < 0)
        {
            m_viewPort.x = 0;
        }
        if(m_viewPort.x > WORLD_WIDTH - m_screenWidth) {
            m_viewPort.x = WORLD_WIDTH - m_screenWidth;
        }
    }

private:
    int m_screenWidth;
    int m_screenHeight;
    SDL_Rect m_viewPort;

    static constexpr int WORLD_WIDTH = 1280;
    static constexpr int WORLD_HEIGHT = 720;
};

#endif // CAMERA_HPP
