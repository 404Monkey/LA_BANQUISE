#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "game.h"

t_game* InitGame()
{
    t_game* game = malloc(sizeof(t_game));                                          // créer un t_game* et alloue l'espace associé

    t_banquise* banquise = malloc(sizeof(t_banquise));                              // créer un t_banquise* et alloue l'espace associé
    banquise = InitBanquise();                                                      // Initialise une banquise

    int nb_players;
    do{
    printf("Combien de joueurs voulez-vous pour cette partie? (entre 1 et 4) : ");  // Demande le nombre de joueurs à l'utilisateur
    scanf("%d", &nb_players);
    } while ((nb_players<1)||(nb_players>4));

    t_player *arr_players = malloc(sizeof(t_player)*nb_players);                    // créer un t_player* (tableau de joueurs) et alloue l'espace associé
    CreateArrPlayer(arr_players, nb_players);                                       // Créer le tableau de joueurs

    (*game).banquise = banquise;                                                    // Implementation des valeurs du t_game*
    (*game).arr_player = arr_players;
    (*game).nb_player = nb_players;
    (*game).nb_lap = 1;

    ImplementPlayerMatrix((*game).banquise, (*game).arr_player, (*game).nb_player); // Implemente les joueurs dans la matrice

    return game;
}

void PlayLap(t_game* game)
{
    int i;
    for(i=0; i<(*game).nb_player; i++)
    {
        system("cls");                                                              //clear la console
        DisplayWithPlayers((*game).banquise, (*game).arr_player, (*game).nb_player);//Affiche la matrices

        printf("Tour n%c%d\n", 248, (*game).nb_lap);                                //Affiche du numéro de tour
        printf("%s, %c toi de jouer !\n", (*game).arr_player[i].name, 133);         //Affiche quel joueur doit jouer

        /** affichage test **                                                       // Si on veut afficher faire avant displacement le scans retarde le clear
        printf("P%d_win : %d\n", i, (*game).arr_player[i].win);
        printf("P%d_death : %d\n", i, (*game).arr_player[i].death);**/
        printf("P%d_score : %d\n", i, (*game).arr_player[i].score);

        displacement_player(&(*game).arr_player[i], (*game).banquise);              //Demande aux joueur de se deplacer
        RespawnPlayer(&(*game).arr_player[i], (*game).banquise);
    }
    (*game).nb_lap += 1;                                                            // Compte le nombre de tour
}

void PlayGame(t_game* game)
{
    while(1)
    {
        PlayLap(game);
    }
}
