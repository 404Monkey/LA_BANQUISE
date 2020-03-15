#include <stdio.h>
#include <stdlib.h>

#include "players.h"

void displacement_player(t_player *player, t_banquise *board);

void RespawnPlayer(t_player* player, t_banquise* banquise);
int verif_player_won(t_player *player, t_banquise *board);
