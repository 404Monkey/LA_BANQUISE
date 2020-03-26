/************************************************************************
**************************   Banquise.h   *******************************
************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "Utils.h"

/******* CONSTANTES *******/

#define MATRIX_SIZE 21      // Taille de la matrice
#define WATER_LIMIT 2       // Ecart de l'eau au contours de la matrice
#define SPRING_GAP 5        // Ecart des ressorts aux contours de la matrice
#define HAMMER_PLINTH_GAP 4 // Ecart socle marteau


/******* STRUCTURES *******/

typedef enum {WATER, PACKED_ICE, PLAYER, ICE, ROCK, SPRING, FINAL_POINT, HAMMER_HEAD, HAMMER_PLINTH} t_ground;  // les differents types de sol dans la matrice

typedef enum {TOP, BOTTOM, LEFT, RIGHT} t_hammerstate;  // Etat d'un marteau

typedef enum {NORTH, EAST, SOUTH, WEST} t_cardinal;

// Type du ressort
typedef struct
{
    t_pos position;         // position d'un ressort
    t_cardinal where;       // position dans la matrice
} t_spring;

// Type du marteau
typedef struct
{
    t_pos plinth;           // position du socle
    t_pos head;             // position de la tete du martaeu
    t_hammerstate state;    // Etat de la tete du marteau
} t_hammer;

// Type de la banquise
typedef struct
{
    int banquise_size;                                          // Taille de la banquise
    t_ground** matrix;                                          // matrice de la banquise
    t_spring* arrspring;                                        // Tableau des ressorts
    t_hammer* arrhammer;                                        // tableau des marteau
} t_banquise;


/******* Prototypes *******/

// Init banquise
void CreateMatrixBanquise(int b_size, t_ground** matrix);           // Initialise une matrice de t_ground
void ImplementFinalPointMatrix(t_ground** matrix, int nb_size);     // Implemente le point d'arrivé au milieu d'une matrice

// Spring
t_spring* CreateSpring();                                           // Créer un ressort
void CreateArrSpring(t_spring* arrspring);                          // Créer le tableau de ressorts
void ImplementSpringMatrix(t_ground** matrix, t_spring* arrspring); // Implémente les ressorts dans la matrice

// Rock
int CheckAround(t_ground** matrix, int x, int y);                   // retourne 1 si il y a un element perturbateur autour des indices retourne 0 sinon
void ImplementRockMatrix(t_ground** matrix, int nb_size);           // Implémente les rochers dans la matrice

// Ice Melting
int CheckWaterAround(t_banquise* banquise, int x, int y);           // retourne 1 s'il y'a de l'eau autour des indices
int IsTherePackedIce(t_banquise* banquise);                         // Vérifie s'il y'a encore de la glace dans la banquise
void IceMelting(t_banquise* banquise);                              // Fais fondre une banquise aléatoirement avec 10% de chances qu'elle fonde

// Hammer
t_hammer* CreateHammer();                                           // Créer un marteau
void CreateArrHammer(t_hammer* arrhammer);                          // Créer le tableau des marteaux
void ImplementHammerMatrix(t_ground** matrix, t_hammer* arrhammer); // Implemente les marteaux dans la matrice

// Banquise
t_banquise* InitBanquise(void);                                     // Initialise un pointeur de t_banquise


