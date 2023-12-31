#pragma once
//C++ headers
#include <SDL2/SDL.h>
#include <SDL2/SDL_rect.h>
#include <tuple>
#include <unordered_map>
//Local headers
#include "ball.hpp"
#include "../constants.hpp"
#include "pad.hpp"
#include "score_digit.hpp"

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
    GameState m_GameState;

    Game()
        : //initializing all members
        m_GameState(GameState::Waiting),
        m_Timeout(Constants::TIMEOUT_FRAMES),
        m_Score({0, 0}),

        //game sprites
        m_Ball(Ball()),
        m_ScoreDigits{
            {Constants::WINDOW_W<int>/4-4*Constants::DIGIT_PIXEL_SIZE/2},
            {3*Constants::WINDOW_W<int>/4-4*Constants::DIGIT_PIXEL_SIZE/2}
        },
        m_Pads {
            {50, 50+Constants::PAD_W},
            {Constants::WINDOW_W<int>-50-Constants::PAD_W, Constants::WINDOW_W<int>-50-Constants::PAD_W}
        }
    {
        SetGameStateWaiting();
    }

    void Iteration(SDL_Renderer* renderer) {
        //?handle different things based on game state
        switch (m_GameState) {
            case GameState::Running:
                //handle all events
                CollectEvents();
                TreatEvents();
                //game logic
                EventlessGameLogic();
                break;

            case GameState::Waiting:
                if (m_Timeout-- <= 0) SetGameStateRunning();
                //only "closing" event
                CollectEvents();
                break;

            default:
                break;
        }
        
        //?RENDERING
        //background
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); //color black
        SDL_RenderClear(renderer);
        //foreground
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); //color white
        m_Ball.Render(renderer);
        m_ScoreDigits.first.Render(renderer, m_Score.first);
        m_ScoreDigits.second.Render(renderer, m_Score.second);
        m_Pads.first.Render(renderer);
        m_Pads.second.Render(renderer);
        //drawing everything to screen
        SDL_RenderPresent(renderer);
    }
   
private:

    int m_Timeout;
    std::pair<uint8_t, uint8_t> m_Score;
    std::unordered_map<int, bool> m_KeyInput;
    SDL_Event m_Events;

    //game sprites
    Ball m_Ball;
    std::pair<ScoreDigit, ScoreDigit> m_ScoreDigits;
    std::pair<Pad, Pad> m_Pads;

    void TreatEvents() {
        if (m_KeyInput[SDLK_z]) m_Pads.first.GoUp(Pad::s_SlowVel);
        if (m_KeyInput[SDLK_s]) m_Pads.first.GoDown(Pad::s_SlowVel);
        if (m_KeyInput[SDLK_o]) m_Pads.second.GoUp( Pad::s_SlowVel);
        if (m_KeyInput[SDLK_l]) m_Pads.second.GoDown(Pad::s_SlowVel);
        if (m_KeyInput[SDLK_e]) m_Pads.first.GoUp( Pad::s_FastVel);
        if (m_KeyInput[SDLK_d]) m_Pads.first.GoDown(Pad::s_FastVel);
        if (m_KeyInput[SDLK_i]) m_Pads.second.GoUp(Pad::s_FastVel);
        if (m_KeyInput[SDLK_k]) m_Pads.second.GoDown(Pad::s_FastVel);
        DEBUG (
            if (m_KeyInput[SDLK_c]) m_Ball.GetVelocity() -= 0.05;
            if (m_KeyInput[SDLK_v]) m_Ball.GetVelocity() += 0.05;
            if (m_KeyInput[SDLK_w]) m_Ball.AddAngle(-0.1);
            if (m_KeyInput[SDLK_x]) m_Ball.AddAngle(+0.1);
            if (m_KeyInput[SDLK_b]) {
                m_Ball.GetX() = Constants::WINDOW_W<double>/2+Constants::BALL_SIZE<double>/2;
                m_Ball.GetY() = Constants::WINDOW_H<double>/2+Constants::BALL_SIZE<double>/2;
            }
            if (m_KeyInput[SDLK_n]) {
                m_Score.first = 9;
                m_Score.second = 9;
            }
        )
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
    void EventlessGameLogic() {
        //handle collisions
        HandleBallWallCol();
        HandleBallPadCol();

        //ball moving
        m_Ball.SetNewPos();
        m_Ball.GetVelocity() += Constants::BALL_VELOCITY_GAIN_PER_FRAME;
    }

    void SetGameStateWaiting() {
        m_Ball.SetPosMiddle();
        m_Pads.first.SetPosMiddle();
        m_Pads.second.SetPosMiddle();
        m_Timeout = Constants::TIMEOUT_FRAMES;
        ScoreDigit::s_Show = true;
        m_GameState = GameState::Waiting;
    }

    void SetGameStateRunning() {
        ScoreDigit::s_Show = false;
        m_GameState = GameState::Running;
    }

    void Scoring(bool isLeft) {
        //?some debug
        DEBUG (
            std::cout
                << "[INFO] : Score["
                << static_cast<int>(m_Score.first)
                << ", "
                << static_cast<int>(m_Score.second)
                << "]; Ball Velocity["
                << m_Ball.GetVelocity()
                << "];\n";
        )

        uint8_t& score = (isLeft ? m_Score.first : m_Score.second);
        DEBUG(std::cout << "[INFO] : " << (isLeft ? "Left" : "Right") << " Scored !\n";)
        score++;
        if (score >= 10) {
            DEBUG(std::cout << "[INFO] : " << (isLeft ? "LEFT" : "RIGHT") << " WON !\n";)
            m_GameState = GameState::Exited;
            return;
        }
        m_Ball.RandomStartAngle(isLeft);
        SetGameStateWaiting();        
    }

    void HandleBallWallCol() {
        if (m_Ball.GetY()-Constants::BALL_SIZE<double>/2 < 0 or
            m_Ball.GetY()+Constants::BALL_SIZE<double>/2 > Constants::WINDOW_H<double>) {
                m_Ball.InvertAngle(true);
        } else if (m_Ball.GetX()-Constants::BALL_SIZE<double>/2 < 0) {
            Scoring(true);
        } else if (m_Ball.GetX()+Constants::BALL_SIZE<double>/2 > Constants::WINDOW_W<double>) {
            Scoring(false);
        }
    }

    void HandleOneBallPadCol(bool isLeft, const SDL_Rect& ballShape) {
        Pad& pad = (isLeft ? m_Pads.first : m_Pads.second);

        if (SDL_IntersectRectAndLine(&ballShape, &pad.m_UpLine.x1, &pad.m_UpLine.y1, &pad.m_UpLine.x2, &pad.m_UpLine.y2)) {
            DEBUG(std::cout << "[INFO] : m_Ball.OpposeAngle(isLeft);\n");
            m_Ball.OpposeAngleSecure(isLeft);
        } else if (SDL_IntersectRectAndLine(&ballShape, &pad.m_DownLine.x1, &pad.m_DownLine.y1, &pad.m_DownLine.x2, &pad.m_DownLine.y2)) {
            DEBUG(std::cout << "[INFO] : m_Ball.OpposeAngle(isLeft);\n");
            m_Ball.OpposeAngleSecure(isLeft);
        } else if (SDL_IntersectRectAndLine(&ballShape, &pad.m_FrontLine.x1, &pad.m_FrontLine.y1, &pad.m_FrontLine.x2, &pad.m_FrontLine.y2)) {
            DEBUG(std::cout << "[INFO] : m_Ball.InvertAngleSecure(false, isLeft);\n");
            m_Ball.InvertAngleSecure(false, isLeft);
        } else if (SDL_HasIntersection(&ballShape, &pad.m_Area)) {
            DEBUG(std::cout << "[INFO] : m_Ball.InvertAngleSecure(false, isLeft);\n");
            m_Ball.InvertAngleSecure(false, isLeft);
        }
    }

    void HandleBallPadCol() {
        SDL_Rect ballShape = m_Ball.GetShape();
        HandleOneBallPadCol(true, ballShape);
        HandleOneBallPadCol(false, ballShape);
    }
};