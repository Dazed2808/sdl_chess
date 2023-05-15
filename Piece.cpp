#include "Piece.h"
#include <SDL2/SDL_rect.h>

Piece::Piece()
{

}

Piece::Piece(int type)
{
    setType(type);
}

Piece::Piece(int type, SDL_Rect* clip, int pos)
{
    setType(type);
    m_clip = clip;
    m_pos = pos;
}

Piece::~Piece()
{
    delete m_clip;
}

void Piece::setType(int type)
{
    if(type - 16 < 0)
    {
        m_color = 8;
        m_type = type - 8;
    }
    else
    {
        m_color = 16;
        m_type = type - 16;
    }
}

int Piece::getColor()
{
    return m_color;
}

int Piece::getType()
{
    return m_type;
}

void Piece::setClip(SDL_Rect * clip)
{
    m_clip = clip;
}

SDL_Rect* Piece::getClip()
{
    return m_clip;
}

bool Piece::getHasMoved()
{
    return m_has_moved;
}

void Piece::setHasMoved()
{
    m_has_moved = true;
}

int Piece::getPos()
{
    return m_pos;
}

void Piece::setPos(int pos)
{
    m_pos = pos;
}