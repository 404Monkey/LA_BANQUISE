#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "players.h"

int main()
{
    t_banquise* my_banquise = malloc(sizeof(t_banquise)); //creation d'une banquise

    my_banquise = initBanquise(); //initialisation d'une banquise en BANQUISE

    afficheMatrice(my_banquise);

    t_player* my_tab_joueurs = malloc(sizeof(t_player));

    int player_size = CreerTabJoueurs(my_tab_joueurs);

    printf("%d\n", my_tab_joueurs[0].color);

    //AffectePositionJoueursMatrice(my_banquise, my_tab_joueurs, player_size);

    return 0;
}
