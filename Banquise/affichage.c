#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "affichage.h"


void textcolor(int color)
{
HANDLE h=GetStdHandle(STD_OUTPUT_HANDLE);
   SetConsoleTextAttribute(h,color);
}

void CouleurTexte(int color)
{
    switch(color)
    {
        case RED : textcolor(4); break;
        case GREEN : textcolor(2); break;
        case BLUE : textcolor(1); break;
        case YELLOW : textcolor(6); break;
        case COLOR_DEFAULT : textcolor(7); break;
        default : textcolor(7);
    }
}

int CheckPosition(int indbanqx, int indbanqy, int posplayerx, int posplayery)
{
    return ((indbanqx == posplayerx )&&(indbanqy == posplayery));
}

void ChangeCouleurJoueurMatrice(t_player* tab_players, int nb_player, int banqx, int banqy)
{
    int i;
    for(i=0; i<nb_player; i++)
    {
        if(CheckPosition(banqx, banqy, tab_players[i].position.x, tab_players[i].position.y)==1)
        {
            CouleurTexte(tab_players[i].color);
            break;
        }else CouleurTexte(COLOR_DEFAULT);
    }
}

void AfficheWithPlayers(t_banquise* banquise, t_player* tab_player, int nb_players)
{
    t_sol** matrice = (*banquise).matrice; //récupère la matrice de la banquise
    int N = (*banquise).taille;

    printf("la banquise a boug%c !\n", 130);

    int i, j;
    for(i=0; i<N; i++)
    {
        for(j=0; j<N; j++)
        {
            //présentation "esthetique" de chaque valeur de la matrice
            if(j%N == 0) printf("\n|");
            ChangeCouleurJoueurMatrice(tab_player, nb_players, j, i);
            printf("% d", matrice[i][j]);
            if(j%N == N-1) printf(" |");
        }
    }
    printf("\n");
}
