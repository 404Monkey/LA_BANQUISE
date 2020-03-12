#include <stdio.h>
#include <stdlib.h>

#include "banquise.h"


void creerMatriceBanquise(int taille, t_sol** matrice)
{
    int i, j;
    for(i=0; i<taille; i++)
    {
        for(j=0; j<taille; j++)
        {
            if(i<WATER_LIMIT || j<WATER_LIMIT || i>=MATRIX_SIZE - WATER_LIMIT || j>=MATRIX_SIZE - WATER_LIMIT)
            {
                matrice[i][j] = WATER;
            }
            else matrice[i][j] = PACKED_ICE;
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
    t_sol** matrice_banquise; // matrice de la banquise
    int i;

    matrice_banquise = malloc(sizeof(t_sol *) * MATRIX_SIZE);
    for(i=0; i<MATRIX_SIZE; i++)
        matrice_banquise[i]= malloc(MATRIX_SIZE * sizeof(t_sol));

    creerMatriceBanquise(MATRIX_SIZE, matrice_banquise); //matrice de taille*taille BANQUISE

    //STRUCT t_banquise

    t_banquise* banquise = malloc(sizeof(t_banquise)); // creation et affectation pour la banquise
    (*banquise).matrice = matrice_banquise;
    (*banquise).taille = MATRIX_SIZE;

    return banquise;
}


void afficheMatrice(t_banquise* banquise)
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
            printf("% d", matrice[i][j]);
            if(j%N == N-1) printf(" |");
        }
    }
    printf("\n");
}

