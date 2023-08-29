#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include "../constants.hpp"


class Pad {

public:
    struct Line {
        int x1, y1, x2, y2;
    };
    SDL_Rect m_Area;
    Line m_UpLine, m_DownLine, m_FrontLine;
    inline static int s_SlowVel = Constants::PAD_SLOW_VELOCITY;
    inline static int s_FastVel = Constants::PAD_FAST_VELOCITY;

    Pad(int areaX, int frontLineX)
        : m_Area {
            areaX,
            Constants::WINDOW_H<int>/2-Constants::PAD_H/2,
            Constants::PAD_W,
            Constants::PAD_H
        },
        //initialize all lines X position
        m_UpLine   {areaX,0,areaX+Constants::PAD_W,0},
        m_DownLine {areaX,0,areaX+Constants::PAD_W,0},
        m_FrontLine {frontLineX, 0, frontLineX,0}
    {
        FixLines();
    }

    void SetPosMiddle() {
        m_Area.y = Constants::WINDOW_H<int>/2-m_Area.h/2;
        FixLines();
    }

    void GoUp(bool isFast, int vel) {
        if (m_Area.y < 0) return;
        Move(true, vel);
    }

    void GoDown(bool isFast, int vel) {
        if (m_Area.y+m_Area.h > Constants::WINDOW_H<int>) return;
        Move(false, vel);
    }

    void Render(SDL_Renderer* renderer) {
        SDL_RenderFillRect(renderer, &m_Area);
        DEBUG (
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            SDL_RenderDrawLine(renderer, m_DownLine.x1, m_DownLine.y1, m_DownLine.x2, m_DownLine.y2);
            SDL_RenderDrawLine(renderer, m_UpLine.x1, m_UpLine.y1, m_UpLine.x2, m_UpLine.y2);
            SDL_RenderDrawLine(renderer, m_FrontLine.x1, m_FrontLine.y1, m_FrontLine.x2, m_FrontLine.y2);
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); 
        )
    }

private:
    void Move(bool isUp, int vel) {
        m_Area.y += (isUp ? -1 : 1) * vel;
        FixLines();
    }

    //initialize all lines Y positions
    void FixLines() {
        m_UpLine.y1    = m_Area.y;
        m_UpLine.y2    = m_Area.y;
        m_DownLine.y1  = m_Area.y+m_Area.h;
        m_DownLine.y2  = m_Area.y+m_Area.h;
        m_FrontLine.y1 = m_Area.y;
        m_FrontLine.y2 = m_Area.y+m_Area.h;
    }
};