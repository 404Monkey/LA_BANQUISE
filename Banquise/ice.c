#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#include "ice.h"

/******* ICE *******/

void GenerateRandomIce(t_banquise* banquise)
{
    int b_size = (*banquise).banquise_size;
    t_ground** matrix = (*banquise).matrix;

    int N = b_size - WATER_LIMIT;

    int rx = RandomInt(WATER_LIMIT, N-1);   // indices au hasard entre l� o� commence la banquise et o� elle se termine
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

/******* FONCTIONS AUX DE DEPLACEMENT *******/

int verif_exit_board_ice(int x, int y, int size_board)
{
    if ((x<0)||(y<0)||(x>size_board-1)||(y>size_board-1))
    {
        return 1;                               //retourne vrai si le joueur souhaite se deplacer en dehors du plateau de jeu
    }
    else return 0;                              //sinon retourne 0
}

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

void kill_by_ice(int x, int y, int id_killer, t_player *arr_player, int nb_player)
{
    int id_victim = verif_player_in_pos(x,y,arr_player,nb_player);
    arr_player[id_victim].death = 1;            //declare le joueur ayant subit la collision comme mort
    arr_player[id_killer].score += 100;         //recompense le joueur ayant inittie la collision avec le glacon
}

/******** Spring ********/

t_spring* WhichSpringIsIt(t_banquise* board, int headx, int heady)
{
    int i;
    t_spring* spring = malloc(sizeof(t_spring));
    for(i=0; i<4; i++)
    {
        spring = &(*board).arrspring[i];
        if ((*spring).position.x == headx && (*spring).position.y == heady) // V�rifie si les indices corresponde avec un ressort existant
        {
            break;
        }
    }
    return spring;
}

void RotationSpringIce(t_ice* ice, t_spring* spring)
{
    int dx = (*ice).vect.dx;
    int dy = (*ice).vect.dy;
    int card = (*spring).where;

    switch(card)
    {   // On a d�cid� d'orienter les ressorts vers le point final quel que soit le vecteur du glacon
        case NORTH :
            if(dx == 1 && dy == 0)          // glacon arrive par la gauche
            {
                (*ice).position.x += 1;
                (*ice).position.y += 1;
            }
            if(dx == -1 && dy == 0)         // glacon arrice par la droite
            {
                (*ice).position.x += -1;
                (*ice).position.y += 1;
            }
            if(dx == 0 && dy == 1)          // glacon arrice par le haut
            {
                (*ice).position.y += 2;
            }
            (*ice).vect.dx = 0;
            (*ice).vect.dy = 1;
            break;
        case EAST :
            if(dx == 0 && dy == -1)         // glacon arrive par le bas
            {
                (*ice).position.x += -1;
                (*ice).position.y += -1;
            }
            if(dx == -1 && dy == 0)         // glacon arrice par la droite
            {
                (*ice).position.x += -2;
            }
            if(dx == 0 && dy == 1)          // glacon arrice par le haut
            {
                (*ice).position.x += -1;
                (*ice).position.y += 1;
            }
            (*ice).vect.dx = -1;
            (*ice).vect.dy = 0;
            break;
        case SOUTH :
            if(dx == 1 && dy == 0)          // glacon arrive par la gauche
            {
                (*ice).position.x += 1;
                (*ice).position.y += -1;
            }
            if(dx == 0 && dy == -1)         // glacon arrive par le bas
            {
                (*ice).position.y += -2;
            }
            if(dx == -1 && dy == 0)         // glacon arrice par la droite
            {
                (*ice).position.x += -1;
                (*ice).position.y += -1;
            }
            (*ice).vect.dx = 0;
            (*ice).vect.dy = -1;
            break;
        case WEST :
            if(dx == 1 && dy == 0)          // glacon arrive par la gauche
            {
                (*ice).position.x += 2;
            }
            if(dx == 0 && dy == -1)         // glacon arrive par le bas
            {
                (*ice).position.x += 1;
                (*ice).position.y += -1;
            }
            if(dx == 0 && dy == 1)          // glacon arrice par le haut
            {
                (*ice).position.x += 1;
                (*ice).position.y += 1;
            }
            (*ice).vect.dx = 1;
            (*ice).vect.dy = 0;
            break;
    }
}

/******* HAMMER *******/

t_hammer* WhichHammerIsIt(t_banquise* board, int headx, int heady)
{
    int i;
    t_hammer* hammer = malloc(sizeof(t_hammer));
    for(i=0; i<4; i++)
    {
        hammer = &(*board).arrhammer[i];
        if ((*hammer).head.x == headx && (*hammer).head.y == heady) // V�rifie si les indices correspondent avec un marteau existant
        {
            break;
        }
    }
    return hammer;
}

void StopIceHammer(t_ice* ice, t_hammer* hammer)
{
    int dx = (*ice).vect.dx;
    int dy = (*ice).vect.dy;
    t_hammerstate hammerstate = (*hammer).state;

    if  // Si le socle du marteau est derri�re sa tete, on stoppe le glacon
    (
        (dx == 0 && dy == 1 && hammerstate == TOP) ||
        (dx == 0 && dy == -1 && hammerstate == BOTTOM) ||
        (dx == 1 && dy == 0 && hammerstate == LEFT) ||
        (dx == -1 && dy == 0 && hammerstate == RIGHT)
    )
    {
        (*ice).is_moving = 0;
    }
}

int RotationStateHammerMovement(t_ice* ice, t_hammer* hammer)
{
    int dx = (*ice).vect.dx;
    int dy = (*ice).vect.dy;
    t_hammerstate hammerstate = (*hammer).state;

    int rotationstate;

    switch(hammerstate)
    {                   // rotationstate = 1 pour sens Horaire 0 pour anti-horaraire
        case TOP :      if(dx == 1 && dy == 0) rotationstate = 1;
                        if(dx == -1 && dy == 0) rotationstate = 0;
                        break;
        case BOTTOM :   if(dx == 1 && dy == 0) rotationstate = 0;
                        if(dx == -1 && dy == 0) rotationstate = 1;
                        break;
        case LEFT :     if(dx == 0 && dy == 1) rotationstate = 0;
                        if(dx == 0 && dy == -1) rotationstate = 1;
                        break;
        case RIGHT :    if(dx == 0 && dy == 1) rotationstate = 1;
                        if(dx == 0 && dy == -1) rotationstate = 0;
                        break;
    }

    return rotationstate;
}

void ChangeIceVector(t_ice* ice, t_hammer* hammer, int rotationstate)
{
    int dx = (*ice).vect.dx;
    int dy = (*ice).vect.dy;
    t_hammerstate hammerstate = (*hammer).state;

    if(rotationstate == 1)
    {   // Oriente le vecteur du glacon selon le sens de rotation, son vecteur, et la position de la tete
        if(dx == 1 && dy == 0 && hammerstate == TOP)
        {
            (*ice).vect.dx = 0;
            (*ice).vect.dy = -1;
        }
        if(dx == 0 && dy == 1 && hammerstate == RIGHT)
        {
            (*ice).vect.dx = 1;
            (*ice).vect.dy = 0;
        }
        if(dx == -1 && dy == 0 && hammerstate == BOTTOM)
        {
            (*ice).vect.dx = 0;
            (*ice).vect.dy = 1;
        }
        if(dx == 0 && dy == -1 && hammerstate == LEFT)
        {
            (*ice).vect.dx = -1;
            (*ice).vect.dy = 0;
        }
    }
    else
    {
        if(dx == -1 && dy == 0 && hammerstate == TOP)
        {
            (*ice).vect.dx = 0;
            (*ice).vect.dy = -1;
        }
        if(dx == 0 && dy == -1 && hammerstate == RIGHT)
        {
            (*ice).vect.dx = 1;
            (*ice).vect.dy = 0;
        }
        if(dx == 1 && dy == 0 && hammerstate == BOTTOM)
        {
            (*ice).vect.dx = 0;
            (*ice).vect.dy = 1;
        }
        if(dx == 0 && dy == 1 && hammerstate == LEFT)
        {
            (*ice).vect.dx = -1;
            (*ice).vect.dy = 0;
        }
    }
}

void InteractionHammer(t_ice* ice, t_hammer* hammer, t_banquise* banquise, t_player* arr_player, int nb_player)
{
    int rotationstate = RotationStateHammerMovement(ice, hammer);

    ChangeIceVector(ice, hammer, rotationstate);

    int i;
    for(i=0; i<3; i++)  // 3 car un marteau fait 3/4 de tour
    {
        t_hammerstate hammerstate = (*hammer).state;

        if(rotationstate == 1)      // Change la position de la tete selon le sens de rotation et affiche chaque etat
        {
            if(hammerstate == TOP)
            {
                (*banquise).matrix[(*hammer).head.y][(*hammer).head.x] = PACKED_ICE;
                (*hammer).head.x += 1;
                (*hammer).head.y += 1;
                (*banquise).matrix[(*hammer).head.y][(*hammer).head.x] = HAMMER_HEAD;
                (*hammer).state = RIGHT;
            }
            if(hammerstate == RIGHT)
            {
                (*banquise).matrix[(*hammer).head.y][(*hammer).head.x] = PACKED_ICE;
                (*hammer).head.x += -1;
                (*hammer).head.y += 1;
                (*banquise).matrix[(*hammer).head.y][(*hammer).head.x] = HAMMER_HEAD;
                (*hammer).state = BOTTOM;
            }
            if(hammerstate == BOTTOM)
            {
                (*banquise).matrix[(*hammer).head.y][(*hammer).head.x] = PACKED_ICE;
                (*hammer).head.x += -1;
                (*hammer).head.y += -1;
                (*banquise).matrix[(*hammer).head.y][(*hammer).head.x] = HAMMER_HEAD;
                (*hammer).state = LEFT;
            }
            if(hammerstate == LEFT)
            {
                (*banquise).matrix[(*hammer).head.y][(*hammer).head.x] = PACKED_ICE;
                (*hammer).head.x += 1;
                (*hammer).head.y += -1;
                (*banquise).matrix[(*hammer).head.y][(*hammer).head.x] = HAMMER_HEAD;
                (*hammer).state = TOP;
            }
        }
        if(rotationstate == 0)
        {
            if(hammerstate == TOP)
            {
                (*banquise).matrix[(*hammer).head.y][(*hammer).head.x] = PACKED_ICE;
                (*hammer).head.x += -1;
                (*hammer).head.y += 1;
                (*banquise).matrix[(*hammer).head.y][(*hammer).head.x] = HAMMER_HEAD;
                (*hammer).state = LEFT;
            }
            if(hammerstate == LEFT)
            {
                (*banquise).matrix[(*hammer).head.y][(*hammer).head.x] = PACKED_ICE;
                (*hammer).head.x += 1;
                (*hammer).head.y += 1;
                (*banquise).matrix[(*hammer).head.y][(*hammer).head.x] = HAMMER_HEAD;
                (*hammer).state = BOTTOM;
            }
            if(hammerstate == BOTTOM)
            {
                (*banquise).matrix[(*hammer).head.y][(*hammer).head.x] = PACKED_ICE;
                (*hammer).head.x += 1;
                (*hammer).head.y += -1;
                (*banquise).matrix[(*hammer).head.y][(*hammer).head.x] = HAMMER_HEAD;
                (*hammer).state = RIGHT;
            }
            if(hammerstate == RIGHT)
            {
                (*banquise).matrix[(*hammer).head.y][(*hammer).head.x] = PACKED_ICE;
                (*hammer).head.x += -1;
                (*hammer).head.y += -1;
                (*banquise).matrix[(*hammer).head.y][(*hammer).head.x] = HAMMER_HEAD;
                (*hammer).state = TOP;
            }
        }
        system("cls");
        DisplayWithColors(banquise, arr_player, nb_player);
        Sleep(300);
    }
}

/******* DISPLACEMENT *******/

void displacement_ice(t_ice *ice, t_banquise *board, t_player *arr_player, int nb_player)
{
    while((*ice).is_moving == 1)                                                //condition permettant de savoir si le glacon se deplace encore
    {
        int pos_x = (*ice).position.x,
            pos_y = (*ice).position.y,
            new_pos_x = pos_x + (*ice).vect.dx,
            new_pos_y = pos_y + (*ice).vect.dy,
            new_new_pos_x = new_pos_x + (*ice).vect.dx,
            new_new_pos_y = new_pos_y + (*ice).vect.dy;

        if (verif_exit_board_ice(new_pos_x,new_pos_y,(*board).banquise_size))   //vraie si le glacon veut sortir du plateau de jeu
        {
            (*ice).is_moving = 0;                                               //si condition vraie, arrete le deplacement du glacon
        }
        else
        {
            system("cls");
            DisplayWithColors(board, arr_player, nb_player);

            int obstacle = (*board).matrix[new_pos_y][new_pos_x];

            switch (obstacle){                                                  //evalue l'obsatacle que va rencontrer le glacon dans son deplacement
                case ROCK:                                                      //si c'est un rocher,
                case HAMMER_PLINTH :
                (*ice).is_moving = 0;                                           //on ne bouge plus le glacon
                break;
                case WATER:                                                     //si c'est de l'eau,
                (*board).matrix[new_pos_y][new_pos_x] = PACKED_ICE;             //la nouvelle case du plateau de jeu occupee par le glacon devient une banquise
                (*board).matrix[pos_y][pos_x] = PACKED_ICE;                     //l'ancienne case du plateau de jeu occup� par le glason se libere (redevient banquise)
                (*ice).is_moving = 0;                                           //on ne bouge plus le glacon
                break;
                case PLAYER:                                                    //si c'est un joueur,
                kill_by_ice(new_pos_x,new_pos_y,(*ice).player_source,arr_player,nb_player);     //on change le score des joueurs concernes
                (*board).matrix[new_pos_y][new_pos_x] = ICE;                    //cette nouvelle case du plateau de jeu est occupee par le glacon
                (*board).matrix[pos_y][pos_x] = PACKED_ICE;                     //l'ancienne case du plateau de jeu occup� par le glason se libere (redevient banquise)
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
                (*board).matrix[pos_y][pos_x] = PACKED_ICE;                     //l'ancienne case du plateau de jeu occup� par le glason se libere (redevient banquise)
                (*ice).position.x = new_pos_x;                                  //on affecte cette nouvelle position en x au glacon
                (*ice).position.y = new_pos_y;                                  //on affecte cette nouvelle position en y au glacon
                break;
                case SPRING:
                    (*board).matrix[pos_y][pos_x] = PACKED_ICE;

                    t_spring* spring = malloc(sizeof(t_spring));
                    spring = WhichSpringIsIt(board, new_pos_x, new_pos_y);

                    RotationSpringIce(ice, spring);
                    (*board).matrix[(*ice).position.y][(*ice).position.x] = ICE;
                break;
                case HAMMER_HEAD :
{
                    t_hammer* hammer = malloc(sizeof(t_hammer));
                    hammer = WhichHammerIsIt(board, new_pos_x, new_pos_y);

                    StopIceHammer(ice, hammer);
                    if((*ice).is_moving == 1)
                    {
                        InteractionHammer(ice, hammer, board, arr_player, nb_player);
                    }
}
                    break;
            default:
            printf("ERROR with displacement_ice(t_ice *ice, t_banquise *board, t_player *arr_player, int nb_player) \n");
            }
        }
    }
}
