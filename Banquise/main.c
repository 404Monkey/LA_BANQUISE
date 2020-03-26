#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

#include "game.h"


int main()
{
    srand(time(NULL));

    t_game* my_game = malloc(sizeof(t_game));
    my_game = InitGame();

    PlayGame(my_game);

    free(my_game);

    return 0;
}
