#include <stdio.h>
#include <stdlib.h>

#include "players.h"

#define PLAYER_GAP 3

t_player* CreatePlayer(t_color color, int id)
{
    t_player* player = malloc(sizeof(t_player));

    char* name = malloc(sizeof(char));
    printf("Joueur %d, Veuillez rentrer votre nom : ", id+1);
    scanf("%s", name);
    (*player).name = name;

    (*player).color = color;
    (*player).id = id;
    (*player).position.x = (*player).position.y = 0;
    (*player).vect.dx = (*player).vect.dy = 0;
    (*player).score = 0;
    (*player).death = 0;
    (*player).win = 0;

    return player;
}

void CreateArrPlayer(t_player* arr_player, int nb_player)
{
    for (int i=0; i<nb_player; i++)
    {
        arr_player[i] = *CreatePlayer(i,i);
        switch(i)
        {
            case 0 : arr_player[i].position.x = arr_player[i].start_point.x =PLAYER_GAP;
                     arr_player[i].position.y = arr_player[i].start_point.y = PLAYER_GAP; break;
            case 1 : arr_player[i].position.x = arr_player[i].start_point.x = MATRIX_SIZE - PLAYER_GAP-1;
                     arr_player[i].position.y = arr_player[i].start_point.y = PLAYER_GAP; break;
            case 2 : arr_player[i].position.x = arr_player[i].start_point.x = MATRIX_SIZE - PLAYER_GAP -1;
                     arr_player[i].position.y = arr_player[i].start_point.y = MATRIX_SIZE - PLAYER_GAP -1; break;
            case 3 : arr_player[i].position.x = arr_player[i].start_point.x = PLAYER_GAP;
                     arr_player[i].position.y = arr_player[i].start_point.y = MATRIX_SIZE - PLAYER_GAP-1; break;
        }
    }
}

void ImplementPlayerMatrix_aux(t_banquise* banquise, t_player* player)
{
    int posx = (*player).position.x;
    int posy = (*player).position.y;

    (*banquise).matrix[posy][posx] = PLAYER;
}

void ImplementPlayerMatrix(t_banquise* banquise, t_player* arr_player, int nb_player)
{
    int i;
    for(i=0; i<nb_player; i++)
    {
        ImplementPlayerMatrix_aux(banquise, &arr_player[i]);
    }
}
