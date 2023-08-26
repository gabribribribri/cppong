#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <array>
#include <vector>
#include "constants.hpp"
#include <iostream>

class ScoreDigit {


public:
    inline static bool s_Show = false;

    ScoreDigit(int x, int y, int w ,int h)
        : m_Area ({
            x,
            y,
            w,
            h
        })
    {}

    void Render(SDL_Renderer* renderer, uint8_t score) {
        if (!s_Show) return;

        if (score > 9) {
            std::cout << "[ERROR] : Score must be less than 9\n";
            std::exit(-1);
        }

        SDL_Texture* digitTexture = SDL_CreateTextureFromSurface(renderer, DIGITS_SURFACES[score]);
        SDL_RenderCopy(renderer, digitTexture, NULL, &m_Area);
    }

private:
    SDL_Rect m_Area;
    inline const static std::array<SDL_Surface*, 10> DIGITS_SURFACES  =  {
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
};