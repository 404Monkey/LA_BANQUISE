#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "affichage.h"

typedef struct
{
    t_banquise* banquise;
    t_player* arr_player;
    int nb_player;
    int nb_lap;
} t_game;

t_game* InitGame(void);         // Initialise un jeu
void PlayLap(t_game* game);     // Joue un tour de jeu
void PlayGame(t_game* game);    // Lance une partie
