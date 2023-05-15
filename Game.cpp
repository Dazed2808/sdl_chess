#include "Game.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mouse.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <chrono>
#include <cstddef>
#include <thread>

Game::Game()
{
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);
    m_window = SDL_CreateWindow("GChess", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 768, 768,
        SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI);
    m_renderer = SDL_CreateRenderer(m_window, -1, 0);
    m_board = new Board(m_renderer);
    m_board -> drawBoard();
    m_board -> loadSprites();
    SDL_RenderPresent(m_renderer);
}

Game::~Game()
{
    SDL_DestroyWindow(m_window);
    SDL_DestroyRenderer(m_renderer);
    IMG_Quit();
    SDL_Quit();
    delete m_board;
}

void Game::Update()
{
    int mouseX, mouseY;
    SDL_Event e;
    while (SDL_PollEvent(&e) != 0) 
    {
        if(e.type == SDL_QUIT)
        {
            exit(0);
        }
        if(e.type == SDL_MOUSEBUTTONDOWN)
        {
            if (e.button.button == SDL_BUTTON_LEFT) 
            {
                SDL_GetMouseState(&mouseX, &mouseY);
                m_board -> playerMove(mouseX, mouseY);
                m_board -> updateBoard();
            }
        }
    }
}

void Game::GameLoop()
{
    std::chrono::time_point<std::chrono::system_clock> t = std::chrono::system_clock::now();
    m_board -> setupBoard();
    m_board -> genarateMoves();
    while (true) 
    {
        Update();
        t += std::chrono::milliseconds(DELAY);
        std::this_thread::sleep_until(t);
    }
}