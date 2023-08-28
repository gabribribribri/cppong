#pragma once
#include <cstdint>

//enable DEBUGGING
#if true //<-- this
    #define DEBUG(x) x
#else
    #define DEBUG(x)
#endif

namespace Constants {

    //fps
    constexpr int FPS = 120;
    constexpr int TIMEOUT_SECONDS = 1;
    constexpr int TIMEOUT_FRAMES = TIMEOUT_SECONDS * FPS;

    //pi
    constexpr double PI { 3.14159 };

    //window
    template<typename T> constexpr T WINDOW_W { 1500 };
    template<typename T> constexpr T WINDOW_H { 500 };

    //ball
    constexpr double BALL_BASE_VELOCITY { 3 };
    constexpr double BALL_VELOCITY_GAIN_PER_FRAME { 0.0004 };
    constexpr double BALL_VELOCITY_LOST_PER_SCORE { 0.25   };
    template<typename T> constexpr T BALL_SIZE { 15 }; 

    //score_digit
    constexpr int DIGIT_PIXEL_SIZE = 15;

    //pad
    constexpr int PAD_BASE_VELOCITY { 3 };
    constexpr int PAD_W { 15 };
    constexpr int PAD_H { 75 };
}