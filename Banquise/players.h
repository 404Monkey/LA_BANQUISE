#include <stdio.h>
#include <stdlib.h>

#include "banquise.h"

typedef enum {RED, GREEN, BLUE, YELLOW, COLOR_DEFAULT} t_color;

typedef struct
{
    int x;              // position en x
    int y;              // position en y
} t_pos;

typedef struct
{
    int dx;             // deplacement en x
    int dy;             // deplacement en y
} t_vector;

typedef struct
{
    char *name;         // nom
    t_color color;      // couleur du joueur
    int id;             // id du Joueur
    t_pos position;     // coordonnées du joeurs
    t_pos start_point;  // coordonnées du point de depart d'un joueur
    t_vector vect;      // vecteur de deplacement du joueur
    int score;          // score du joueur
    int death;          // 1 s'il est mort 0 s'il est vivant
    int win;            // 1 s'il a gagné 0 sinon
} t_player;

t_player* CreatePlayer(t_color color, int id);                                          // Creer un joueur
void CreateArrPlayer(t_player* arr_player, int nb_player);                              // Creer tableau de joueurs avec les bonnes positions
void ImplementPlayerMatrix_aux(t_banquise* banquise, t_player* player);                 // Implemente PLAYER dans la matrice en fonction de la position d'un joueur
void ImplementPlayerMatrix(t_banquise* banquise, t_player* arr_player, int nb_player);  // Implemente PLAYER dans la matrice pour tous les joueurs

