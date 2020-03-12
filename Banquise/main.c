#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "game.h"

int main()
{
    t_game* my_game = malloc(sizeof(t_game));
    my_game = InitGame();

    AfficheWithPlayers((*my_game).banquise, (*my_game).tab_player, (*my_game).nb_player);

    displacement_player(&(*my_game).tab_player[3], (*my_game).banquise);

    int nb_joueurs = (*my_game).nb_player;
    /*for (int i=0; i<nb_joueurs; i++)
    {
        printf("couleur %d : %d\n", (*my_game).tab_player[i].id, (*my_game).tab_player[i].color);
        printf("posx %d : %d\n", (*my_game).tab_player[i].id, (*my_game).tab_player[i].position.x);
        printf("posy %d : %d\n", (*my_game).tab_player[i].id, (*my_game).tab_player[i].position.y);
    }*/

    AfficheWithPlayers((*my_game).banquise, (*my_game).tab_player, (*my_game).nb_player);

    return 0;
}
