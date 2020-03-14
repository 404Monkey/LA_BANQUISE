#include <stdio.h>
#include <stdlib.h>

#include "banquise.h"

typedef enum {RED, GREEN, BLUE, YELLOW, COLOR_DEFAULT} t_color;

typedef struct
{
    int x; //position en x
    int y; //position en y
} t_pos;

typedef struct
{
    int dx; // deplacement en x
    int dy; // deplacement en y
} t_vector;

typedef struct
{
    char *name;
    t_color color;
    int id;
    t_pos position;
    t_pos start_point;
    t_vector vect;    // pour transmettre le vecteur (sens de déplacement) au glacon
    int score;
    int death;
    int win;
} t_player;

t_player* CreatePlayer(t_color color, int id); // Creer un joueur
void CreateArrPlayer(t_player* arr_player, int nb_player); //Creer tableau de joueurs
void ImplementPlayerMatrix_aux(t_banquise* banquise, t_player* player);
void ImplementPlayerMatrix(t_banquise* banquise, t_player* arr_player, int nb_player);





