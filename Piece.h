#pragma once

#ifndef PIECE
#define PIECE

#include "Move.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Move.h"

const int NONE = 0;
const int KING = 1;
const int PAWN = 2;
const int KNIGHT = 3;
const int BISHOP = 4;
const int ROOK = 5;
const int QUEEN = 6;
const int WHITE = 8;
const int BLACK = 16;

class Piece
{
public:
    Piece();
    Piece(int);
    Piece(int, SDL_Rect*);
    Piece(int, SDL_Rect*, int);
    ~Piece();
    void setType(int);
    int getColor();
    int getType();
    void setClip(SDL_Rect*);
    SDL_Rect* getClip();
    bool getHasMoved();
    void setHasMoved();
    int getPos();
    void setPos(int);

private:
    int m_color = 0;
    int m_type = 0;
    bool m_has_moved = false;
    int m_pos;
    SDL_Rect* m_clip = NULL;
};

#endif //PIECE
