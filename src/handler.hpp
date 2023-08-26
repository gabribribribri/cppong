#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_keycode.h>
#include "constants.hpp"
#include "game.hpp"
#include "score_digit.hpp"

class Handler {

/*
    ! events and collisions are all handled in Game class (m_Game member)
*/

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
            Constants::WINDOW_W<int>,
            Constants::WINDOW_H<int>,
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
        while (m_Game.m_GameState != GameState::Exited) {
            m_Game.Iteration(m_Renderer);
            SDL_Delay(1000/Constants::FPS);
        }
    }

};