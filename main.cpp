

#include "dp/dummy_game/dummy_game_client/dummy_game_client/dummy_game_client.h"

int main()
{
    dp::dummy_game_client d;

    d.start();
    d.blockUntilDead();

    return 0;
}
