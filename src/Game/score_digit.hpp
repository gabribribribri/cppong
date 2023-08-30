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

    ScoreDigit(int x)
        : m_Area {
            x,
            Constants::WINDOW_H<int>/9,
            4*Constants::DIGIT_PIXEL_SIZE,
            5*Constants::DIGIT_PIXEL_SIZE,
        }
    {}

    void Render(SDL_Renderer* renderer, uint8_t score) {
        if (!s_Show) return;

        if (!s_DigitsTextures[score])
            s_DigitsTextures[score] = SDL_CreateTextureFromSurface(renderer, s_DigitsSurfaces[score]);

        SDL_RenderCopy(renderer, s_DigitsTextures[score], nullptr, &m_Area);
    }

private:
    SDL_Rect m_Area;

    inline static std::array<SDL_Texture*, 10> s_DigitsTextures {};
    inline const static std::array<SDL_Surface*, 10> s_DigitsSurfaces {
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