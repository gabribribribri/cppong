#pragma once
#include "constants.hpp"
#include <SDL2/SDL.h>
#include <cmath>
#include <iostream>


class Ball {

/*
    ! do not handle events or collisions
*/

private:
    double m_X, m_Y;
    double m_Angle;
    double m_Velocity;

    

    void FixAngle() {
        if (std::abs(m_Angle) > 2*Constants::PI)
            m_Angle = std::fmod(m_Angle, 2*Constants::PI);
        if (m_Angle < 0)
            m_Angle += 2*Constants::PI;
    }

public:
    const double& GetX()        const { return m_X;        }
    const double& GetY()        const { return m_Y;        }
    const double& GetAngle()    const { return m_Angle;    }
    const double& GetVelocity() const { return m_Velocity; }
    double& GetX()                    { return m_X;        }
    double& GetY()                    { return m_Y;        }
    double& GetAngle()                { return m_Angle;    }
    double& GetVelocity()             { return m_Velocity; }

    Ball() :
        m_X(Constants::WINDOW_W<double>/2+Constants::BALL_SIZE<double>/2),
        m_Y(Constants::WINDOW_H<double>/2+Constants::BALL_SIZE<double>/2),
        m_Angle(Constants::PI/2),
        m_Velocity(Constants::BALL_BASE_VELOCITY)
    {}

    void SetAngle(double newValue) {
        m_Angle = newValue;
        FixAngle();
    }

    void AddAngle(double toAdd) {
        m_Angle += toAdd;
        FixAngle();
    }

    void SetNewPos() {
        int nQ = static_cast<int>( m_Angle / (Constants::PI / 2) );
        double useAngle = std::fmod(m_Angle, Constants::PI / 2);

        double plusX = m_Velocity * std::cos(useAngle);
        double plusY = m_Velocity * std::sin(useAngle);

        m_X += (nQ == 0 or nQ == 1 ? 1 : -1) * (nQ == 1 or nQ == 3 ? plusX : plusY);
        m_Y += (nQ == 1 or nQ == 2 ? 1 : -1) * (nQ == 0 or nQ == 2 ? plusX : plusY);

        //std::cout << m_Angle << "  " << useAngle << "  " << nQ << std::endl;
    }

    void SetPosMiddle() {
        m_X = Constants::WINDOW_W<double>/2+Constants::BALL_SIZE<double>/2;
        m_Y = Constants::WINDOW_H<double>/2+Constants::BALL_SIZE<double>/2;
    }

    void InvertAngle(bool vertically /*if not vertically then invert horizontally*/) {
        /* if (vertically)
            SetAngle(Constants::PI - GetAngle());
        else
            SetAngle(2*Constants::PI - GetAngle()); */
        SetAngle((!vertically+1) * Constants::PI - GetAngle());
    }

    void Render(SDL_Renderer* renderer) {
        SDL_Rect ballShape{
            static_cast<int>(m_X),
            static_cast<int>(m_Y),
            Constants::BALL_SIZE<int>,
            Constants::BALL_SIZE<int>,
        };
        SDL_RenderFillRect(renderer, &ballShape);
    }

};