#pragma once
#include <SDL2/SDL.h>
#include "constants.hpp"
#include <optional>



class ScoreDigit {

/*
    ! "R" in front of function names means Render
*/

public:
    ScoreDigit(int x, int y)
        : m_X(x), m_Y(y)
    {}

    void Render(SDL_Renderer* renderer, int score) {

    }

private:
    int m_X, m_Y;

    void ROnePixel(SDL_Renderer* renderer, int offsetX, int offsetY) {
        SDL_Rect pixelShape {
            m_X+offsetX*Constants::DIGIT_PIXEL_SIZE,
            m_Y+offsetY*Constants::DIGIT_PIXEL_SIZE,
            Constants::DIGIT_PIXEL_SIZE,
            Constants::DIGIT_PIXEL_SIZE
        };

        SDL_RenderFillRect(renderer, &pixelShape);
    }    
} ;