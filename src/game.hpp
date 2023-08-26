#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include "ball.hpp"
#include <cstdint>
#include <tuple>
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
    int m_Timeout;
    std::pair<uint8_t, uint8_t> m_Score;

    Game()
        : m_Ball(Ball()), m_Timeout(0), m_Score({0, 0})
    {}

    void EventlessGameLogic() {
        #if DEBUG
            std::cout
                << "Score : "
                << static_cast<int>(m_Score.first)
                << ", "
                << static_cast<int>(m_Score.second)
                << "\n";
        #endif

        HandleCol();
        m_Ball.SetNewPos();
    }

    void Render(SDL_Renderer* renderer) {
        m_Ball.Render(renderer);
    }

private:
    void HandleCol() {
        switch (HandleBallWallCol(true)) {
            
            case WindowBorderCol::Left:
                #if DEBUG == 1
                    std::cout << "Left Scored ! ";
                #endif
                m_Ball.SetPosMiddle();
                m_Ball.SetAngle(Constants::PI/2);
                m_Timeout = Constants::TIMEOUT_SECONDS*Constants::FPS;
                m_Score.first++;
                break;
            case WindowBorderCol::Right:
                #if DEBUG == 1
                    std::cout << "Right Scored ! ";
                #endif
                m_Ball.SetPosMiddle();
                m_Ball.SetAngle(3*Constants::PI/2);
                m_Timeout = Constants::TIMEOUT_SECONDS*Constants::FPS;
                m_Score.second++;
                break;

            default:
                break;
        }
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