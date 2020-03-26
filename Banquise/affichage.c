#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "affichage.h"

/******* AFFICHAGE *******/

// BENJAMIN - CHANGE LA COULEUR

void ChangeTextColor(t_color color)
{
    switch(color)
    {
        case RED : textcolor(12); break;
        case GREEN : textcolor(10); break;
        case BLUE : textcolor(11); break;
        case YELLOW : textcolor(14); break;
        case WATER_COLOR : textcolor(3); break;
        case ICE_COLOR : textcolor(9); break;
        case ROCK_COLOR : textcolor(8); break;
        case HAMMER_COLOR :
        case SPRING_COLOR : textcolor(5); break;
        case FINAL_POINT_COLOR : textcolor(6); break;
        case COLOR_DEFAULT : textcolor(7); break;
    }
}

// BENJAMIN - VERIFIE S'IL Y'A UN JOUEUR SUR UNE CASE

int CheckPosition(int indbanqx, int indbanqy, t_player* player)
{
    int death = (*player).death;
    int playerposx = (*player).position.x;
    int playerposy = (*player).position.y;

    return ((death == 0) && (indbanqx == playerposx) && (indbanqy == playerposy)); // 1 si le joueur est vivant et sur les mêmes indices que la matrice
}

// BENJAMIN - CHANGE LA COULEUR POUR LES JOUEURS

void ChangeColorPlayerMatrix(t_player* arr_player, int nb_player, int banqx, int banqy)
{
    int i;
    for(i=0; i<nb_player; i++)
    {
        if(CheckPosition(banqx, banqy, &arr_player[i]) == 1)
        {
            ChangeTextColor(arr_player[i].color);   // Change la couleur en celle du joueur
            break;
        }
    }
}

// BENJAMIN - CHANGE LA COULEUR POUR LES SOLS

void ChangeColorGroundMatrix(t_ground ground)
{
    switch(ground)
    {
    case WATER : ChangeTextColor(WATER_COLOR); break;
    case ICE : ChangeTextColor(ICE_COLOR); break;
    case ROCK : ChangeTextColor(ROCK_COLOR); break;
    case SPRING : ChangeTextColor(SPRING_COLOR); break;
    case HAMMER_HEAD :
    case HAMMER_PLINTH : ChangeTextColor(HAMMER_COLOR); break;
    case FINAL_POINT : ChangeTextColor(FINAL_POINT_COLOR); break;
    default : ChangeTextColor(COLOR_DEFAULT);
    }
}

// BENJAMIN - AFFICHE LA MATRICE AVEC LES COULEURS

void DisplayWithColors(t_banquise* banquise, t_player* arr_player, int nb_players)
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

            ChangeColorGroundMatrix(matrix[i][j]);
            ChangeColorPlayerMatrix(arr_player, nb_players, j, i);      // Vérifie s'il y a un joueur sur les indices courants si oui on change la couleur à celle du joueur
            printf("% d", matrix[i][j]);
            ChangeTextColor(COLOR_DEFAULT);                             // Remet la couleur par defaut

            if(j%b_size == b_size-1) printf(" |");
        }
    }
    printf("\n\n");
}
