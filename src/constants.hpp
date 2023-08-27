#pragma once
#include <cstdint>

#define DEBUG 1

namespace Constants {

    //fps
    constexpr int FPS = 120;
    constexpr int TIMEOUT_SECONDS = 1;
    constexpr int TIMEOUT_FRAMES = TIMEOUT_SECONDS * FPS;

    //pi
    constexpr double PI { 3.14159 };

    //window
    template<typename T> constexpr T WINDOW_W { 800 };
    template<typename T> constexpr T WINDOW_H { 500 };

    //ball
    constexpr double BALL_BASE_VELOCITY { 3 };
    template<typename T> constexpr T BALL_SIZE { 15 }; 

    //score_digit
    constexpr int DIGIT_PIXEL_SIZE = 15;

    //
}