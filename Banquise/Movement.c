#include <stdio.h>
#include <stdlib.h>

#include "Movement.h"

/************** FONCTIONS AUX DE DEPLACEMENT ****************/


// FONCTION QUI S'OCCUPE DU DEPLACMENT EN Y

void displacement_y(t_player *player, int displacement)
{
    int y_new =((*player).position.y)+displacement;     //la nouvelle position du joueur en Y
    (*player).position.y = y_new;                       //affecte cette nouvelle position au joueur => le joueur monte ou descend
    (*player).vect.dx = 0;                              //change la composante du vecteur deplacement en x
    (*player).vect.dy = displacement;                   //change la composante du vecteur deplacement en y
}

// FONCTION QUI S'OCCUPE DU DEPLACMENT EN X

void displacement_x(t_player *player, int displacement)
{
    int x_new=((*player).position.x)+displacement;      //la nouvelle position du joueur en X
    (*player).position.x = x_new;                       //affecte cette nouvelle position au joueur => le joueur se déplace a gauche ou a droite
    (*player).vect.dx = displacement;                   //change la composante du vecteur deplacement en x
    (*player).vect.dy = 0;                              //change la composante du vecteur deplacement en y
}

// FONCTION EFFECTUANT UN DEPLACEMENT TEMPORAIRE

void primary_displacement_player(t_player* player, char touch)
{
    switch (touch){                                     //effectue le déplacement selon la touche choisie par le joueur
        case 'z':
        case 'Z':
        displacement_y(player,-1);
        break;
        case 's':
        case 'S':
        displacement_y(player,1);
        break;
        case 'q':
        case 'Q':
        displacement_x(player,-1);
        break;
        case 'd':
        case 'D':
        displacement_x(player,1);
        break;
    default:
    printf("ERROR with displacement_player(t_player player, t_board game_board) \n");
    }
}

// FONCTION VERIFIANT SI LE JOUEUR EST SUR LE POINT DE QUITTER LE PLATEAU DE JEU

int verif_exit_board(int x, int y, int size_board)
{
    if ((x<0)||(y<0)||(x>size_board-1)||(y>size_board-1))
    {
        printf("Deplacement impossible, veuillez reessayer.\n");
        return 1;                               //retourne vrai si le joueur souhaite se deplacer en dehors du plateau de jeu
    }
    else return 0;                              //sinon retourne 0
}

// FONCTION VERIFIANT SI LE JOUEUR EST SUR LE POINT DE SE DEPLACER DANS UNE CASE OCCUPEE

int verif_player_board(int x, int y,t_banquise *board)
{
    int case_board = (*board).matrix[y][x];
     if ((case_board == PLAYER) || (case_board == ROCK) || (case_board == SPRING) || (case_board == HAMMER_HEAD) || (case_board == HAMMER_PLINTH))
    {
        printf("Deplacement impossible, veuillez reessayer.\n");
        return 1;                               //retourne vrai si le joueur souhaite se deplacer dans une case occupee par un autre joueur
    }
    else return 0;                              //sinon retourne 0
}

// FONCTION VERIFIANT SI LE JOUEUR NE PEUT PAS SE DEPLACER SUR LA CASE QU'IL SOUHAITE

int verif_displacement(t_player *player, t_banquise *board)    //verifie si le joueur veut se déplacer hors du plateau de jeu ou si une case est occupé (par un autre joueur ou une rocher)
{
    int size_board = (*board).banquise_size;
    int x = (*player).position.x,
        y = (*player).position.y;

    if (verif_exit_board(x,y,size_board))
    {
        return 1;                               //retourne vrai si le déplacement est impossible
    }
    else if(verif_player_board(x,y,board))
        {
            return 1;                           //retourne vrai si le déplacement est impossible
        }
    else return 0;                              //retourne faux si le déplacement est possible
}

//  FONCTION VERIFIANT SI LE JOUEUR MEURT EN VOULANT EFFECTUANT SON DEPLACEMENT

int verif_player_death(t_player *player, int x, int y, t_banquise *board)
{
    int case_board = (*board).matrix[y][x];
    if (case_board == WATER)                    //retourne vrai si le joueur souhaite se deplacer dans l'eau
    {
        (*player).death = 1;                    //declare le joueur comme mort
        return 1;
    }
    else return 0;
}

//  FONCTION VERIFIANT VERS QUELLE TYPE DE CASE LE JOUEUR VEUT SE DEPLACER

void verif_interaction_player(t_player *player, t_banquise *board, t_player *arr_player, int nb_player)
{
    int x = (*player).position.x,
        y = (*player).position.y;
    int case_board = (*board).matrix[y][x];
    if (case_board == FINAL_POINT)              //verifie si le joueur est arrive sur la case final
    {
        (*player).win = 1;                      //change son boolen "win" si c'est le cas
        (*player).score += 1000;                //lui attribue le score qu'il merite si c'est le cas
    }
    if (case_board == ICE)
    {
        t_ice *ice = InitIce(player);
        displacement_ice(ice,board,arr_player,nb_player);
        free(ice);
    }
}

/*********** FONCTION PRINCIPALE DE DEPLACEMENT *************/


void displacement_player(t_player *player, t_banquise *board, t_player *arr_player, int nb_player)
{
    char touch;
    int death = (*player).death;
    if (death != 1)
    {
        do{
            touch = getchar();
            printf("Votre deplacement (z,q,s ou d): ");
            scanf("%c", &touch);
        }while ((touch!='z')&&(touch!='s')&&(touch!='q')&&(touch!='d')&&(touch!='Z')&&(touch!='S')&&(touch!='Q')&&(touch!='D'));    //verifie si c'est bien une touche de deplacement

        int pos_x = (*player).position.x,
            pos_y = (*player).position.y;

        primary_displacement_player(player,touch);                          //affecte (possiblement de maniere temporaire) au joueur la position souhaité

        if(verif_displacement(player,board))                                //si condition vraie, le joueur ne peut pas faire le deplacement
        {
            (*player).position.x = pos_x;                                       //reaffecte l'ancienne position en x du joueur
            (*player).position.y = pos_y;                                       //reaffecte l'ancienne position en y du joueur
            displacement_player(player,board,arr_player,nb_player);                                  //relance la demande de deplacment pour ce joueur
        }
        else                                                                //sinon, le joueur peut effectuer le deplacement
        {
            int new_pos_x = (*player).position.x,                               //recupere la nouvelle position en x du joueur
                new_pos_y = (*player).position.y;                               //recupere la nouvelle position en y du joueur
            (*board).matrix[pos_y][pos_x] = PACKED_ICE;                         //libere l'ancienne case du plateau de jeu occupé par le joueur
            if (verif_player_death(player,new_pos_x,new_pos_y,board) != 1)  //vrai si le joueur est vivant, sinon, le declare le comme mort
            {
                verif_interaction_player(player,board,arr_player,nb_player);
                (*board).matrix[new_pos_y][new_pos_x] = PLAYER; //indique que la nouvelle case du plateau de jeu occupé par le joueur est occupé par un joueur
            }
        }

    }
}
