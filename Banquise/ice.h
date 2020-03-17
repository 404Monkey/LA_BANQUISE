#include <stdio.h>
#include <stdlib.h>

#include "players.h"

typedef struct{
    t_vector vect;
    t_pos position;
    int is_moving;
    t_player* player_source;
} t_ice;

int RandomInt(int rmin, int rmax);
void GenerateRandomIce(t_banquise* banquise);
t_ice* CreateIce();
void StopMoving(t_ice* ice, t_ground** matrix); // Stoppe un glacon
void MoveIce(t_ice* ice, t_banquise* banquise, t_player* player);















