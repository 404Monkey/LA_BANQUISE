#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "Movement.h"

typedef struct
{
    t_banquise* banquise;
    t_player* arr_player;
    int nb_player;
    int nb_lap;
    int* ranking;
} t_game;


t_game* InitGame(void);                     // Initialise un jeu

void sort_tab(int tab[4][2], int size_tab);
void sort_ranking(t_game *game);
int verif_victory(t_game *game);

void PlayLap(t_game* game);                 // Joue un tour de jeu
void PlayGame(t_game* game);                // Lance une partie








