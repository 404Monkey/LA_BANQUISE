#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "players.h"

void textcolor(int color);
void CouleurTexte(int color);
int CheckPosition(int indbanqx, int indbanqy, int posplayerx, int posplayery);
void ChangeCouleurJoueurMatrice(t_player* tab_players, int nb_player, int banqx, int banqy);
void AfficheWithPlayers(t_banquise* banquise, t_player* tab_player, int nb_players);
