#pragma once

#ifndef GAME
#define GAME

#include <SDL2/SDL.h>
#include "Board.h"
#include <stdlib.h>
#include <chrono>
#include <thread>
#include <random>

const int DELAY = 17;

class Game
{
public:
    Game();
    ~Game();
    void Update();
    void GameLoop();
private:
    SDL_Window* m_window = NULL;
    SDL_Renderer* m_renderer = NULL;
    Board* m_board;
};

#endif //GAME