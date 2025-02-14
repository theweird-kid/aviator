#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "../constants.hpp"
#include "../Texture/texture.hpp"
#include <SDL2/SDL_events.h>

class Entity
{
public:
    enum class Type
    {
        PLAYER,
        OBSTACLE,
        PIPE_UPPER,
        PIPE_LOWER
    };

public:
    // Constructor
    Entity(Type type, const std::string& path, float x, float y, float width, float height, SDL_Renderer* renderer)
        : m_type(type),
        m_texture(std::make_unique<Texture>(path, width, height, renderer)),
        m_x(x), m_y(y), m_width(width), m_height(height)
    {
        if(m_type == Type::PLAYER) {
            m_Xvelocity = 0.0f;
            m_Yvelocity = 5.0f;
        }

        if(m_type == Type::PIPE_LOWER || m_type == Type::PIPE_UPPER) {
            m_Xvelocity = -10.0f;
            m_Yvelocity = 0.0f;
        }
    }

    // Move constructor
    Entity(Entity&& other) noexcept
        : m_type(other.m_type),
        m_x(other.m_x), m_y(other.m_y),
        m_Xvelocity(other.m_Xvelocity), m_Yvelocity(other.m_Yvelocity),
        m_width(other.m_width), m_height(other.m_height),
        m_texture(std::move(other.m_texture)) {}

    // Move assignment operator
    Entity& operator=(Entity&& other) noexcept {
        if (this != &other) {
            m_type = other.m_type;
            m_x = other.m_x;
            m_y = other.m_y;
            m_Xvelocity = other.m_Xvelocity;
            m_Yvelocity = other.m_Yvelocity;
            m_width = other.m_width;
            m_height = other.m_height;
            m_texture = std::move(other.m_texture);
        }
        return *this;
    }

    // Delete copy constructor and copy assignment operator
    Entity(const Entity&) = delete;
    Entity& operator=(const Entity&) = delete;

    // Destructor
    ~Entity() = default;

    // Handle Event for Entity
    void handleEvent(SDL_Event& event)
    {
        if(this->m_type != Type::PLAYER) return;
        switch(event.type)
        {
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {
                    case SDLK_UP:
                        m_Yvelocity = -10.0f;
                        break;
                    default:
                        break;
                }
                break;
            case SDL_KEYUP:
                switch(event.key.keysym.sym)
                {
                    case SDLK_UP:
                        m_Yvelocity = 5.0f;
                        break;
                    default:
                        break;
                }
                break;
            default:
                break;
        }
    }

    void render(const SDL_Rect& camera)
    {
        update();

        SDL_Rect dstRect = { static_cast<int>(m_x) - camera.x, static_cast<int>(m_y) - camera.y, static_cast<int>(m_width), static_cast<int>(m_height) };
        m_texture->render(dstRect.x, dstRect.y);
    }

    void update()
    {
        //if(this->m_type != Type::PLAYER) return;
        m_x += m_Xvelocity;
        m_y += m_Yvelocity;

        if(m_x >= SCREEN_WIDTH) {
            m_x = 0;
        }
        if(m_y >= SCREEN_HEIGHT) {
            m_y = 300;
            m_x = 0;
        }
    }

public:
    Type getType() const { return m_type; }

    float getX() const { return m_x; }
    float getY() const { return m_y; }
    void setX(float x) { m_x = x; }
    void setY(float y) { m_y = y; }

    float getWidth() const { return m_width; }
    float getHeight() const { return m_height; }
    void setWidth(float width) { m_width = width; }
    void setHeight(float height) { m_height = height; }

    float getXVelocity() const { return m_Xvelocity; }
    float getYVelocity() const { return m_Yvelocity; }
    void setXVelocity(float xVelocity) { m_Xvelocity = xVelocity; }
    void setYVelocity(float yVelocity) { m_Yvelocity = yVelocity; }

    bool isAlive() const { return b_alive; }
    void setAlive(bool alive) { b_alive = alive; }

private:
    std::unique_ptr<Texture> m_texture;         // Texture Class
    Type m_type;                                // Type of Entity

    float m_x, m_y;                         // Position
    float m_width, m_height;                // Size
    float m_Xvelocity, m_Yvelocity;         // Velocity

    // Status Flags
    bool b_alive = true;
};

#endif // ENTITY_HPP
