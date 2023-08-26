#pragma once
#include <SDL2/SDL.h>
#include <array>
#include <vector>
#include "constants.hpp"

class ScoreDigit {

/*
    ! "R" in front of function names means Render
*/

public:
    static bool s_Show;
    const static std::array<SDL_Surface*, 10> IMAGES;
    ScoreDigit(int x, int y, int h ,int w)
        : m_Area ({
            x,
            y,
            w,
            h
        })
    {}

    void Render(SDL_Renderer* renderer, int score) {
        if (!s_Show) return;
    }

    

private:
    SDL_Rect m_Area;

    
} ;

const std::array<SDL_Surface*, 10> ScoreDigit::IMAGES =  {
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