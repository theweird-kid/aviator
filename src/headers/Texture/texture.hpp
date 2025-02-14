#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>

#include <iostream>
#include <memory>

class Texture
{
public:
    Texture(const std::string& path, int width, int height, SDL_Renderer* renderer)
        : m_texture(nullptr, SDL_DestroyTexture), m_width(width), m_height(height), m_renderer(renderer)
    {
        loadTexture(path);
    }

    ~Texture() = default;

    void setWidth(int width);
    void setHeight(int height);
    int width();
    int height();

    void render(int x, int y, SDL_Rect* clip = nullptr)
    {
        SDL_Rect renderQuad = {x, y, m_width, m_height};
        if (clip != nullptr)
        {
            renderQuad.w = clip->w;
            renderQuad.h = clip->h;
        }
        SDL_RenderCopy(m_renderer, m_texture.get(), clip, &renderQuad);
    }

private:
    void loadTexture(const std::string& path)
    {
        SDL_Surface* surface = SDL_LoadBMP(path.c_str());
        if (surface == nullptr)
        {
            SDL_Log("Unable to load image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
            exit(1);
        }

        m_texture.reset(SDL_CreateTextureFromSurface(m_renderer, surface));
        if (m_texture == nullptr)
        {
            SDL_Log("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
            exit(1);
        }

        SDL_FreeSurface(surface);
    }

private:
    std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)> m_texture;

    // Reference to Raw Renderer Instance pointer
    SDL_Renderer* m_renderer;

    int m_width;
    int m_height;
};

#endif // TEXTURE_HPP
