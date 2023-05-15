#pragma once
#ifndef BOARD
#define BOARD

#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include "Piece.h"
#include "Move.h"
#include <array>
#include <vector>
#include <string>
#include <iostream>

const int SQUARE_SIZE = 96;

const int SPITE_X_OFF_SET = 213;
const int SPITE_Y_OFF_SET = 213;

const int LIGHT_COL[3] = {245, 210, 175};
const int DARK_COL[3] = {140, 90, 70};

const int KNIGHT_OFF_SET[8] = {-17, 17, -10, 10, -6, 6, -15, 15};
const int KING_OFF_SET[8] = {-7, -8, -9, -1, -1, 7, 8, 9};

const std::string STARTING_FEN = "rnbqknr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w";

class Board
{
public:
    Board(SDL_Renderer*);
    ~Board();
    void drawBoard();
    void drawSquare(int, int, int, int, int);
    void drawSquareAtPos(int, int);
    void loadSprites();
    void drawSprites(int, int, SDL_Rect*);
    void setupBoard();
    void updateBoard();
    void setClipFromType(Piece*);
    void convertFEN(std::string);
    void playerMove(int, int);
    void moveToEmpty();
    void moveToCapture();
    void shortCastle();
    void longCastle();
    void pawnPromote();
    void enPassant();
    void switchTurn();
    Piece* pieceFromPos(int);

    void genarateMoves();
    void genarateAttackedPosition();
    int validateMove();
    void pawnMove(Piece*);
    void bishopMove(Piece*);
    void rookMove(Piece*);
    void queenMove(Piece*);
    void kingMove(Piece*);
    void knightMove(Piece*);
    void castleCheck(Piece*);
    void offSetMove(Piece*, const int[8]);
    void diagMove(Piece*);
    void orthoMove(Piece*);
private:
    SDL_Renderer* m_renderer;
    SDL_Surface* m_pieces_texture = IMG_Load("pieces.png");
    SDL_Rect* m_sprite_clips[12];
    Piece* m_piece_to_move = nullptr;
    int m_turn = WHITE;
    int m_prev_pos;
    int m_target_pos;
    int m_enpassant;
    int m_setup;
    float m_move = 1;
    std::vector<int> m_squares_to_update;
    std::vector<Move*> m_moves;
    std::vector<Piece*> m_pieces;
    std::vector<int> m_attacked_pos;
};


#endif //BOARD
