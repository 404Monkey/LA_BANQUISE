#include <stdio.h>
#include <stdlib.h>

#include "affichage.h"

typedef struct{
    t_vector vect;
    t_pos position;
    int is_moving;
    int player_source;
} t_ice;

int RandomInt(int rmin, int rmax);
void GenerateRandomIce(t_banquise* banquise);
t_ice* InitIce(t_player* player);
int verif_exit_board_ice(int x, int y, int size_board);
int verif_player_in_pos(int x, int y, t_player *arr_player, int nb_player);
void kill_by_ice(int x, int y, int id_killer, t_player *arr_player, int nb_player);
void displacement_ice(t_ice *ice, t_banquise *board, t_player *arr_player, int nb_player);


















