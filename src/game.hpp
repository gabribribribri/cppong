#pragma once
#include <SDL2/SDL.h>
#include "ball.hpp"
#include "constants.hpp"
#include <SDL2/SDL_render.h>
#include <tuple>
#include <unordered_map>
#include "score_digit.hpp"

enum class WindowBorderCol {
    Nothing = 0,
    Roof,
    Floor,
    Right,
    Left
};

enum class GameState {
    Running,
    Waiting,
    Exited
};

class Game {

/*
    ! all collisions are handled in Game class
*/

public:

    Ball m_Ball;
    std::pair<ScoreDigit, ScoreDigit> m_ScoreDigits;
    
    GameState m_GameState;
    int m_Timeout;
    std::pair<uint8_t, uint8_t> m_Score;
    std::unordered_map<int, bool> m_KeyInput;
    SDL_Event m_Events;

    void Iteration(SDL_Renderer* renderer) {
        if (m_Timeout-- <= 0) {

            ScoreDigit::s_Show = false;
            
            //Handle Events
            CollectEvents();
            TreatEvents();

            //Eventless Game Logic
            EventlessGameLogic();
        } else {
            ScoreDigit::s_Show = true;
        }

        //Render Everything
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        Render(renderer);
        SDL_RenderPresent(renderer);

    }

    Game()
        : m_Ball(Ball()),
        m_Timeout(0),
        m_Score({0, 0}),
        m_ScoreDigits({
            {
                200-4*Constants::DIGIT_PIXEL_SIZE/2,
                75,
                4*Constants::DIGIT_PIXEL_SIZE,
                5*Constants::DIGIT_PIXEL_SIZE,
            },
            {
                600-4*Constants::DIGIT_PIXEL_SIZE/2,
                75,
                4*Constants::DIGIT_PIXEL_SIZE,
                5*Constants::DIGIT_PIXEL_SIZE,
            }
        })
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
        m_ScoreDigits.first.Render(renderer, m_Score.first);
        m_ScoreDigits.second.Render(renderer, m_Score.second);
    }

private:
    void TreatEvents() {
        #if DEBUG == 1
            if (m_KeyInput[SDLK_c]) m_Ball.InvertAngle(false);
            if (m_KeyInput[SDLK_v]) m_Ball.InvertAngle(true);
            if (m_KeyInput[SDLK_w]) m_Ball.AddAngle(-0.1);
            if (m_KeyInput[SDLK_x]) m_Ball.AddAngle(+0.1);
            if (m_KeyInput[SDLK_b]) {
                m_Ball.GetX() = Constants::WINDOW_W<double>/2+Constants::BALL_SIZE<double>/2;
                m_Ball.GetY() = Constants::WINDOW_H<double>/2+Constants::BALL_SIZE<double>/2;
            }
        #endif
    }

    void CollectEvents() {
        while (SDL_PollEvent(&m_Events)) {
            switch (m_Events.type) {
                case SDL_QUIT:
                    m_GameState = GameState::Exited;
                    break;
                case SDL_KEYDOWN:
                    m_KeyInput[m_Events.key.keysym.sym] = true;
                    break;
                case SDL_KEYUP:
                    m_KeyInput[m_Events.key.keysym.sym] = false;
                    break;

            }
        }
    }

    void ResetGameStat(WindowBorderCol col) {
        m_Ball.SetPosMiddle();
        m_Timeout = Constants::TIMEOUT_SECONDS*Constants::FPS;
        if (col == WindowBorderCol::Left) {
            m_Score.first++;
            m_Ball.SetAngle(Constants::PI/2);
        } else {
            m_Score.second++;
            m_Ball.SetAngle(3*Constants::PI/2);
        }

    }

    void HandleCol() {
        switch (HandleBallWallCol(true)) {
            
            case WindowBorderCol::Left:
                #if DEBUG == 1
                    std::cout << "Left Scored !\n";
                #endif
                ResetGameStat(WindowBorderCol::Left);
                break;
            
            case WindowBorderCol::Right:
                #if DEBUG == 1
                    std::cout << "Right Scored !\n";
                #endif
                ResetGameStat(WindowBorderCol::Right);
                break;

            default:
                break;
        }
    }

    WindowBorderCol HandleBallWallCol(bool doInvert) {
        if (m_Ball.GetX()+Constants::BALL_SIZE<double>/2 > Constants::WINDOW_W<double>) {
            if (doInvert) m_Ball.InvertAngle(false);
            return WindowBorderCol::Right;
        }
        if (m_Ball.GetY()+Constants::BALL_SIZE<double>/2 > Constants::WINDOW_H<double>) {
            if (doInvert) m_Ball.InvertAngle(true);
            return WindowBorderCol::Floor;
        }
        if (m_Ball.GetX()-Constants::BALL_SIZE<double>/2 < 0) {
            if (doInvert) m_Ball.InvertAngle(false);
            return WindowBorderCol::Left;
        }
        if (m_Ball.GetY()-Constants::BALL_SIZE<double>/2 < 0) {
            if (doInvert) m_Ball.InvertAngle(true);
            return WindowBorderCol::Roof;
        }
        return WindowBorderCol::Nothing;
    }

};