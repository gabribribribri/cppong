#pragma once
#include <SDL2/SDL.h>
#include "ball.hpp"
#include "constants.hpp"
#include <SDL2/SDL_render.h>
#include <tuple>
#include <unordered_map>
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
    int m_Timeout;
    std::pair<uint8_t, uint8_t> m_Score;
    std::unordered_map<int, bool> m_KeyInput;
    SDL_Event m_Events;

    //game sprites
    Ball m_Ball;
    std::pair<ScoreDigit, ScoreDigit> m_ScoreDigits;

    Game()
        : //initializing all members
        m_GameState(GameState::Waiting),
        m_Timeout(Constants::TIMEOUT_FRAMES),
        m_Score({0, 0}),

        //game sprites
        m_Ball(Ball()),
        m_ScoreDigits({
            {
                Constants::WINDOW_W<int>/4-4*Constants::DIGIT_PIXEL_SIZE/2,
                Constants::WINDOW_H<int>/9,
                4*Constants::DIGIT_PIXEL_SIZE,
                5*Constants::DIGIT_PIXEL_SIZE,
            },
            {
                3*Constants::WINDOW_W<int>/4-4*Constants::DIGIT_PIXEL_SIZE/2,
                Constants::WINDOW_H<int>/9,
                4*Constants::DIGIT_PIXEL_SIZE,
                5*Constants::DIGIT_PIXEL_SIZE,
            }
        })
    {
        SetGameStateWaiting();
    }

    void Iteration(SDL_Renderer* renderer) {
        switch (m_GameState) {
            case GameState::Running:
                ScoreDigit::s_Show = false;
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
        
        //background
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); //color black
        SDL_RenderClear(renderer);
        //foreground
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); //color white
        m_Ball.Render(renderer);
        m_ScoreDigits.first.Render(renderer, m_Score.first);
        m_ScoreDigits.second.Render(renderer, m_Score.second);
        //drawing everything to screen
        SDL_RenderPresent(renderer);
    }

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

    void HandleCol() {
        HandleBallWallCol();
    }

    void SetGameStateWaiting() {
        m_Ball.SetPosMiddle();
        m_Timeout = Constants::TIMEOUT_FRAMES;
        ScoreDigit::s_Show = true;
        m_GameState = GameState::Waiting;
    }

    void SetGameStateRunning() {
        ScoreDigit::s_Show = false;
        m_GameState = GameState::Running;
    }

    void HandleBallWallCol() {
        if (m_Ball.GetY()-Constants::BALL_SIZE<double>/2 < 0 or
            m_Ball.GetY()+Constants::BALL_SIZE<double>/2 > Constants::WINDOW_H<double>)
            m_Ball.InvertAngle(true);


        else if (m_Ball.GetX()-Constants::BALL_SIZE<double>/2 < 0) {
            #if DEBUG == 1
                    std::cout << "Left Scored !\n";
            #endif
            m_Score.first++;
            m_Ball.SetAngle(Constants::PI/2);
            SetGameStateWaiting();
        }

        else if (m_Ball.GetX()+Constants::BALL_SIZE<double>/2 > Constants::WINDOW_W<double>) {
            #if DEBUG == 1
                    std::cout << "Right Scored !\n";
            #endif
            m_Score.second++;
            m_Ball.SetAngle(3*Constants::PI/2);
            SetGameStateWaiting();
        }
    }
};