#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <array>
#include <vector>
#include "constants.hpp"
#include <iostream>

class ScoreDigit {

/*
    ! "R" in front of function names means Render
*/

public:
    static bool s_Show;

    ScoreDigit(int x, int y, int w ,int h)
        : m_Area ({
            x,
            y,
            w,
            h
        })
    {}

    void Render(SDL_Renderer* renderer, int score) {
        if (!s_Show) return;

        if (score < 0 or score > 9) {
            std::cout << "[ERROR] : Score must be between 0 and 9\n";
            std::exit(-1);
        }

        SDL_Texture* digitTexture = SDL_CreateTextureFromSurface(renderer, DIGITS_SURFACES[score]);
        SDL_RenderCopy(renderer, digitTexture, NULL, &m_Area);
    }

private:
    SDL_Rect m_Area;
    const static std::array<SDL_Surface*, 10> DIGITS_SURFACES;
} ;

const std::array<SDL_Surface*, 10> ScoreDigit::DIGITS_SURFACES =  {
    SDL_LoadBMP("digits/zero.bmp"),
    SDL_LoadBMP("digits/one.bmp"),
    SDL_LoadBMP("digits/two.bmp"),
    SDL_LoadBMP("digits/three.bmp"),
    SDL_LoadBMP("digits/four.bmp"),
    SDL_LoadBMP("digits/five.bmp"),
    SDL_LoadBMP("digits/six.bmp"),
    SDL_LoadBMP("digits/seven.bmp"),
    SDL_LoadBMP("digits/eight.bmp"),
    SDL_LoadBMP("digits/nine.bmp")
};

bool ScoreDigit::s_Show = false;