#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "game.h"

t_game* InitGame()
{
    t_game* game = malloc(sizeof(t_game));

    t_banquise* banquise = malloc(sizeof(t_banquise));
    banquise = initBanquise();

    int nb_joueurs;

    do{
    printf("Combien de joueurs voulez-vous pour cette partie? (entre 1 et 4) : ");
    scanf("%d", &nb_joueurs);
    } while ((nb_joueurs<1)||(nb_joueurs>4));

    t_player *tab_joueurs = malloc(sizeof(t_player)*nb_joueurs); // MEEEEHHHHH cest legit ??
    CreerTabJoueurs_aux(tab_joueurs, nb_joueurs);

    (*game).banquise = banquise;
    (*game).tab_player = tab_joueurs;
    (*game).nb_player = nb_joueurs;
    (*game).nb_lap = 0;

    ImplementeJoueurMatrice((*game).banquise, (*game).tab_player, (*game).nb_player);

    return game;
}
