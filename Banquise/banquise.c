/************************************************************************
**************************   Banquise.c   *******************************
************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "banquise.h"


/******* INITIALISATION BANQUISE *******/

// BENJAMIN - INITIALISE UNE MATRICE DE T_GROUND - O(n²)

void InitMatrixBanquise(int b_size, t_ground** matrix)
{
    int i, j;
    for(i=0; i<b_size; i++)
    {
        for(j=0; j<b_size; j++)
        {
            if((MATRIX_SIZE/2 - 2<i && i<MATRIX_SIZE/2 + 2) && (MATRIX_SIZE/2 - 2<j && j<MATRIX_SIZE/2 + 2))
            {
                matrix[i][j] = WATER;
            }
            else if(i<WATER_LIMIT || j<WATER_LIMIT || i>=MATRIX_SIZE - WATER_LIMIT || j>=MATRIX_SIZE - WATER_LIMIT)  // rempli les contours de la matrice d'eau
            {
                matrix[i][j] = WATER;
            }
            else matrix[i][j] = PACKED_ICE;
        }
    }
}

// BENJAMIN - IMPLEMENTE LE POINT D'ARRIVE AU MILIEU D'UNE MATRICE - O(1)

void ImplementFinalPointMatrix(t_ground** matrix, int nb_size)
{
    int N = nb_size/2;          // On met la point final au milieu de la matrice
    matrix[N][N] = FINAL_POINT;
}


/***** SPRING *****/

// BENJAMIN - CREE UN RESSORT  - O(1)

t_spring* CreateSpring()
{
    t_spring* spring = malloc(sizeof(t_spring));

    (*spring).position.x = 0;
    (*spring).position.y = 0;
    (*spring).where = NORTH;

    return spring;
}

// BENJAMIN - CREE LE TABLEAU DE RESSORT - O(n)

void CreateArrSpring(t_spring* arrspring)
{
    int N = MATRIX_SIZE/2;                          // Milieu de la matrice
    int i;
    for(i=0; i<4; i++)                              // On veut 4 ressorts
    {
        arrspring[i] = *CreateSpring();
        switch(i)
        {
            case 0 :                                // Ressort WEST
                arrspring[i].position.x = SPRING_GAP;
                arrspring[i].position.y = N;
                arrspring[i].where = WEST;
                break;

            case 1 :                                // Ressort EAST
                arrspring[i].position.x = MATRIX_SIZE - SPRING_GAP -1;
                arrspring[i].position.y = N;
                arrspring[i].where = EAST;
                break;

            case 2 :                                // Ressort NORTH
                arrspring[i].position.x = N;
                arrspring[i].position.y = SPRING_GAP;
                arrspring[i].where = NORTH;
                break;

            case 3 :                                // Ressort SOUTH
                arrspring[i].position.x = N;
                arrspring[i].position.y = MATRIX_SIZE - SPRING_GAP - 1;
                arrspring[i].where = SOUTH;
                break;
        }
    }
}

// BENJAMIN - IMPLEMENTE LES RESSORTS DANS LA MATRICE - O(n)

void ImplementSpringMatrix(t_ground** matrix, t_spring* arrspring)
{
    int i;
    int posx, posy;
    for(i=0; i<4; i++)
    {
        posx = arrspring[i].position.x;
        posy = arrspring[i].position.y;

        matrix[posy][posx] = SPRING;    // on met SPRING dans la matrice aux positions des differents ressorts
    }
}


/******* ROCHER *******/

// BENJAMIN - VERIFIE S'IL Y'A UN ELEMENT PERTUBATEUR AUTOUR D'UNE CASE - O(1)

int CheckAround(t_ground** matrix, int x, int y)
{
    int ret = 0;

    if(!(x == 0 || y == 0 || x == MATRIX_SIZE-1 || y == MATRIX_SIZE-1)) // Ici on veut pas de rocher aux contours de la matrice
    {
        for(int i = x-1; i <= x+1; i++)
        {
            for(int j = y-1; j <= y+1; j++)
            {
                if  // S'il y a un element perturbateur autour (marteau, ressort ou point final) on ajoute 1 à ret
                (
                    matrix[j][i] == SPRING ||
                    matrix[j][i] == FINAL_POINT ||
                    matrix[j][i] == HAMMER_PLINTH ||
                    matrix[j][i] == HAMMER_HEAD
                )
                ret += 1;
            }
        }
    }

    if(ret > 0)
    {
        return 1;
    } else return 0;
}

// BENJAMIN - IMPLEMENTE LES ROCHERS DANS LA MATRICES - O(n*p²)

void ImplementRockMatrix(t_ground** matrix, int nb_size)
{
    int nb_rocks = MATRIX_SIZE * MATRIX_SIZE / 20;          // On définit le nombre de rochers selon la taille de la matrice (ici 5% des elements la matrice sont des rochers
    int posx, posy;

    for(int i=0; i<nb_rocks; i++)
    {
        posx = RandomInt(0, MATRIX_SIZE-1);
        posy = RandomInt(0, MATRIX_SIZE-1);
        int is_it_ok = CheckAround(matrix, posx, posy);

        while((!(matrix[posy][posx] == WATER) && !(matrix[posy][posx] == PACKED_ICE)) || is_it_ok)  // On chercher une autre place si l'element courant n'est pas de l'eau, pas de la banquise ou qu'il y'ai un element autour
        {
            posx = RandomInt(0, MATRIX_SIZE-1);
            posy = RandomInt(0, MATRIX_SIZE-1);
            is_it_ok = CheckAround(matrix, posx, posy);
        }
        matrix[posy][posx] = ROCK;
    }
}


/******* ICE MELTING *******/

// BENJAMIN - VERIFIE S'IL Y'A DE L'EAU AUTOUR D'UNE CASE - O(1)

int CheckWaterAround(t_banquise* banquise, int x, int y)
{
    t_ground** matrix = (*banquise).matrix;

    if  // regarde s'il y a de l'eau autour
    (
        matrix[y-1][x] == WATER ||
        matrix[y][x+1] == WATER ||
        matrix[y+1][x] == WATER ||
        matrix[y][x-1] == WATER
    ) return 1;
    else return 0;
}

// BENJAMIN - VERIFIE S'IL Y'A ENCORE DE LA BANQUISE DANS LA MATRICE - O(n²)

int IsTherePackedIce(t_banquise* banquise)
{
    int N = (*banquise).banquise_size;
    int ind = 0;

    int i, j;
    for(i=0; i<N -1; i++)
    {
        for(j=0; j<N -1; j++)
        {
            if((*banquise).matrix[i][j] == PACKED_ICE)
            {
               ind += 1;    // Compte le nombre de "banquise" dans la matrice
            }
        }
    }
    return ind;
}

// BENJAMIN - GERE LA FONTE DES GLACES - O(n²)

void IceMelting(t_banquise* banquise)
{
    if(IsTherePackedIce(banquise) > 0)
    {
        int N = (*banquise).banquise_size;

        int posx = RandomInt(1, N-2);
        int posy = RandomInt(1, N-2);
        int is_it_ok = CheckWaterAround(banquise, posx, posy);

        while(!((*banquise).matrix[posy][posx] == PACKED_ICE && is_it_ok)) // On veut une position où il y a de la glace et de l'eau juxtaposé
        {
            posx = RandomInt(1, N-2);
            posy = RandomInt(1, N-2);
            is_it_ok = CheckWaterAround(banquise, posx, posy);
        }

        int r = RandomInt(1, 10);

        if(r == 1)  // 10 % de chances que ça fonde
        {
            (*banquise).matrix[posy][posx] = WATER;
        }
    }
    else printf("Y'A PLUS DE BANQUISE ON VA TOUS MOURIIIR !!\n");
}


/******** HAMMER *********/

// BENJAMIN - CREE UN MARTEAU - O(1)

t_hammer* CreateHammer()
{
    t_hammer* hammer = malloc(sizeof(t_hammer));

    (*hammer).plinth.x = 0;
    (*hammer).plinth.y = 0;
    (*hammer).head.x = 0;
    (*hammer).head.y = 0;

    return hammer;
}

// BENJAMIN - CREE LE TABLEAU DES MARTEAUX - O(n)

void CreateArrHammer(t_hammer* arrhammer)
{
    int i;
    for(i=0; i<4; i++)  // On veut 4 marteaux // Ici on a placé les socles et les tetes de telle sorte a ce que le jeu soit plus intéressant
    {
        arrhammer[i] = *CreateHammer();
        switch(i)
        {
            case 0 : arrhammer[i].plinth.x = HAMMER_PLINTH_GAP;                  // MArteau NOrd-OUest
                     arrhammer[i].plinth.y = HAMMER_PLINTH_GAP;
                     arrhammer[i].head.x = arrhammer[i].plinth.x +1;
                     arrhammer[i].head.y = arrhammer[i].plinth.y;
                     arrhammer[i].state = RIGHT;
                     break;

            case 1 : arrhammer[i].plinth.x = MATRIX_SIZE - HAMMER_PLINTH_GAP -1; // MArteau NOrd-est
                     arrhammer[i].plinth.y = HAMMER_PLINTH_GAP;
                     arrhammer[i].head.x = arrhammer[i].plinth.x;
                     arrhammer[i].head.y = arrhammer[i].plinth.y +1;
                     arrhammer[i].state = BOTTOM;
                     break;

            case 2 : arrhammer[i].plinth.x = MATRIX_SIZE - HAMMER_PLINTH_GAP -1; // MArteau SUd-est
                     arrhammer[i].plinth.y = MATRIX_SIZE - HAMMER_PLINTH_GAP -1;
                     arrhammer[i].head.x = arrhammer[i].plinth.x -1;
                     arrhammer[i].head.y = arrhammer[i].plinth.y;
                     arrhammer[i].state = LEFT;
                     break;

            case 3 : arrhammer[i].plinth.x = HAMMER_PLINTH_GAP;                  // MArteau SUd-OUest
                     arrhammer[i].plinth.y = MATRIX_SIZE - HAMMER_PLINTH_GAP -1;
                     arrhammer[i].head.x = arrhammer[i].plinth.x;
                     arrhammer[i].head.y = arrhammer[i].plinth.y -1;
                     arrhammer[i].state = TOP;
                     break;
        }
    }
}

// BENJAMIN - IMPLEMENTE LES MARTEAUX DANS LA MATRICE - O(n)

void ImplementHammerMatrix(t_ground** matrix, t_hammer* arrhammer)
{
    int i, plinthposx, plinthposy, headposx, headposy;
    for(i=0; i<4; i++)
    {
        plinthposx = arrhammer[i].plinth.x;
        plinthposy = arrhammer[i].plinth.y;
        headposx = arrhammer[i].head.x;
        headposy = arrhammer[i].head.y;

        matrix[plinthposy][plinthposx] = HAMMER_PLINTH; // On met le socle du marteau dans la matrice
        matrix[headposy][headposx] = HAMMER_HEAD;       // On met la tete du marteau dans la matrice
    }
}


/******** BANQUISE ********/

// BENJAMIN - INITIALISE UNE BANQUISE - O(1)

t_banquise* InitBanquise()
{
    printf("Bienvenue dans le jeu de la banquise !\n");

    t_ground** banquise_matrix;                                     // matrice de la banquise

    int i;
    banquise_matrix = malloc(sizeof(t_ground *) * MATRIX_SIZE);     // alloue MATRIX_SIZE fois un tableau de t_ground
    for(i=0; i<MATRIX_SIZE; i++)
        banquise_matrix[i]= malloc(MATRIX_SIZE * sizeof(t_ground)); // alloue MATRIX_SIZE fois un t_ground dans chaque tableau alloué precedemment

    InitMatrixBanquise(MATRIX_SIZE, banquise_matrix);               // initialise la matrice
    ImplementFinalPointMatrix(banquise_matrix, MATRIX_SIZE);        // implemente le point d'arrive

    t_spring* arrspring = malloc(sizeof(t_spring) * 4);
    CreateArrSpring(arrspring);                                     // Crée le tableau des ressorts
    ImplementSpringMatrix(banquise_matrix, arrspring);              // implemente les ressorts

    t_hammer* arrhammer = malloc(sizeof(t_hammer) * 4);
    CreateArrHammer(arrhammer);                                     // Crée le tableau des marteaux
    ImplementHammerMatrix(banquise_matrix, arrhammer);              // Implemente les marteaux

    ImplementRockMatrix(banquise_matrix, MATRIX_SIZE);              // Implemente les rochers

    t_banquise* banquise = malloc(sizeof(t_banquise));              // creation et allocation pour la banquise
    (*banquise).matrix = banquise_matrix;
    (*banquise).banquise_size = MATRIX_SIZE;
    (*banquise).arrspring = arrspring;
    (*banquise).arrhammer = arrhammer;

    return banquise;
}
