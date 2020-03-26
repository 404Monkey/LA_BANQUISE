#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "Movement.h"

/******* STRUCTURES *******/

//Type du jeu
typedef struct
{
    t_banquise* banquise;   // plateau de jeu
    t_player* arr_player;   // tableau de joueurs
    int nb_player;          // nombre de joueurs
    int nb_lap;             // nombre de tour
    int* ranking;           // classement de joueurs
} t_game;


/******* PROTOTYPES *******/

//Initialisation jeu
t_game* InitGame(void);                     // Initialise un jeu

//Fin du jeu
void sort_tab(int tab[4][2], int size_tab); //HENINTSOA - FONCTION POUR TRIER UN TABLEAU A 2 DIMENSIONS
void sort_ranking(t_game *game);            //HENINTSOA - FONCTION POUR EFFECTUER LE CLASSEMENT DES JOUEURS
int verif_victory(t_game *game);            //HENINTSOA - FONCRION VERIFIANT SI UN JOUEUR EST ARRIVE AU POINT D'ARRIVEE
void display_end_game(t_game *game);        //HENINTSOA - FONCTION PERMETTANT D'ETABLIR ET D'AFFICHER LE CLASSEMENT EN FIN DE JEU

//Jeu
void PlayLap(t_game* game);                 // Joue un tour de jeu
void PlayGame(t_game* game);                // Lance une partie








