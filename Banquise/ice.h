#include <stdio.h>
#include <stdlib.h>

#include "affichage.h"

/******* STRUCTURES *******/

typedef struct
{
    t_vector vect;
    t_pos position;
    int is_moving;
    int player_source;
} t_ice;

/******* PROTOTYPES *******/

//Ice
void GenerateRandomIce(t_banquise* banquise);       // Place un glacon aléatoirement dans la matrice
t_ice* InitIce(t_player* player);                   // Initialise un glaçon

//Fonctions aux de deplacement
int verif_exit_board_ice(int x, int y, int size_board);                             // VERIFIE SI LE GLACON EST SUR LE POINT DE SE DEPLACER EN DEHORS DU PLATEAU DE JEU
int verif_player_in_pos(int x, int y, t_player *arr_player, int nb_player);         // CHERCHE L'ID DU JOUEUR SE SITUANT DANS LA CASE ENTREE EN PARAMETRE
void kill_by_ice(int x, int y, int id_killer, t_player *arr_player, int nb_player); // PERMET DE GERER LA COLLISION ENTE UN GLACON ET UN JOUEUR

//Spring
t_spring* WhichSpringIsIt(t_banquise* board, int headx, int heady); // Cherche quel ressort le glacon a touché
void RotationSpringIce(t_ice* ice, t_spring* spring);               // Oriente le glacon quand il touche un ressort

// marteau
t_hammer* WhichHammerIsIt(t_banquise* board, int headx, int heady);                                             // Cherche quel marteau le glacon a touché
void StopIceHammer(t_ice* ice, t_hammer* hammer);                                                               // Stoppe un glacon si la le socle est derriere sa tete
int RotationStateHammerMovement(t_ice* ice, t_hammer* hammer);                                                  // Trouve quel sens de rotation le marteau doit tourner
void ChangeIceVector(t_ice* ice, t_hammer* hammer, int rotationstate);                                          // Change le vecteur du glacon selon les parametres du marteau
void InteractionHammer(t_ice* ice, t_hammer* hammer, t_banquise* banquise, t_player* arr_player, int nb_player);// Joue les interactions entre le marteau et le glacon

// Displacement
void displacement_ice(t_ice *ice, t_banquise *board, t_player *arr_player, int nb_player);  // PERMET DE GERER LE DEPLACEMENT DU GLACON ET SES EVENTUELLES COLLISIONS



















