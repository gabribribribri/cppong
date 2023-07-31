#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include "ball.hpp"

class Game {

private:
    Ball m_Ball;

public:
    Game()
        : m_Ball(Ball())
    {}

    void Iteration(SDL_Renderer* renderer) {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        m_Ball.Iteration(renderer);
    }

};