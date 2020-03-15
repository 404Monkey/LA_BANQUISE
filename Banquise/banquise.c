/************************************************************************
**************************   Banquise.c   *******************************
************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "banquise.h"

/***************************************/
/********* BANQUISE FONCTIONS **********/
/***************************************/

void InitMatrixBanquise(int b_size, t_ground** matrix)
{
    int i, j;
    for(i=0; i<b_size; i++)
    {
        for(j=0; j<b_size; j++)
        {
            if(i<WATER_LIMIT || j<WATER_LIMIT || i>=MATRIX_SIZE - WATER_LIMIT || j>=MATRIX_SIZE - WATER_LIMIT)  // rempli les contours de la matrice d'eau
            {
                matrix[i][j] = WATER;
            }
            else matrix[i][j] = PACKED_ICE;
        }
    }
}


void ImplementFinalPointMatrix(t_ground** matrix, int nb_size)
{
    int N = nb_size/2;                                              // Milieu de la matrice
    matrix[N][N] = FINAL_POINT;
}


t_banquise* InitBanquise()
{
    printf("Bienvenue dans le jeu de la banquise !\n");

    /* TAILLE MATRICE                                               // Demander a l'utilisateur la taille de la matrice
    printf("Saisir la taille du plateau : ");
    int taille;
    scanf("%d", &taille); */

    //MATRICE :
    t_ground** banquise_matrix;                                     // matrice de la banquise

    int i;
    banquise_matrix = malloc(sizeof(t_ground *) * MATRIX_SIZE);     // alloue MATRIX_SIZE fois un tableau de t_ground
    for(i=0; i<MATRIX_SIZE; i++)
        banquise_matrix[i]= malloc(MATRIX_SIZE * sizeof(t_ground)); // alloue MATRIX_SIZE fois un t_ground dans chaque tableau alloué precedemment

    InitMatrixBanquise(MATRIX_SIZE, banquise_matrix);               // initialise la matrice
    ImplementFinalPointMatrix(banquise_matrix, MATRIX_SIZE);        // implemente le point d'arrive

    //STRUCT t_banquise
    t_banquise* banquise = malloc(sizeof(t_banquise));              // creation et allocation pour la banquise
    (*banquise).matrix = banquise_matrix;
    (*banquise).banquise_size = MATRIX_SIZE;

    return banquise;
}


void DisplayMatrix(t_banquise* banquise)
{
    t_ground** matrix = (*banquise).matrix;                         // récupère la matrice
    int b_size = (*banquise).banquise_size;                         // récupère la taille de la matrice

    printf("la banquise a boug%c !\n", 130);

    int i, j;
    for(i=0; i<b_size; i++)
    {
        for(j=0; j<b_size; j++)
        {
            if(j%b_size == 0) printf("\n|");
            printf("% d", matrix[i][j]);                            // affiche le t_ground des coordonnées correspondant
            if(j%b_size == b_size-1) printf(" |");
        }
    }
    printf("\n");
}

