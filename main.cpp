

#include "dp/tictactoe/tictactoe_game/tictactoe_game/tictactoe_game.h"

int main()
{
    dp::tictactoe_game d;

    d.start();
    d.blockUntilDead();

    return 0;
}
