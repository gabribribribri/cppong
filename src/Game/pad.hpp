#pragma once
#include <SDL2/SDL.h>
#include "../constants.hpp"

class Pad {

public:
    SDL_Rect m_Area;
    int m_Vel;

    Pad(int x)
        : m_Area {
            x,
            Constants::WINDOW_H<int>/2-Constants::PAD_H/2,
            Constants::PAD_W,
            Constants::PAD_H
        },
        m_Vel(Constants::PAD_BASE_VELOCITY)
    {}

    void SetPosMiddle() {
        m_Area.y = Constants::WINDOW_H<int>/2-Constants::PAD_H/2;
    }

    void GoUp() {
        Move(true);
    }

    void GoDown() {
        Move(false);
    }

    void Render(SDL_Renderer* renderer) {
        SDL_RenderFillRect(renderer, &m_Area);
    }

private:
    void Move(bool isUp) {
        m_Area.y += (isUp ? -1 : 1) * m_Vel;
    }
};