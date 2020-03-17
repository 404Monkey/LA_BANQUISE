#include <stdio.h>
#include <stdlib.h>

#include "ice.h"

void displacement_y(t_player *player, int displacement);
void displacement_x(t_player *player, int displacement);
void primary_displacement_player(t_player* player, char touch);
int verif_exit_board(int x, int y, int size_board);
int verif_player_board(int x, int y,t_banquise *board);
int verif_displacement(t_player *player, t_banquise *board);
int verif_player_death(t_player *player, int x, int y, t_banquise *board);
void verif_player_won(t_player *player, t_banquise *board);
void displacement_player(t_player *player, t_banquise *board);
void RespawnPlayer(t_player* player, t_banquise* banquise);















