#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "players.h"

/******* PLAYERS *******/

// BENJAMIN - CREE UN JOUEUR

t_player* CreatePlayer(t_color color, int id)
{
    t_player* player = malloc(sizeof(t_player));

    char* name = malloc(sizeof(char));
    printf("Joueur %d, Veuillez rentrer votre nom : ", id);
    scanf("%s", name);
    (*player).name = name;

    (*player).color = color;
    (*player).id = id;
    (*player).position.x = (*player).position.y = 0;
    (*player).start_point.x = (*player).start_point.y = 0;
    (*player).vect.dx = (*player).vect.dy = 0;
    (*player).score = 0;
    (*player).death = 0;
    (*player).win = 0;

    return player;
}

// BENJAMIN - CREE LE TABLEAU DES JOUEURS

void CreateArrPlayer(t_player* arr_player, int nb_player)
{
    for (int i=0; i<nb_player; i++)
    {
        arr_player[i] = *CreatePlayer(i,i+1);
        switch(i)    // Positionne aux coins de la matrice en fonction de l'écart
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

// BENJAMIN - IMPLEMENTE UN JOUEUR DANS LA MATRICE

void ImplementPlayerMatrix_aux(t_banquise* banquise, t_player* player)
{
    int posx = (*player).position.x;
    int posy = (*player).position.y;

    (*banquise).matrix[posy][posx] = PLAYER; // Implemente PLAYER à la position du joueur
}

// BENJAMIN - IMPLEMENTE TOUS LES JOUEURS DANS LA MATRICE

void ImplementPlayerMatrix(t_banquise* banquise, t_player* arr_player, int nb_player)
{
    int i;
    for(i=0; i<nb_player; i++)
    {
        ImplementPlayerMatrix_aux(banquise, &arr_player[i]); // Implemente PLAYER pour tous les joueurs
    }
}

// BENJAMIN - RESSUSCITE UN JOUEUR

void RespawnPlayer(t_player* player, t_banquise* banquise)
{
    if((*player).death == 1)
    {
        system("cls");
        printf("%s t'es mort :/\n", (*player).name);
        printf("- 100 points ;P\n");
        Sleep(500);

        (*player).position.x = (*player).start_point.x;
        (*player).position.y = (*player).start_point.y;
        (*player).death = 0;

        ImplementPlayerMatrix_aux(banquise, player); // Replace le joueur à son point de départ s'il meurt

        (*player).score -= 100;
    }
}
