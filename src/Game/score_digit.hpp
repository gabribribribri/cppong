#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <array>
#include <vector>
#include "../constants.hpp"
#include <iostream>

class ScoreDigit {

public:
    inline static bool s_Show = false;

    ScoreDigit(int x, int y)
        : m_Area ({
            x,
            y,
            4*Constants::DIGIT_PIXEL_SIZE,
            5*Constants::DIGIT_PIXEL_SIZE,
        })
    {}

    void Render(SDL_Renderer* renderer, uint8_t score) {
        if (!s_Show) return;

        if (!DIGITS_TEXTURES[score])
            DIGITS_TEXTURES[score] = SDL_CreateTextureFromSurface(renderer, DIGITS_SURFACES[score]);
            
        SDL_RenderCopy(renderer, DIGITS_TEXTURES[score], nullptr, &m_Area);
    }

private:
    SDL_Rect m_Area;

    inline static std::array<SDL_Texture*, 10> DIGITS_TEXTURES {};
    inline const static std::array<SDL_Surface*, 10> DIGITS_SURFACES {
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