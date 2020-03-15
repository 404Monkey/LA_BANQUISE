/************************************************************************
**************************   Banquise.h   *******************************
************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#define MATRIX_SIZE 19                                          // Taille de la matrice
#define WATER_LIMIT 2                                           // Ecart ce l'au aux contours de la matrice


typedef enum {WATER, PACKED_ICE, PLAYER, ICE, ROCK, FINAL_POINT} t_ground;

typedef struct
{
    int banquise_size;                                          // Taille de la banquise
    t_ground** matrix;                                          // matrice de la banquise
} t_banquise;

/******* Prototypes *******/

void CreateMatrixBanquise(int b_size, t_ground** matrix);       // Initialise une matrice de t_ground
void ImplementFinalPointMatrix(t_ground** matrix, int nb_size); // Implemente le point d'arrivé au milieu d'une matrice
t_banquise* InitBanquise(void);                                 // Initialise un pointeur de t_banquise
void DisplayMatrix(t_banquise* banquise);                       // Affiche la matrice de la banquise sans couleur

