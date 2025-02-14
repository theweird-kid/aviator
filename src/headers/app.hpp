#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <imgui/imgui.h>
#include <imgui/imgui_impl_sdl2.h>
#include <imgui/imgui_impl_sdlrenderer2.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>

#include "./Game/game.hpp"
#include "constants.hpp"

#include <memory>

class Application
{
public:
    Application()
        : m_window(nullptr, SDL_DestroyWindow), m_renderer(nullptr, SDL_DestroyRenderer)
    {
        if (SDL_Init(SDL_INIT_VIDEO) != 0) {
            SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
            exit(1);
        }

        m_window.reset(SDL_CreateWindow("Aviator", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN));
        if (m_window == nullptr) {
            SDL_Log("Unable to create window: %s", SDL_GetError());
            exit(1);
        }

        m_renderer.reset(SDL_CreateRenderer(m_window.get(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC));
        if (m_renderer == nullptr) {
            SDL_Log("Unable to create renderer: %s", SDL_GetError());
            exit(1);
        }

        m_game = std::make_unique<Game>(m_renderer.get());

        init();
    }
    ~Application()
    {
        // Cleanup ImGui
        ImGui_ImplSDLRenderer2_Shutdown();
        ImGui_ImplSDL2_Shutdown();
        ImGui::DestroyContext();
    };

    void run()
    {
        b_running = true;
        while(b_running) {
            // Handling Frame Rates
            frameStart = SDL_GetTicks();

            handleEvents();
            update();
            render();

            frameTime = SDL_GetTicks() - frameStart;
            if(frameDelay > frameTime) {
                SDL_Delay(frameDelay - frameTime);
            }
        }
    }

private:
    void init()
    {
        SDL_SetRenderDrawColor(m_renderer.get(), 0, 0, 0, 255);
        SDL_RenderClear(m_renderer.get());
        SDL_RenderPresent(m_renderer.get());

        // Initialize ImGui
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        ImGui::StyleColorsDark();

        ImGui_ImplSDL2_InitForSDLRenderer(m_window.get(), m_renderer.get());
        ImGui_ImplSDLRenderer2_Init(m_renderer.get());

        // Testing Entities
        m_game->init();
    }

    void handleEvents()
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            ImGui_ImplSDL2_ProcessEvent(&event);
            // SDL KEYDOWN event
            if(event.type == SDL_KEYDOWN) {
                switch(event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:                   // Quit
                        b_running = false;
                        break;
                    default:
                        break;
                }
            }
            // SDL QUIT event
            if (event.type == SDL_QUIT) {
                b_running = false;
            }

            m_game->handleEvents(event);
        }
    }

    void update()
    {
    }

    void render()
    {
        // Start the ImGui frame
        ImGui_ImplSDLRenderer2_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();

        // Create a window called "Frame Rate"
        ImGui::Begin("Frame Rate");
        ImGui::Text("Average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::End();

        // Rendering
        ImGui::Render();
        SDL_SetRenderDrawColor(m_renderer.get(), 0, 0, 0, 255);
        SDL_RenderClear(m_renderer.get());

        m_game->render();

        ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(), m_renderer.get());
        SDL_RenderPresent(m_renderer.get());
    }

private:
    std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> m_window;         // SDL window Instance
    std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> m_renderer;   // SDL renderer Instance
    std::unique_ptr<Game> m_game;                                               // Game Instance

    // Status Flags
    bool b_running = false;

    // Frame Rate Control
    const int FPS = 60;
    const int frameDelay = 1000 / FPS;
    uint32_t frameStart;
    int frameTime;
};

#endif // APPLICATION_HPP
