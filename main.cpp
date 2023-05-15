#include <SDL2/SDL.h>
#include "Game.h"

int main(int argc, char* argv[])
{
    Game chess = Game();
    chess.GameLoop();
    return 0;
}