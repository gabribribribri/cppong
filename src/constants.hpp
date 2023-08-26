#pragma once
#include <cstdint>

#define DEBUG 1

namespace Constants {

    //fps
    constexpr int FPS = 120;
    constexpr int TIMEOUT_SECONDS = 1;

    //pi
    constexpr double PI { 3.14159 };

    //window
    template<typename T> constexpr T WINDOW_W { 800 };
    template<typename T> constexpr T WINDOW_H { 500 };

    //ball
    constexpr int32_t BALL_BASE_VELOCITY = 1;
    template<typename T> constexpr T BALL_SIZE { 20 }; 

}