#include <stdio.h>
#include <stdlib.h>

#define MATRIX_SIZE 8
#define WATER_LIMIT 2


typedef enum {WATER, PACKED_ICE, PLAYER, ICE, ROCK} t_sol;

typedef struct
{
    int taille;
    t_sol** matrice;
} t_banquise;


void creerMatriceBanquise(int taille, t_sol** matrice); //retourne une matrice de BANQUISE
t_banquise* initBanquise(void); // initialise une banquise en demandant la taille à l'utilisateur et en utilisant la fonction ci-dessus
void afficheMatrice(t_banquise* banquise); // affiche "esthetiquement la matrice d'une bannquise
