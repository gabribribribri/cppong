#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include "ball.hpp"

class Game {

public:
    Ball m_Ball;

    Game()
        : m_Ball(Ball())
    {}

    void Render(SDL_Renderer* renderer) {
        m_Ball.Render(renderer);
    }

};