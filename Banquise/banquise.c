#include <stdio.h>
#include <stdlib.h>

#include "banquise.h"


void creerMatriceBanquise(int b_size, t_ground** matrix)
{
    int i, j;
    for(i=0; i<b_size; i++)
    {
        for(j=0; j<b_size; j++)
        {
            if(i<WATER_LIMIT || j<WATER_LIMIT || i>=MATRIX_SIZE - WATER_LIMIT || j>=MATRIX_SIZE - WATER_LIMIT)
            {
                matrix[i][j] = WATER;
            }
            else matrix[i][j] = PACKED_ICE;
        }
    }
}


t_banquise* initBanquise()
{
    printf("Bienvenue dans le jeu de la banquise !\n");

    /* TAILLE MATRICE
    // TAILLE : demande à l'urilisateur de saisir la taille du plateau
    printf("Saisir la taille du plateau : ");
    int taille;
    scanf("%d", &taille); */

    //MATRICE :
    t_ground** banquise_matrix; // matrice de la banquise
    int i;

    banquise_matrix = malloc(sizeof(t_ground *) * MATRIX_SIZE);
    for(i=0; i<MATRIX_SIZE; i++)
        banquise_matrix[i]= malloc(MATRIX_SIZE * sizeof(t_ground));

    creerMatriceBanquise(MATRIX_SIZE, banquise_matrix); //matrice de taille*taille BANQUISE

    //STRUCT t_banquise

    t_banquise* banquise = malloc(sizeof(t_banquise)); // creation et affectation pour la banquise
    (*banquise).matrix = banquise_matrix;
    (*banquise).banquise_size = MATRIX_SIZE;

    return banquise;
}


void afficheMatrice(t_banquise* banquise)
{
    t_ground** matrix = (*banquise).matrix; //récupère la matrice de la banquise
    int N = (*banquise).banquise_size;

    printf("la banquise a boug%c !\n", 130);

    int i, j;
    for(i=0; i<N; i++)
    {
        for(j=0; j<N; j++)
        {
            //présentation "esthetique" de chaque valeur de la matrice
            if(j%N == 0) printf("\n|");
            printf("% d", matrix[i][j]);
            if(j%N == N-1) printf(" |");
        }
    }
    printf("\n");
}

