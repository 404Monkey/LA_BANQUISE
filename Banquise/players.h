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
    t_vector vect;    // pour transmettre le vecteur (sens de déplacement) au glacon
    int score;
} t_player;

t_player* CreerJoueur(t_color color, int id); // Creer un joueur
void CreerTabJoueurs_aux(t_player* tab_joueurs, int nb_joueurs); //Creer tableau de joueurs
int CreerTabJoueurs(t_player* tab_joueurs); // créer tableau de joueurs et retourne la taille du tableau
//void AffectePositionJoueursMatrice(t_banquise* banquise, t_player* tab_player, int size_array); // affecte les positions des joueurs

