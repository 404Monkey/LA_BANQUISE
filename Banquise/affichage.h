#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "players.h"

/******* PROTOTYPES *******/

void ChangeTextColor(t_color color);                                                        // Change la couleur en fonction d'un t_color
int CheckPosition(int indbanqx, int indbanqy, t_player* player);                            // Vérifie s'il y a un joueur sur les coordonées courants de la matrice retourne 1 si le joueur est vivant et sur les mêmes indices
void ChangeColorPlayerMatrix(t_player* arr_player, int nb_player, int banqx, int banqy);    // Change la couleur si un des joueurs est sur ma coordonnées étudiés
void ChangeColorGroundMatrix(t_ground ground);                                              // Change la couleur pour les sols
void DisplayWithColors(t_banquise* banquise, t_player* arr_player, int nb_players);         // Affiche la matrice avec les couleurs





















