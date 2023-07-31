#pragma once
#include "constants.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>

class Ball {

private:
    SDL_Rect m_Shape;
    float m_Angle;
    float m_Velocity;

    void SetNewPos() {
        m_Shape.x += 1;
    }

public:
    Ball()
        : m_Shape(SDL_Rect{
            Constants::WINDOW_W/2+Constants::BALL_SIZE/2,
            Constants::WINDOW_H/2+Constants::BALL_SIZE/2,
            Constants::BALL_SIZE,
            Constants::BALL_SIZE
        }),
        m_Angle(Constants::PI/2),
        m_Velocity(Constants::BALL_BASE_VELOCITY)
    {}

    void Iteration(SDL_Renderer* renderer) {
        SDL_RenderFillRect(renderer, &m_Shape);
        SetNewPos();
    }

};