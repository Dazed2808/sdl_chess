#include "Board.h"
#include "Piece.h"
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <cmath>
#include <iostream>
#include <string>

Board::Board(SDL_Renderer* renderer)
{
    for (int i = 0; i < 12; i++) 
    {
        m_sprite_clips[i] = new SDL_Rect();
    }
    convertFEN(STARTING_FEN);
    m_renderer = renderer;
}

Board::~Board()
{
    for (int i = 0; i < 12; i++) 
    {
        m_pieces.clear();
        m_moves.clear();
        m_squares_to_update.clear();
    }
}

void Board::drawBoard()
{
    for (int rank = 0; rank < 8; rank++) 
    {
        for (int file = 0; file < 8; file++) 
        {
            if((file + rank) % 2 == 0) 
            {
                drawSquare(LIGHT_COL[0], LIGHT_COL[1], LIGHT_COL[2], file, rank);
            }
            else 
            {
                drawSquare(DARK_COL[0], DARK_COL[1], DARK_COL[2], file, rank);
            }
        }
    }
}

void Board::drawSquare(int r, int g, int b, int x, int y)
{
    SDL_Rect rect;
    rect.x = x * SQUARE_SIZE;
    rect.y = y * SQUARE_SIZE;
    rect.w = SQUARE_SIZE;
    rect.h = SQUARE_SIZE;
    SDL_SetRenderDrawColor(m_renderer, r, g, b, 255);
    SDL_RenderFillRect(m_renderer, &rect);
}

void Board::drawSquareAtPos(int x, int y)
{
    if((x + y) % 2 == 0)
    {
        drawSquare(LIGHT_COL[0], LIGHT_COL[1], LIGHT_COL[2], x, y);
    }
    else
    {
        drawSquare(DARK_COL[0], DARK_COL[1], DARK_COL[2], x, y);
    }
}

void Board::loadSprites()
{
    for (int i = 0; i < 12; i++) 
    {
        if(i >= 6)
        {
            m_sprite_clips[i]->x = (i - 6) * SPITE_X_OFF_SET;
            m_sprite_clips[i]->y = SPITE_Y_OFF_SET;
        }
        else 
        {
            m_sprite_clips[i]->x = i * SPITE_X_OFF_SET;
            m_sprite_clips[i]->y = 0;
        }
        m_sprite_clips[i]->w = SPITE_X_OFF_SET;
        m_sprite_clips[i]->h = SPITE_Y_OFF_SET;
    }
}

void Board::drawSprites(int x, int y, SDL_Rect* clip)
{
    SDL_Rect render_rect = {x, y, SQUARE_SIZE, SQUARE_SIZE};
    SDL_Texture* new_texture = SDL_CreateTextureFromSurface(m_renderer, m_pieces_texture);
    SDL_RenderCopy(m_renderer, new_texture, clip, &render_rect);
    SDL_RenderPresent(m_renderer);
}

void Board::setupBoard()
{
    for(int i = 0; i < m_pieces.size(); i++)
    {
        int pos = m_pieces[i]->getPos();
        drawSprites(pos % 8 *SQUARE_SIZE, (int) floor(pos / 8) * SQUARE_SIZE, m_pieces[i]->getClip());
    }
}

void Board::updateBoard()
{
    for(int i = 0; i < m_squares_to_update.size(); i++)
    {
        int pos = m_squares_to_update[i];
        drawSprites(pos % 8 *SQUARE_SIZE, (int) floor(pos / 8) * SQUARE_SIZE, pieceFromPos(pos)->getClip());
    }
    m_squares_to_update.clear();
}

void Board::setClipFromType(Piece* p)
{
    int col = p->getColor();
    int type = p->getType();
    if(col == 8)
    {
        switch (type) 
        {
        case KING:
            p->setClip(m_sprite_clips[0]);
            break;
        case QUEEN:
            p->setClip(m_sprite_clips[1]);
            break;
        case BISHOP:
            p->setClip(m_sprite_clips[2]);
            break;
        case KNIGHT:
            p->setClip(m_sprite_clips[3]);
            break;
        case ROOK:
            p->setClip(m_sprite_clips[4]);
            break;
        case PAWN:
            p->setClip(m_sprite_clips[5]);
            break;
        default:
            p->setClip(nullptr);
            break;
        }
    }
    else 
    {
        switch (type) 
        {
        case KING:
            p->setClip(m_sprite_clips[6]);
            break;
        case QUEEN:
            p->setClip(m_sprite_clips[7]);
            break;
        case BISHOP:
            p->setClip(m_sprite_clips[8]);
            break;
        case KNIGHT:
            p->setClip(m_sprite_clips[9]);
            break;
        case ROOK:
            p->setClip(m_sprite_clips[10]);
            break;
        case PAWN:
            p->setClip(m_sprite_clips[11]);
            break;
        default:
            p->setClip(nullptr);
            break;
        }
    }
}

void Board::convertFEN(std::string fen)
{
    int pos = 0;
    int fen_data_track = 0;
    for (int i = 0; i < fen.length(); i++) 
    {
        if(isdigit(fen[i]))
        {
            pos += (int) fen[i] - 48;
        }
        else if (fen[i] != '/' && fen[i] != ' ') 
        {
            switch (fen[i]) 
            {
            case 'p':
                m_pieces.push_back(new Piece(BLACK + PAWN, m_sprite_clips[11], pos));
                break;
            case 'r':
                m_pieces.push_back(new Piece(BLACK + ROOK, m_sprite_clips[10], pos));
                break;
            case 'n':
                m_pieces.push_back(new Piece(BLACK + KNIGHT, m_sprite_clips[9], pos));
                break;
            case 'b':
                m_pieces.push_back(new Piece(BLACK + BISHOP, m_sprite_clips[8], pos));
                break;
            case 'q':
                m_pieces.push_back(new Piece(BLACK + QUEEN, m_sprite_clips[7], pos));
                break;
            case 'k':
                m_pieces.push_back(new Piece(BLACK + KING, m_sprite_clips[6], pos));
                break;
            case 'P':
                m_pieces.push_back(new Piece(WHITE + PAWN, m_sprite_clips[5], pos));
                break;
            case 'R':
                m_pieces.push_back(new Piece(WHITE + ROOK, m_sprite_clips[4], pos));
                break;
            case 'N':
                m_pieces.push_back(new Piece(WHITE + KNIGHT, m_sprite_clips[3], pos));
                break;
            case 'B':
                m_pieces.push_back(new Piece(WHITE + BISHOP, m_sprite_clips[2], pos));
                break;
            case 'Q':
                m_pieces.push_back(new Piece(WHITE + QUEEN, m_sprite_clips[1], pos));
                break;
            case 'K':
                m_pieces.push_back(new Piece(WHITE + KING, m_sprite_clips[0], pos));
                break;
            default:
                break;
            }
            pos++;
        }
        if(pos == 63 && fen_data_track == 0)
        {
            if (fen[i] == 'b') 
            {
                m_turn = BLACK;
                fen_data_track++;
            }
        }
    }
    std::string result = (m_turn == 8) ? "White" : "Black";
    std::cout << "Turn: " << result << std::endl;
}

Piece* Board::pieceFromPos(int pos)
{
    for (int i = 0; i < m_pieces.size(); i++)
    {
        if (m_pieces[i]->getPos() == pos)
        {
            return m_pieces[i];
        }
    }
    return nullptr;
}

void Board::playerMove(int mouseX, int mouseY)
{
    m_target_pos = (int)floor(mouseX / SQUARE_SIZE) + ((int)floor(mouseY / SQUARE_SIZE) * 8);
    Piece* p = pieceFromPos(m_target_pos);
    std::cout << m_target_pos << " ";
    if (p && !m_piece_to_move) 
    {
        m_piece_to_move = p;
        m_prev_pos = m_target_pos;
        return;
    }
    if(m_piece_to_move)
    {
        int move = validateMove();
        if (move == 1) 
        {
            moveToCapture();
        }
        if (move == 0) 
        {
            moveToCapture();
        }
        if (move == 2) 
        {
            shortCastle();
        }
        if (move == 3) 
        {
            longCastle();
        }
        if (move == 4) 
        {
            pawnPromote();
        }
        if (move == 5) 
        {
            enPassant();
        }
        m_piece_to_move = nullptr;
    }
}

void Board::moveToEmpty()
{
    int cover = (m_turn == WHITE) ? 8 : -8;
    m_piece_to_move->setHasMoved();
    drawSquareAtPos(m_prev_pos % 8, floor(m_prev_pos / 8));
    m_piece_to_move->setPos(m_target_pos);
    m_squares_to_update.push_back(m_target_pos);
    if (m_piece_to_move->getType() == PAWN && abs(m_prev_pos - m_target_pos) == 16) 
    {
        m_enpassant = m_target_pos + cover;
    }
    switchTurn();
}

void Board::moveToCapture()
{
    m_piece_to_move->setHasMoved();
    drawSquareAtPos(m_target_pos % 8, floor(m_target_pos / 8));
    drawSquareAtPos(m_prev_pos % 8, floor(m_prev_pos / 8));

    for (int i = 0; i < m_pieces.size(); i++) 
    {
        if(m_pieces[i]->getPos() == m_target_pos)
        {
            m_pieces.erase(m_pieces.begin() + i);
        }
    }

    m_piece_to_move->setPos(m_target_pos);
    m_squares_to_update.push_back(m_target_pos);
    switchTurn();
}

void Board::shortCastle()
{
    m_piece_to_move->setPos(m_target_pos);
    Piece* r = pieceFromPos(m_target_pos + 1);

    drawSquareAtPos(m_prev_pos % 8, floor(m_prev_pos / 8));
    drawSquareAtPos((m_target_pos % 8) + 1, floor(m_prev_pos / 8));
    m_squares_to_update.push_back(m_target_pos);
    m_squares_to_update.push_back(m_target_pos - 1);

    m_piece_to_move->setHasMoved();
    r->setHasMoved();
    switchTurn();
}

void Board::longCastle()
{
    m_piece_to_move->setPos(m_target_pos);
    Piece* r = pieceFromPos(m_target_pos - 2);
    r->setPos(m_target_pos +1);

    drawSquareAtPos(m_prev_pos % 8, floor(m_prev_pos / 8));
    drawSquareAtPos((m_target_pos % 8) - 2, floor(m_prev_pos / 8));
    m_squares_to_update.push_back(m_target_pos);
    m_squares_to_update.push_back(m_target_pos + 1);

    m_piece_to_move->setHasMoved();
    r->setHasMoved();
    switchTurn();
}

void Board::pawnPromote()
{
    std::string input;
    std::cout << "Enter piece to promote pawn to (n, b, q, r): ";
    std::cin >> input;
    int col = m_piece_to_move -> getColor();
    if(input == "n")
    {
        m_piece_to_move->setType(KNIGHT + col);
    }
    else if(input == "b")
    {
        m_piece_to_move->setType(BISHOP + col);
    }
    else if(input == "q")
    {
        m_piece_to_move->setType(QUEEN + col);
    }
    else if(input == "r")
    {
        m_piece_to_move->setType(ROOK + col);
    }

    drawSquareAtPos(m_prev_pos % 8, floor(m_prev_pos / 8));
    m_piece_to_move->setPos(m_target_pos);
    drawSquareAtPos(m_target_pos % 8 , floor(m_target_pos / 8));
    setClipFromType(m_piece_to_move);
    m_squares_to_update.push_back(m_target_pos);
    switchTurn();
}

void Board::enPassant()
{
    int cover = m_turn == WHITE ? 8 : -8;
    drawSquareAtPos(m_prev_pos % 8, floor(m_prev_pos / 8));
    drawSquareAtPos(m_enpassant % 8, floor((m_enpassant + cover) / 8));
    for (int i = 0; i < m_pieces.size(); i++) 
    {
        if(m_pieces[i]->getPos() == m_enpassant + cover)
        {
            m_pieces.erase(m_pieces.begin() + 1);
        }
    }
    m_piece_to_move->setPos(m_enpassant);
    m_squares_to_update.push_back(m_target_pos);
    switchTurn();
}

void Board::switchTurn()
{
    m_move += 0.5f;
    m_turn == WHITE ? m_turn = BLACK : m_turn = WHITE;
    genarateAttackedPosition();
    genarateMoves();
}

// MOVE FUNING MOVE
// MOVE FUNING MOVE
// MOVE FUNING MOVE
// MOVE FUNING MOVE
// MOVE FUNING MOVE
// MOVE FUNING MOVE

void Board::genarateMoves()
{
    m_moves.clear();
    std::cout << "\nClearing moves";
    for (int i = 0; i < m_pieces.size(); i++) 
    {
        if(m_pieces[i]->getColor() == m_turn)
        {
            switch (m_pieces[i]->getType()) 
            {
            case PAWN:
                pawnMove(m_pieces[i]);
                break;
            }
        }
    }
}

void Board::genarateAttackedPosition()
{
    for (int i = 0; i < m_moves.size(); i++) 
    {
        if(m_moves[i]->type == 0)
        {
            m_attacked_pos.push_back(m_moves[i]->target);
        }
    }
}

int Board::validateMove()
{
    for (int i = 0; i < m_moves.size(); i++) 
    {
        if(m_prev_pos == m_moves[i] -> prev && m_target_pos == m_moves[i] -> target)
        {
            return m_moves[i] -> type;
        }
    }
    return -1;
}

void Board::pawnMove(Piece* p)
{
    int move_direction = 1;
    int capture_color = WHITE;
    if(m_turn == WHITE)
    {
        move_direction = -1;
        capture_color = BLACK;
    }

    int pos = p -> getPos();
    int once_forward = pos + (move_direction * 8);
    int twice_forward = pos + (move_direction * 16);
    int capture_left = pos + (move_direction * 7);
    int capture_right = pos + (move_direction * 9);
    if(!pieceFromPos(once_forward) && 0 <= once_forward && once_forward < 64)
    {
        if(once_forward < 8 || once_forward > 55)
        {
            m_moves.push_back(new Move(pos, once_forward, 4));
        }
        else
        {
            m_moves.push_back(new Move(pos, once_forward, 0));
        }
    }
    if(capture_left == m_enpassant || capture_right == m_enpassant) 
    {
        m_moves.push_back(new Move(pos, m_enpassant, 5));
    }
    if(pieceFromPos(capture_left) && 0 <= capture_left && capture_left < 64)
    {
        if(pieceFromPos(capture_left) -> getColor() == capture_color)
        {
            m_moves.push_back(new Move(pos, capture_left, 1));
        }
    }
    if(pieceFromPos(capture_right) && 0 <= capture_right && capture_right < 64)
    {
        if(pieceFromPos(capture_right) -> getColor() == capture_color)
        {
            m_moves.push_back(new Move(pos, capture_right, 1));
        }
    }
}

void Board::bishopMove(Piece * p)
{
    diagMove(p);
}

void Board::rookMove(Piece * p)
{
    orthoMove(p);
}

void Board::queenMove(Piece * p)
{
    diagMove(p);
    orthoMove(p);
}

void Board::knightMove(Piece * p)
{
    offSetMove(p, KNIGHT_OFF_SET);
}

void Board::kingMove(Piece * p)
{
    offSetMove(p, KING_OFF_SET);
    castleCheck(p);
    for (int i = 0; i < m_moves.size(); i++) 
    {
        if(m_moves[i]->target == p->getPos())
        {
            std::cout << "Check ";
        }
        if(m_moves[i]->prev == p->getPos())
        {
            for (int n = 0; n < m_attacked_pos.size(); n++) 
            {
                if(m_moves[i]->target == m_attacked_pos[n])
                {
                    m_moves.erase(m_moves.begin() + 1);
                }
            }
        }   
    }
}

void Board::castleCheck(Piece * p)
{
    if(p->getHasMoved())
    {
        return;
    }
    int k_pos = p->getPos();
    Piece* k_rook = pieceFromPos(k_pos + 3);
    Piece* q_rook = pieceFromPos(k_pos - 4);
    if(!pieceFromPos(k_pos + 1) && !pieceFromPos(k_pos + 2) && k_rook)
    {
        if(!k_rook->getHasMoved()) 
        {
            m_moves.push_back(new Move(k_pos, k_pos + 2, 2));
        }
    }
    if(!pieceFromPos(k_pos - 1) && !pieceFromPos(k_pos - 2) && !pieceFromPos(k_pos - 3) && q_rook)
    {
        if(!q_rook->getHasMoved()) 
        {
            m_moves.push_back(new Move(k_pos, k_pos - 2, 3));
        }
    }
}

void Board::offSetMove(Piece *p, const int off[8])
{
    int capture_color = (m_turn == WHITE) ? BLACK : WHITE;
    for (int i = 0; i < 8; i++) 
    {
        int new_pos = p->getPos() + off[i];
        if(0 <= new_pos && new_pos < 64)
        {
            Piece* otherPiece = pieceFromPos(new_pos);
            if(otherPiece)
            {
                if (otherPiece->getColor() == capture_color) 
                {
                    m_moves.push_back(new Move(p->getPos(), new_pos, 1));
                }
                else continue;
            }
            m_moves.push_back(new Move(p->getPos(), new_pos, 0));
        }
    }
}

void Board::diagMove(Piece *p)
{
    int capture_color = (m_turn == WHITE) ? BLACK : WHITE;
    int offset[4] = {-7, 7, -9, 9};

    for (int i = 0; i < 4; i++) 
    {
        int new_pos = p->getPos() + offset[i];
        while (0 <= new_pos && new_pos < 64) 
        {
            Piece* otherPiece = pieceFromPos(new_pos);
            if(otherPiece)
            {
                if (otherPiece->getColor() == capture_color) 
                {
                    m_moves.push_back(new Move(p->getPos(), new_pos, 1));
                }
                else break;
            }
            m_moves.push_back(new Move(p->getPos(), new_pos, 0));
            new_pos += offset[i];
        }
    }
}

void Board::orthoMove(Piece *p)
{
    int capture_color = (m_turn == WHITE) ? BLACK : WHITE;
    int offset[4] = {-8, 8, -1, 1};

    for(int i = 0; i < 4; i++)
    {
        int new_pos = p->getPos() + offset[i];
        while (0 <= new_pos && new_pos < 64 && (new_pos % 8) + 1 != 0) 
        {
            Piece* otherPiece = pieceFromPos(new_pos);
            if (otherPiece) 
            {
                if (otherPiece->getColor() == capture_color) 
                {
                    m_moves.push_back(new Move(p->getPos(), new_pos, 1));
                    break;
                }
                else break;
            }
            m_moves.push_back(new Move(p->getPos(), new_pos, 0));
            new_pos += offset[i];
        }
    }
}