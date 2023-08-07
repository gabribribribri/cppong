#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include "ball.hpp"
#include "constants.hpp"

enum class WindowBorderCollision {
    Nothing = 0,
    Roof,
    Floor,
    Right,
    Left
};

class Game {

public:
    Ball m_Ball;

    Game()
        : m_Ball(Ball())
    {}

    void Render(SDL_Renderer* renderer) {
        m_Ball.Render(renderer);
    }

private:
    void HandleCollisions() {
        switch (BallWallCollisions()) {
            case WindowBorderCollision::Nothing:
                break;
            case WindowBorderCollision::Left:
        }
    }

    WindowBorderCollision BallWallCollisions() {
        if (m_Ball.getX()+Constants::BALL_SIZE > Constants::WINDOW_W) return WindowBorderCollision::Right;
        if (m_Ball.getY()+Constants::BALL_SIZE > Constants::WINDOW_H) return WindowBorderCollision::Floor;
        if (m_Ball.getX() < 0) return WindowBorderCollision::Left;
        if (m_Ball.getY() < 0) return WindowBorderCollision::Roof;
        return WindowBorderCollision::Nothing;
    }

};