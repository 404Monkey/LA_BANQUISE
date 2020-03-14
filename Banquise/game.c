#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "game.h"

t_game* InitGame()
{
    t_game* game = malloc(sizeof(t_game));

    t_banquise* banquise = malloc(sizeof(t_banquise));
    banquise = InitBanquise();

    int nb_players;

    do{
    printf("Combien de joueurs voulez-vous pour cette partie? (entre 1 et 4) : ");
    scanf("%d", &nb_players);
    } while ((nb_players<1)||(nb_players>4));

    t_player *arr_players = malloc(sizeof(t_player)*nb_players); // MEEEEHHHHH cest legit ??
    CreateArrPlayer(arr_players, nb_players);

    (*game).banquise = banquise;
    (*game).arr_player = arr_players;
    (*game).nb_player = nb_players;
    (*game).nb_lap = 1;

    ImplementPlayerMatrix((*game).banquise, (*game).arr_player, (*game).nb_player);

    return game;
}

void PlayLap(t_game* game)
{
    int i;
    for(i=0; i<(*game).nb_player; i++)
    {
        if((*game).arr_player[i].death == 1) {}
        //system("cls");                                                              //clear la console
        DisplayWithPlayers((*game).banquise, (*game).arr_player, (*game).nb_player);//Affiche la matrices

        printf("Tour n°%d\n", (*game).nb_lap);                                      //Affiche du numéro de tour
        printf("%s, à toi de jouer !\n", (*game).arr_player[i].name);               //Affiche quel joueur doit jouer
        displacement_player(&(*game).arr_player[i], (*game).banquise);              //Demande aux joueur de se deplacer
        printf("P%d_win : %d\n", i, (*game).arr_player[i].win);
        printf("P%d_death : %d\n", i, (*game).arr_player[i].death);
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
