#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include "ball.hpp"
#include "constants.hpp"

enum class WindowBorderCol {
    Nothing = 0,
    Roof,
    Floor,
    Right,
    Left
};

class Game {

/*
    ! all collisions are handled in Game class
*/

public:
    Ball m_Ball;

    Game()
        : m_Ball(Ball())
    {}

    void EventlessGameLogic() {
        HandleCol();
        m_Ball.SetNewPos();
    }

    void Render(SDL_Renderer* renderer) {
        m_Ball.Render(renderer);
    }

private:
    void HandleCol() {
        WindowBorderCol ballWallCol = HandleBallWallCol(true);
    }

    WindowBorderCol HandleBallWallCol(bool doInvert) {
        if (m_Ball.GetX()+Constants::BALL_SIZE<double> > Constants::WINDOW_W<double>) {
            if (doInvert) m_Ball.InvertAngle(false);
            return WindowBorderCol::Right;
        }
        if (m_Ball.GetY()+Constants::BALL_SIZE<double> > Constants::WINDOW_H<double>) {
            if (doInvert) m_Ball.InvertAngle(true);
            return WindowBorderCol::Floor;
        }
        if (m_Ball.GetX() < 0) {
            if (doInvert) m_Ball.InvertAngle(false);
            return WindowBorderCol::Left;
        }
        if (m_Ball.GetY() < 0) {
            if (doInvert) m_Ball.InvertAngle(true);
            return WindowBorderCol::Roof;
        }
        return WindowBorderCol::Nothing;
    }

};