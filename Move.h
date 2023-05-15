#pragma once
#ifndef MOVE
#define MOVE

class Move
{
public:
    Move(int, int);
    Move(int, int, int);
    int prev;
    int target;
    int type;
};

#endif //MOVE