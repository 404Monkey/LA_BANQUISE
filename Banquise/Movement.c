#include <stdio.h>
#include <stdlib.h>

#include "Movement.h"

/************** FONCTIONS AUX DE DEPLACEMENT ****************/

void displacement_y(t_player *player, int displacement)
{
    int y_new =((*player).position.y)+displacement;     //la nouvelle position du joueur en Y
    (*player).position.y = y_new;                       //affecte cette nouvelle position au joueur => le joueur monte ou descend
    (*player).vect.dx = 0;                              //change la composante du vecteur deplacement en x
    (*player).vect.dy = displacement;                   //change la composante du vecteur deplacement en y
}

void displacement_x(t_player *player, int displacement)
{
    int x_new=((*player).position.x)+displacement;      //la nouvelle position du joueur en X
    (*player).position.x = x_new;                       //affecte cette nouvelle position au joueur => le joueur se déplace a gauche ou a droite
    (*player).vect.dx = displacement;                   //change la composante du vecteur deplacement en x
    (*player).vect.dy = 0;                              //change la composante du vecteur deplacement en y
}

/*********** FONCTION PRINCIPALE DE DEPLACEMENT *************/

void primary_displacement_player(t_player* player, char touch) //affecte au joueur la position souhaité
{
    switch (touch){
        case 'z':
        displacement_y(player,-1);
        break;
        case 's':
        displacement_y(player,1);
        break;
        case 'q':
        displacement_x(player,-1);
        break;
        case 'd':
        displacement_x(player,1);
        break;
    default:
    printf("ERROR with displacement_player(t_player player, t_board game_board) \n");
    }
}

int verif_exit_board(int x, int y, int size_board)
{
    if ((x<0)||(y<0)||(x>size_board-1)||(y>size_board-1))
    {
        printf("Deplacement impossible, veuillez reessayer.\n");
        return 1;                       //retourne vrai si le joueur souhaite se deplacer en dehors du plateau de jeu
    }
    else return 0;                      //sinon retourne 0
}

int verif_player_board(int x, int y,t_banquise *board)
{
    int case_board = (*board).matrix[y][x];
     if ((case_board == PLAYER) || (case_board == ROCK))
    {
        printf("Deplacement impossible, veuillez reessayer.\n");
        return 1;                       //retourne vrai si le joueur souhaite se deplacer dans une case occupee par un autre joueur
    }
    else return 0;                      //sinon retourne 0
}


int verif_displacement(t_player *player, t_banquise *board)    //verifie si le joueur veut se déplacer hors du plateau de jeu ou si une case est occupé (par un autre joueur ou une rocher)
{
    int size_board = (*board).banquise_size;
    int x = (*player).position.x,
        y = (*player).position.y;

    if (verif_exit_board(x,y,size_board))
    {
        return 1;                       //retourne vrai si le déplacement est impossible
    }
    else if(verif_player_board(x,y,board))
        {
            return 1;                   //retourne vrai si le déplacement est impossible
        }
    else return 0;                      //retourne faux si le déplacement est possible
}

int verif_player_death(t_player *player, int x, int y, t_banquise *board)
{
    int case_board = (*board).matrix[y][x];
    if (case_board == WATER)            //retourne vrai si le joueur souhaite se deplacer dans l'eau
    {
        (*player).death = 1;            //declare le joueur comme mort
        printf("Tu es mort gros con ;p.");
        return 1;
    }
    else return 0;
}

void verif_player_won(t_player *player, int x, int y, t_banquise *board)
{
    int case_board = (*board).matrix[y][x];
    if (case_board == FINAL_POINT)            //retourne vrai si le joueur souhaite se deplacer dans l'eau
    {
        (*player).win = 1;                    //declare le joueur comme mort
        printf("Tu as gagné! Bravo BG ;D.");
        //return 1;
    }
    //else return 0;
}

void displacement_player(t_player *player, t_banquise *board)
{
    char touch;
    int death = (*player).death;
    if (death != 1)
    {
        do{
            touch = getchar();
            printf("Votre deplacement (z,q,s ou d): ");
            scanf("%c", &touch);
            switch (touch){
            case 'Z':
            touch='z';
            break;
            case 'S':
            touch='s';
            break;
            case 'Q':
            touch='q';
            break;
            case 'D':
            touch='d';
            break;                    //convertit les majuscules en minuscules
        }
        }while ((touch!='z')&&(touch!='s')&&(touch!='q')&&(touch!='d'));    //verifie si c'est bien une touche de deplacement

        int pos_x = (*player).position.x,
            pos_y = (*player).position.y;

        primary_displacement_player(player,touch);        //affecte (possiblement de maniere temporaire) au joueur la position souhaité

        if(verif_displacement(player,board))              //si condition vraie, le joueur ne peut pas faire le deplacement
        {
            (*player).position.x = pos_x;                       //reaffecte l'ancienne position en x du joueur
            (*player).position.y = pos_y;                       //reaffecte l'ancienne position en y du joueur
            displacement_player(player,board);                  //relance la demande de deplacment pour ce joueur
        }
        else                                              //sinon, le joueur peut effectuer le deplacement
        {
            int new_pos_x = (*player).position.x,               //recupere la nouvelle position en x du joueur
                new_pos_y = (*player).position.y;               //recupere la nouvelle position en y du joueur
            (*board).matrix[pos_y][pos_x] = PACKED_ICE;        //libere l'ancienne case du plateau de jeu occupé par le joueur
            if (verif_player_death(player,new_pos_x,new_pos_y,board) != 1)          //vrai si le joueur est vivant, sinon le declare le comme mort
            {
                (*board).matrix[new_pos_y][new_pos_x] = PLAYER;//indique que la nouvelle case du plateau de jeu occupé par le joueur est occupé par un joueur
            }
            verif_player_won(player,new_pos_x,new_pos_y,board);
        }

    }
}

void RespawnPlayer(t_player* player, t_banquise* banquise)
{
    if((*player).death == 1)
    {
            printf("%s t'es mort\n", (*player).name);
            (*player).position.x = (*player).start_point.x;
            (*player).position.y = (*player).start_point.y;
            (*player).death =0;

            ImplementPlayerMatrix_aux(banquise, player);

            (*player).score -= 100;
    }
}
