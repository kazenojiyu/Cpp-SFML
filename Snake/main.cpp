#include "game.h"

int main()
{
    Game game;

    if(!game.init())
        return EXIT_FAILURE;

    game.run();
    return EXIT_SUCCESS;
}