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
    (*game).nb_lap = 1;

    ImplementeJoueurMatrice((*game).banquise, (*game).tab_player, (*game).nb_player);

    return game;
}

void PlayLap(t_game* game)
{
    int i;
    for(i=0; i<(*game).nb_player; i++)
    {
        printf("Tour n°%d\n", (*game).nb_lap);                                      //Affiche du numéro de tour
        printf("%s, à toi de jouer !\n", (*game).tab_player[i].name);               //Affiche quel joueur doit jouer
        displacement_player(&(*game).tab_player[i], (*game).banquise);              //Demande aux joueur de se deplacer
        system("cls");                                                              //clear la console
        AfficheWithPlayers((*game).banquise, (*game).tab_player, (*game).nb_player);//Affiche la matrices
    }
    (*game).nb_lap += 1;
}

void PlayGame(t_game* game)
{
    while(1)
    {
        PlayLap(game);
    }
}
