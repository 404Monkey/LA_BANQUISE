#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "affichage.h"

void textcolor(int color)
{
HANDLE h=GetStdHandle(STD_OUTPUT_HANDLE);
   SetConsoleTextAttribute(h,color);
}

void ChangeTextColor(t_color color)
{
    switch(color)
    {
        case RED : textcolor(4); break;
        case GREEN : textcolor(2); break;
        case BLUE : textcolor(1); break;
        case YELLOW : textcolor(6); break;
        case COLOR_DEFAULT : textcolor(7); break;
    }
}

int CheckPosition(int indbanqx, int indbanqy, t_player* player)
{
    return (((*player).death == 0) && (indbanqx == (*player).position.x)&&(indbanqy == (*player).position.y)); // 1 si le joueur est vivant et sur les mêmes indices que la matrice
}

void ChangeColorPlayerMatrix(t_player* arr_player, int nb_player, int banqx, int banqy)
{
    int i;
    for(i=0; i<nb_player; i++)
    {
        if(CheckPosition(banqx, banqy, &arr_player[i]) == 1)
        {
            ChangeTextColor(arr_player[i].color);                                                              // Change la couleur en celle du joueur
            break;
        }else ChangeTextColor(COLOR_DEFAULT);                                                                  // gris clair (couleur de base)
    }
}

void DisplayWithPlayers(t_banquise* banquise, t_player* arr_player, int nb_players)
{
    t_ground** matrix = (*banquise).matrix;                             // récupère la matrice
    int b_size = (*banquise).banquise_size;                             // récupère la taille de la matrice

    printf("la banquise a boug%c !\n", 130);

    int i, j;
    for(i=0; i<b_size; i++)
    {
        for(j=0; j<b_size; j++)
        {
            if(j%b_size == 0) printf("\n|");

            ChangeColorPlayerMatrix(arr_player, nb_players, j, i);      // Vérifie s'il y a un joueur sur les indices courants si oui on change la couleur à celle du joueur
            printf("% d", matrix[i][j]);

            if(j%b_size == b_size-1) printf(" |");
        }
    }
    printf("\n\n");
}
