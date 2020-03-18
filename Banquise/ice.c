#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "ice.h"


void GenerateRandomIce(t_banquise* banquise)
{
    int b_size = (*banquise).banquise_size;
    t_ground** matrix = (*banquise).matrix;

    int N = b_size - WATER_LIMIT;

    int rx = RandomInt(WATER_LIMIT, N-1);
    int ry = RandomInt(WATER_LIMIT, N-1);

    if(matrix[ry][rx] == PACKED_ICE)
    {
    matrix[ry][rx] = ICE;
    }
}

t_ice* InitIce(t_player* player)
{
    t_ice* ice = malloc(sizeof(t_ice));

    int posx = (*player).position.x;
    int posy = (*player).position.y;
    int playerdx = (*player).vect.dx;
    int playerdy = (*player).vect.dy;
    int playerid = (*player).id;

    (*ice).is_moving = 1;
    (*ice).position.x = posx;
    (*ice).position.y = posy;
    (*ice).vect.dx = playerdx;
    (*ice).vect.dy = playerdy;
    (*ice).player_source = playerid;

    return ice;
}

/************** FONCTIONS AUX DE DEPLACEMENT ****************/


// FONCTION VERIFIANT SI LE GLACON EST SUR LE POINT DE SE DEPLACER EN DEHORS DU PLATEAU DE JEU

int verif_exit_board_ice(int x, int y, int size_board)
{
    if ((x<0)||(y<0)||(x>size_board-1)||(y>size_board-1))
    {
        return 1;                               //retourne vrai si le joueur souhaite se deplacer en dehors du plateau de jeu
    }
    else return 0;                              //sinon retourne 0
}

// FONCTION CHERCHANT L'ID DU JOUEUR SE SITUANT DANS LA CASE ENTREE EN PARAMETRE

int verif_player_in_pos(int x, int y, t_player *arr_player, int nb_player)
{
        int id_player = -1;

    for (int i=0; i<nb_player; i++)                     //parcourt le tableau de joueurs a la recherche du joueur se trouvant a la position entree
    {
        int x_player = arr_player[i].position.x;
        int y_player = arr_player[i].position.y;
        if((x == x_player)&&(y == y_player))
        {
            id_player = i;                              //recupere l'ID du joueur concerne
        }
    }
    if (id_player != -1)                                //condition pour reperer un cas d'erreur
    {
        return id_player;
    }
    else printf("*** ERROR with verif_player_in_pos(int x, int y, t_game *game) \n***");
}

// FONCTION PERMETTANT DE GERER LA COLLISION ENTE UN GLACON ET UN JOUEUR

void kill_by_ice(int x, int y, int id_killer, t_player *arr_player, int nb_player)
{
    int id_victim = verif_player_in_pos(x,y,arr_player,nb_player);
    arr_player[id_victim].death = 1;            //declare le joueur ayant subit la collision comme mort
    arr_player[id_killer].score += 100;         //recompense le joueur ayant inittie la collision avec le glacon
}

void RotationSpringIce(t_ice* ice)
{
    int dx = (*ice).vect.dx;
    int dy = (*ice).vect.dy;

    if(dx == 1 && dy == 0)          // glacon arrive par la gauche
    {
        (*ice).position.x += 1;
        (*ice).position.y += 1;
        (*ice).vect.dx = 0;
        (*ice).vect.dy = 1;
    }
    if(dx == 0 && dy == -1)         // glacon arrive par le bas
    {
        (*ice).position.x += 1;
        (*ice).position.y += -1;
        (*ice).vect.dx = 1;
        (*ice).vect.dy = 0;
    }
    if(dx == -1 && dy == 0)         // glacon arrice par la droite
    {
        (*ice).position.x += -1;
        (*ice).position.y += -1;
        (*ice).vect.dx = 0;
        (*ice).vect.dy = -1;
    }
    if(dx == 0 && dy == 1)          // glacon arrice par le haut
    {
        (*ice).position.x += -1;
        (*ice).position.y += 1;
        (*ice).vect.dx = -1;
        (*ice).vect.dy = 0;
    }
}

// FONCTION PERMETTANT DE GERER LE DEPLACEMENT DU GLACON ET SES EVENTUELLES COLLISIONS

void displacement_ice(t_ice *ice, t_banquise *board, t_player *arr_player, int nb_player)
{
    while((*ice).is_moving == 1)                                                //condition permettant de savoir si le glacon se deplace encore
    {
        int pos_x = (*ice).position.x,
            pos_y = (*ice).position.y,
            new_pos_x = pos_x + (*ice).vect.dx,
            new_pos_y = pos_y + (*ice).vect.dy,
            new_new_pos_x = new_pos_x + (*ice).vect.dx,
            new_new_pos_y = new_pos_y + (*ice).vect.dy;;
        printf("j'ai init un glacon\n");
        if (verif_exit_board_ice(new_pos_x,new_pos_y,(*board).banquise_size))   //vraie si le glacon veut sortir du plateau de jeu
        {
            (*ice).is_moving = 0;                                               //si condition vraie, arrete le deplacement du glacon
        }
        else
        {
            system("cls");
            DisplayWithPlayers(board, arr_player, nb_player);

            int obstacle = (*board).matrix[new_pos_y][new_pos_x];

            switch (obstacle){                                                  //evalue l'obsatacle que va rencontrer le glacon dans son deplacement
                case ROCK:                                                      //si c'est un rocher,
                (*ice).is_moving = 0;                                           //on ne bouge plus le glacon
                break;
                case WATER:                                                     //si c'est de l'eau,
                (*board).matrix[new_pos_y][new_pos_x] = PACKED_ICE;             //la nouvelle case du plateau de jeu occupee par le glacon devient une banquise
                (*board).matrix[pos_y][pos_x] = PACKED_ICE;                     //l'ancienne case du plateau de jeu occupé par le glason se libere (redevient banquise)
                (*ice).is_moving = 0;                                           //on ne bouge plus le glacon
                break;
                case PLAYER:                                                    //si c'est un joueur,
                kill_by_ice(new_pos_x,new_pos_y,(*ice).player_source,arr_player,nb_player);     //on change le score des joueurs concernes
                (*board).matrix[new_pos_y][new_pos_x] = ICE;                    //cette nouvelle case du plateau de jeu est occupee par le glacon
                (*board).matrix[pos_y][pos_x] = PACKED_ICE;                     //l'ancienne case du plateau de jeu occupé par le glason se libere (redevient banquise)
                (*ice).position.x = new_pos_x;                                  //on affecte cette nouvelle position en x au glacon
                (*ice).position.y = new_pos_y;                                  //on affecte cette nouvelle position en y au glacon
                break;
                case FINAL_POINT:                                               //si c'est un point d'arrivee,
                case ICE:                                                       //ou un autre glacon,
                if((verif_exit_board_ice(new_new_pos_x,new_new_pos_y,(*board).banquise_size)) || ((*board).matrix[new_new_pos_y][new_new_pos_x] == ROCK)) //vraie si dans 2 deplacements, la position du glacon est hors plateau de jeu ou sur un rocher
                {
                    (*ice).is_moving = 0;                                       //si condition vraie, on ne bouge plus le glacon
                }
                else                                                            //sinon le glacon peu continuer a se deplacer
                {
                    (*ice).position.x = new_pos_x;                              //on affecte cette nouvelle position en x au glacon
                    (*ice).position.y = new_pos_y;                              //on affecte cette nouvelle position en y au glacon
                    displacement_ice(ice,board,arr_player,nb_player);           //on rapelle recursivement la fonction avec les parametres ainsi modifies
                    (*ice).is_moving = 0;                                       //on casse le bouclage (while) pour rendre uniquement effectif, le depacement du glacon dans l'appel recursive
                }
                break;
                case PACKED_ICE:                                                //si c'est de la banquise,
                (*board).matrix[new_pos_y][new_pos_x] = ICE;                    //cette nouvelle case du plateau de jeu est occupee par le glacon
                (*board).matrix[pos_y][pos_x] = PACKED_ICE;                     //l'ancienne case du plateau de jeu occupé par le glason se libere (redevient banquise)
                (*ice).position.x = new_pos_x;                                  //on affecte cette nouvelle position en x au glacon
                (*ice).position.y = new_pos_y;                                  //on affecte cette nouvelle position en y au glacon
                break;
                case SPRING:
                (*board).matrix[pos_y][pos_x] = PACKED_ICE;
                RotationSpringIce(ice);
            default:
            printf("ERROR with displacement_ice(t_ice *ice, t_banquise *board, t_player *arr_player, int nb_player) \n");
            }
        }
    }
}
