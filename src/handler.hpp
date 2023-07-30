#pragma once
#include "constants.hpp"
#include <SDL2/SDL.h>
#include "game.hpp"

class Handler {

private:
    SDL_Window* m_Window;
    SDL_Renderer* m_Renderer;
    Game m_Game;


public:
    Handler()
        : m_Game(Game())
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

    void Run() {

    }

};