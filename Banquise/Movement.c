#include <stdio.h>
#include <stdlib.h>

#include "Movement.h"

/************** FONCTIONS AUX DE DEPLACEMENT ****************/


//HENINTSOA - FONCTION QUI S'OCCUPE DU DEPLACMENT EN Y - O(1)

void displacement_y(t_player *player, int displacement)
{
    (*player).position.y += displacement;               //affecte la nouvelle position au joueur => le joueur monte ou descend
    (*player).vect.dx = 0;                              //change la composante du vecteur deplacement en x
    (*player).vect.dy = displacement;                   //change la composante du vecteur deplacement en y
}

//HENINTSOA - FONCTION QUI S'OCCUPE DU DEPLACMENT EN X - O(1)

void displacement_x(t_player *player, int displacement)
{
    (*player).position.x += displacement;               //affecte la nouvelle position au joueur => le joueur se déplace a gauche ou a droite
    (*player).vect.dx = displacement;                   //change la composante du vecteur deplacement en x
    (*player).vect.dy = 0;                              //change la composante du vecteur deplacement en y
}

//HENINTSOA - FONCTION EFFECTUANT UN DEPLACEMENT TEMPORAIRE D'UN JOUEUR - O(1)

void primary_displacement_player(t_player* player, char touch)
{
    switch (touch){ //effectue le déplacement selon la touche choisie par le joueur
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

//HENINTSOA - FONCTION VERIFIANT SI LE JOUEUR EST SUR LE POINT DE QUITTER LE PLATEAU DE JEU - O(1)

int verif_exit_board(int x, int y, int size_board)
{
    if ((x<0) || (y<0) || (x>size_board-1) || (y>size_board-1))
    {
        printf("Deplacement impossible, veuillez reessayer.\n");
        return 1;                               //retourne vrai si le joueur souhaite se deplacer en dehors du plateau de jeu
    }
    else return 0;                              //sinon retourne 0
}

//HENINTSOA - FONCTION VERIFIANT SI LE JOUEUR EST SUR LE POINT DE SE DEPLACER DANS UNE CASE OU IL EST IMPOSSIBLE DE S'Y DEPLACER (OCCUPEE OU AUTRE) - O(1)

int verif_board(int x,int y, int dx, int dy, t_banquise *board)
{
    int next_x = x + dx,
        next_y = y + dy,

        case_board = (*board).matrix[y][x],
        next_case_board = (*board).matrix[next_y][next_x];

    if(
        (case_board == PLAYER)                 //verifie si la case est occupee par un joueur
        || (case_board == ROCK)                //verifie si la case est occupee par un rocher
        || (case_board == SPRING)              //verifie si la case est occupee par un ressort
        || (case_board == HAMMER_HEAD)         //verifie si la case est occupee par une tete de marteau
        || (case_board == HAMMER_PLINTH)       //verifie si la case est occupee par un socle de marteau
        || ((case_board == ICE) && (next_case_board == ICE                  //verifie si la case voulue par le deplacement est un glacon suivi d'un autre,
                                    || next_case_board == ROCK              //d'un rocher
                                    || next_case_board == HAMMER_HEAD       //ou bien d'une partie de marteau
                                    || next_case_board == HAMMER_PLINTH))
    )
    {
        printf("Deplacement impossible, veuillez reessayer.\n");
        return 1;                               //retourne vrai si le deplacement est impossible
    }
    else return 0;                              //sinon retourne faux
}

//HENINTSOA - FONCTION VERIFIANT SI LE JOUEUR NE PEUT PAS SE DEPLACER SUR LA CASE QU'IL SOUHAITE - O(1)

int verif_displacement(t_player *player, t_banquise *board)
{
    int size_board = (*board).banquise_size;
    int x = (*player).position.x,
        y = (*player).position.y,
        dx = (*player).vect.dx,
        dy = (*player).vect.dy;

    if (verif_exit_board(x,y,size_board))   //verifie si le joueur veut se déplacer hors du plateau de jeu
    {
        return 1;                           //retourne vrai si le déplacement est impossible
    }
    else if(verif_board(x,y,dx,dy,board))   //verifie si le joueur veut se déplacer dans une case où il ne peut pas se rendre
    {
        return 1;                           //retourne vrai si le déplacement est impossible
    }
    else return 0;                          //retourne faux si le déplacement est possible
}

//HENINTSOA - FONCTION VERIFIANT SI LE JOUEUR MEURT EN VOULANT EFFECTUANT SON DEPLACEMENT - O(1)

int verif_player_death(t_player *player, int x, int y, t_banquise *board)
{
    int case_board = (*board).matrix[y][x];

    if (case_board == WATER)                    //verifie si le joueur veut se déplacer dans l'eau
    {
        (*player).death = 1;                    //declare le joueur comme mort si c'est le cas
        return 1;                               //retourne vrai si le joueur meurt (en se deplacant dans l'eau)
    }
    else return 0;                              //sinon retourne faux
}

//HENINTSOA - FONCTION VERIFIANT VERS QUELLE TYPE DE CASE LE JOUEUR VEUT SE DEPLACER ET AGISSANT EN CONSEQUENCE - O(1)

void verif_player_interaction(t_player *player, t_banquise *board, t_player *arr_player, int nb_player)
{
    int x = (*player).position.x,
        y = (*player).position.y,
        case_board = (*board).matrix[y][x];

    if (case_board == FINAL_POINT)                          //verifie si le joueur est arrive sur la case final
    {
        (*player).win = 1;                                  //change son boolen "win" si c'est le cas
        (*player).score += 1000;                            //lui attribue le score qu'il merite si c'est le cas
    }
    if (case_board == ICE)
    {
        t_ice *ice = InitIce(player);                       //cree un glacon temporaire pour simuler son deplacement
        displacement_ice(ice,board,arr_player,nb_player);   //implemente ce glacon a la matrice et l'affiche pour chacun de ses deplacements jusqu'a son arret
        free(ice);                                          //detruit le glacon artificiel
    }
}

//HENINTSOA - FONCTION RENDANT EFFECTIF LE DEPLACMENT DU JOUEUR, VERIFIANT ET APPLIQUANT LES ACTIONS/CHANGEMENTS ENGENDRES PAR CELUI-CI - O(1)

void final_displacement(t_player *player, t_banquise *board, t_player *arr_player, int nb_player, int pos_x, int pos_y)
{
    int new_pos_x = (*player).position.x,                               //recupere la nouvelle position en x du joueur
        new_pos_y = (*player).position.y;                               //recupere la nouvelle position en y du joueur

    (*board).matrix[pos_y][pos_x] = PACKED_ICE;                         //libere l'ancienne case du plateau de jeu occupé par le joueur
    if (verif_player_death(player,new_pos_x,new_pos_y,board) != 1)      //vrai si le joueur est vivant, sinon, le declare le comme mort
    {
        verif_player_interaction(player,board,arr_player,nb_player);    //execute une action en fonction de l'objet avec lequel le joueur est entre en interaction
        (*board).matrix[new_pos_y][new_pos_x] = PLAYER;                 //indique que la nouvelle case du plateau de jeu occupé par le joueur est occupé par un joueur
    }
}


/*********** FONCTION PRINCIPALE DE DEPLACEMENT *************/

//HENINTSOA - FONCTION PERMETTANT DE GERER LE DEPLACEMENT D'UN JOUEUR - O(n)

void displacement_player(t_player *player, t_banquise *board, t_player *arr_player, int nb_player)
{
    char touch;
    int death = (*player).death;

    if (death != 1)
    {
        do
            {
                touch = getchar();                              //vide la variable "touch"
                printf("Votre deplacement (z,q,s ou d): ");
                fflush(stdin);
                scanf("%c", &touch);                            //affecte la valeur saisie à la variable "touch"
            }
        while ((touch!='z')&&(touch!='s')&&(touch!='q')&&(touch!='d')&&(touch!='Z')&&(touch!='S')&&(touch!='Q')&&(touch!='D'));    //verifie si c'est bien une touche de deplacement

        int pos_x = (*player).position.x,                                   //sauvegarde de la position initiale en x du joueur
            pos_y = (*player).position.y;                                   //sauvegarde de la position initiale en y du joueur

        primary_displacement_player(player,touch);                          //affecte (possiblement de maniere temporaire) au joueur la position souhaité

        if(verif_displacement(player,board))                                //si condition vraie, le joueur ne peut pas faire le deplacement
        {
            (*player).position.x = pos_x;                                       //reaffecte l'ancienne position en x du joueur
            (*player).position.y = pos_y;                                       //reaffecte l'ancienne position en y du joueur
            displacement_player(player,board,arr_player,nb_player);             //relance la demande de deplacment pour ce joueur
        }
        else                                                                //sinon, le joueur peut effectuer le deplacement
        {
            final_displacement(player,board,arr_player,nb_player,pos_x,pos_y);  //verifie et applique les actions/changements en consequence du deplacement
        }
    }
}
