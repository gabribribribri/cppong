#pragma once
#include <SDL2/SDL.h>
#include "constants.hpp"
#include "game.hpp"

class Handler {

private:
    SDL_Window* m_Window;
    SDL_Renderer* m_Renderer;
    SDL_Event m_Events;
    Game m_Game;
    bool m_Running;

    void HandleEvents() {
        while (SDL_PollEvent(&m_Events)) {
            switch (m_Events.type) {
                case SDL_QUIT:
                    m_Running = false;
            }
        }
    }

    void Iteration() {
        HandleEvents();
        
        SDL_SetRenderDrawColor(m_Renderer, 0, 0, 0, 255);
        SDL_RenderClear(m_Renderer);

        m_Game.Iteration(m_Renderer);

        SDL_RenderPresent(m_Renderer);

    }


public:
    Handler()
        : m_Game(Game()),
        m_Running(true)
    {
        SDL_Init(SDL_INIT_VIDEO);

        m_Window = SDL_CreateWindow(
            "Pong",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            Constants::WINDOW_W,
            Constants::WINDOW_H,
            SDL_WINDOW_SHOWN
        );

        m_Renderer = SDL_CreateRenderer(
            m_Window, 
            -1, 
            SDL_RENDERER_ACCELERATED
        );
    }

    ~Handler() {
        SDL_DestroyRenderer(m_Renderer);
        SDL_DestroyWindow(m_Window);
        SDL_Quit();
    }

    void Run() {
        while (m_Running) {
            Iteration();
            SDL_Delay(1000/Constants::FPS);
        }
    }

};