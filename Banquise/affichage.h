#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "movement.h"

void textcolor(int color);
void ChangeTextColor(int color);
int CheckPosition(int indbanqx, int indbanqy, t_player* player);
void ChangeColorPlayerMatrix(t_player* arr_player, int nb_player, int banqx, int banqy);
void DisplayWithPlayers(t_banquise* banquise, t_player* arr_player, int nb_players);
