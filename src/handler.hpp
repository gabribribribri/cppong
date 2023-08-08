#pragma once
#include <SDL2/SDL.h>
#include <unordered_map>
#include "constants.hpp"
#include "game.hpp"

class Handler {

/*
    ! all events are handled in Handler class
*/

private:
    SDL_Window* m_Window;
    SDL_Renderer* m_Renderer;
    SDL_Event m_Events;
    Game m_Game;
    bool m_Running;
    std::unordered_map<int, bool> m_KeyInput;

    void CollectEvents() {
        while (SDL_PollEvent(&m_Events)) {
            switch (m_Events.type) {
                case SDL_QUIT:
                    m_Running = false;
                    break;
                case SDL_KEYDOWN:
                    m_KeyInput[m_Events.key.keysym.sym] = true;
                    break;
                case SDL_KEYUP:
                    m_KeyInput[m_Events.key.keysym.sym] = false;
                    break;

            }
        }
    }

    void TreatEvents() {
        if (m_KeyInput[SDLK_c]) m_Game.m_Ball.InvertAngle(false);
        if (m_KeyInput[SDLK_v]) m_Game.m_Ball.InvertAngle(true);
        if (m_KeyInput[SDLK_w]) m_Game.m_Ball.AddAngle(-0.1);
        if (m_KeyInput[SDLK_x]) m_Game.m_Ball.AddAngle(+0.1);
    }

    void Iteration() {
        //Handle Events
        CollectEvents();
        TreatEvents();

        //Eventless Game Logic
        m_Game.EventlessGameLogic();

        //Render Everything
        SDL_SetRenderDrawColor(m_Renderer, 0, 0, 0, 255);
        SDL_RenderClear(m_Renderer);
        SDL_SetRenderDrawColor(m_Renderer, 255, 255, 255, 255);
        m_Game.Render(m_Renderer);
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