#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "affichage.h"

int main()
{
    // ***** BANQUISE ***** //
    t_banquise* my_banquise = malloc(sizeof(t_banquise)); //creation d'une banquise

    my_banquise = initBanquise(); //initialisation d'une banquise en BANQUISE

    afficheMatrice(my_banquise);

    // ***** PLAYERS ***** //
    int nb_joueurs;

    do{
    printf("Combien de joueurs voulez-vous pour cette partie? (entre 1 et 4) : ");
    scanf("%d", &nb_joueurs);
    } while ((nb_joueurs<1)||(nb_joueurs>4));

    t_player *tab_joueurs = malloc(sizeof(t_player)*nb_joueurs); // MEEEEHHHHH cest legit ??

    CreerTabJoueurs_aux(tab_joueurs, nb_joueurs);

    for (int i=0; i<nb_joueurs; i++)
    {
        printf("couleur %d : %d\n", tab_joueurs[i].id, tab_joueurs[i].color);
        printf("posx %d : %d\n", tab_joueurs[i].id, tab_joueurs[i].position.x);
        printf("posy %d : %d\n", tab_joueurs[i].id, tab_joueurs[i].position.y);
    }

    //AffectePositionJoueursMatrice(my_banquise, my_tab_joueurs, player_size);

    return 0;
}
