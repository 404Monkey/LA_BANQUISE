#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "players.h"

typedef struct
{
    t_banquise* banquise;
    t_player* tab_player;
    int nb_player;
    int nb_lap;
} t_game;

t_game* InitGame(void);
