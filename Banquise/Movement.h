#include <stdio.h>
#include <stdlib.h>

#include "ice.h"

/******* PROTOTYPES *******/

// Déplacement auxiliaire
void displacement_y(t_player *player, int displacement);                    //HENINTSOA - FONCTION QUI S'OCCUPE DU DEPLACMENT EN Y
void displacement_x(t_player *player, int displacement);                    //HENINTSOA - FONCTION QUI S'OCCUPE DU DEPLACMENT EN X
void primary_displacement_player(t_player* player, char touch);             //HENINTSOA - FONCTION EFFECTUANT UN DEPLACEMENT TEMPORAIRE D'UN JOUEUR
int verif_exit_board(int x, int y, int size_board);                         //HENINTSOA - FONCTION VERIFIANT SI LE JOUEUR EST SUR LE POINT DE QUITTER LE PLATEAU DE JEU
int verif_player_board(int x, int y,t_banquise *board);                     //HENINTSOA - FONCTION VERIFIANT SI LE JOUEUR EST SUR LE POINT DE SE DEPLACER DANS UNE CASE OU IL EST IMPOSSIBLE DE S'Y DEPLACER (OCCUPEE OU AUTRE)
int verif_displacement(t_player *player, t_banquise *board);                //HENINTSOA - FONCTION VERIFIANT SI LE JOUEUR NE PEUT PAS SE DEPLACER SUR LA CASE QU'IL SOUHAITE
int verif_player_death(t_player *player, int x, int y, t_banquise *board);  //HENINTSOA - FONCTION VERIFIANT SI LE JOUEUR MEURT EN VOULANT EFFECTUANT SON DEPLACEMENT
void verif_player_won(t_player *player, t_banquise *board);                 //HENINTSOA - FONCTION VERIFIANT VERS QUELLE TYPE DE CASE LE JOUEUR VEUT SE DEPLACER ET AGISSANT EN CONSEQUENCE

// Deplacement
void displacement_player(t_player *player, t_banquise *board, t_player *arr_player, int nb_player); //HENINTSOA - FONCTION QUI S'OCCUPE DU DEPLACEMENT D'UN JOUEUR














