#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#include "ice.h"

/******* ICE *******/

// BENJAMIN - GENERE ALEATOIREMENT DES GLACONS DANS LA MATRICE - O(1)

void GenerateRandomIce(t_banquise* banquise)
{
    int b_size = (*banquise).banquise_size;
    t_ground** matrix = (*banquise).matrix;

    int N = b_size - WATER_LIMIT;

    int rx = RandomInt(WATER_LIMIT, N-1);   // indices au hasard entre là où commence la banquise et où elle se termine
    int ry = RandomInt(WATER_LIMIT, N-1);

    if(matrix[ry][rx] == PACKED_ICE)
    {
        matrix[ry][rx] = ICE;
    }
}

// BENJAMIN - INITIALISE UN GLACON - O(1)

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

/******* DEPLACEMENT AUXILIAIRE GLACON *******/

//HENINTSOA - FONCTION VERIFIANT SI LE GLACON EST SUR LE POINT DE SE DEPLACER EN DEHORS DU PLATEAU DE JEU - O(1)

int verif_exit_board_ice(int x, int y, int size_board)
{
    if ((x<0)||(y<0)||(x>size_board-1)||(y>size_board-1))
    {
        return 1;   //retourne vrai si le joueur souhaite se deplacer en dehors du plateau de jeu
    }
    else return 0;  //sinon retourne 0
}

//HENINTSOA - FONCTION CHERCHANT L'ID DU JOUEUR SE SITUANT DANS LA CASE ENTREE EN PARAMETRE - O(n)

int verif_player_in_pos(int x, int y, t_player *arr_player, int nb_player)
{
    int id_player = -1;

    for (int i=0; i<nb_player; i++)                 //parcourt le tableau de joueurs a la recherche du joueur se trouvant a la position entree
    {
        int x_player = arr_player[i].position.x;
        int y_player = arr_player[i].position.y;

        if((x == x_player)&&(y == y_player))
        {
            id_player = i;                          //recupere l'ID du joueur concerne
        }
    }

    if (id_player != -1)                            //condition pour reperer un cas d'erreur
    {
        return id_player;
    }
    else
    {
        printf("*** ERROR with verif_player_in_pos(int x, int y, t_game *game) \n***");
        return id_player;
    }
}

//HENINTSOA - FONCTION PERMETTANT DE GERER LA COLLISION ENTE UN GLACON ET UN JOUEUR - O(1)

void kill_by_ice(int x, int y, int id_killer, t_player *arr_player, int nb_player)
{
    int id_victim = verif_player_in_pos(x,y,arr_player,nb_player);

    arr_player[id_victim].death = 1;    //declare le joueur ayant subit la collision comme mort
    arr_player[id_killer].score += 100; //recompense le joueur ayant initie la collision avec le glacon
}

//HENINTSOA - FONCTION VERIFIANT SI UN GLACON VEUT S'ENTASSER AVEC UN AUTRE / D'AUTRES GLACON(S) SUR UN ROCHER - O(1)

int verif_ice_heap(int x,int y, t_banquise *board)
{
    if((*board).matrix[y][x] == ROCK )          //verifie si dans la trajectoie du glacon il y a cet alignement contigu precis: glacon et rocher
    {
        return 1;
    }
    else return 0;
}

/******** SPRING ********/

// BENJAMIN - VERIFIE QUEL RESSORT A ETE TOUCHE - O(n)

t_spring* WhichSpringIsIt(t_banquise* board, int headx, int heady)
{
    int i;
    t_spring* spring = malloc(sizeof(t_spring));

    for(i=0; i<4; i++)
    {
        spring = &(*board).arrspring[i];
        if ((*spring).position.x == headx && (*spring).position.y == heady) // Vérifie si les indices corresponde avec un ressort existant
        {
            break;
        }
    }

    return spring;
}

// BENJAMIN - CHANGE LE VECTEUR D'UN GLACON SELON LE RESSORT - O(1)

void RotationSpringIce(t_ice* ice, t_spring* spring)
{
    int dx = (*ice).vect.dx;
    int dy = (*ice).vect.dy;
    int card = (*spring).where;

    switch(card)
    {   // On a décidé d'orienter les ressorts vers le point final quel que soit le vecteur du glacon
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

// BENJAMIN - VERIFIE QUEL MARTEAU A ETE TOUCHE - O(n)

t_hammer* WhichHammerIsIt(t_banquise* board, int headx, int heady)
{
    int i;
    t_hammer* hammer = malloc(sizeof(t_hammer));

    for(i=0; i<4; i++)
    {
        hammer = &(*board).arrhammer[i];
        if ((*hammer).head.x == headx && (*hammer).head.y == heady) // Vérifie si les indices correspondent avec un marteau existant
        {
            break;
        }
    }

    return hammer;
}

// BENJAMIN - STOPPE UN GLACON SI LE SOCLE D'UN MARTEAU EST DERRIERE SA TETE - O(1)

void StopIceHammer(t_ice* ice, t_hammer* hammer)
{
    int dx = (*ice).vect.dx;
    int dy = (*ice).vect.dy;
    t_hammerstate hammerstate = (*hammer).state;

    if  // Si le socle du marteau est derrière sa tete, on stoppe le glacon
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

// BENJAMIN - CALCULE LE SENS DE ROTATION DU MARTEAU - O(1)

int RotationStateHammerMovement(t_ice* ice, t_hammer* hammer)
{
    int dx = (*ice).vect.dx;
    int dy = (*ice).vect.dy;
    t_hammerstate hammerstate = (*hammer).state;

    int rotationstate;

    switch(hammerstate)
    {   // rotationstate = 1 pour sens Horaire 0 pour anti-horaraire
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

// BENJAMIN - CHANGE LE VECTEUR D'UN GLACON - O(1)

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

//BENJAMIN - JOUE LES ANIMATIONS DU MARTEAU PUIS CHANGE LE VECTEUR DU GLACON - O(1)

void InteractionHammer(t_ice* ice, t_hammer* hammer, t_banquise* banquise, t_player* arr_player, int nb_player)
{
    int rotationstate = RotationStateHammerMovement(ice, hammer);

    ChangeIceVector(ice, hammer, rotationstate);

    int i;
    for(i=0; i<3; i++)  // 3 car un marteau fait 3/4 de tour
    {
        t_hammerstate hammerstate = (*hammer).state;
        (*banquise).matrix[(*hammer).head.y][(*hammer).head.x] = PACKED_ICE;

        if(rotationstate == 1)      // Change la position de la tete selon le sens de rotation et affiche chaque etat
        {
            if(hammerstate == TOP)
            {
                (*hammer).head.x += 1;
                (*hammer).head.y += 1;
                (*hammer).state = RIGHT;
            }
            if(hammerstate == RIGHT)
            {
                (*hammer).head.x += -1;
                (*hammer).head.y += 1;
                (*hammer).state = BOTTOM;
            }
            if(hammerstate == BOTTOM)
            {
                (*hammer).head.x += -1;
                (*hammer).head.y += -1;
                (*hammer).state = LEFT;
            }
            if(hammerstate == LEFT)
            {
                (*hammer).head.x += 1;
                (*hammer).head.y += -1;
                (*hammer).state = TOP;
            }
        }
        if(rotationstate == 0)
        {
            if(hammerstate == TOP)
            {
                (*hammer).head.x += -1;
                (*hammer).head.y += 1;
                (*hammer).state = LEFT;
            }
            if(hammerstate == LEFT)
            {
                (*hammer).head.x += 1;
                (*hammer).head.y += 1;
                (*hammer).state = BOTTOM;
            }
            if(hammerstate == BOTTOM)
            {
                (*hammer).head.x += 1;
                (*hammer).head.y += -1;
                (*hammer).state = RIGHT;
            }
            if(hammerstate == RIGHT)
            {
                (*hammer).head.x += -1;
                (*hammer).head.y += -1;
                (*hammer).state = TOP;
            }
        }
        (*banquise).matrix[(*hammer).head.y][(*hammer).head.x] = HAMMER_HEAD;

        system("cls");
        DisplayWithColors(banquise, arr_player, nb_player);
        Sleep(300);
    }
}

/******* DISPLACEMENT *******/

//HENINTSOA - FONCTION S'OCCUPANT DU CAS OU UN GLACON RENCONTRE DE L'EAU - O(1)

void case_WATER(t_banquise *board, int pos_x, int pos_y, int new_pos_x, int new_pos_y)
{
    (*board).matrix[new_pos_y][new_pos_x] = PACKED_ICE;             //la nouvelle case du plateau de jeu occupee par le glacon devient une banquise
    (*board).matrix[pos_y][pos_x] = PACKED_ICE;                     //l'ancienne case du plateau de jeu occupé par le glacon se libere (redevient banquise)
}

//HENINTSOA - FONCTION S'OCCUPANT DU CAS OU UN GLACON RENCONTRE UN JOUEUR - O(n)

void case_PLAYER(t_ice *ice, t_banquise *board, t_player *arr_player, int nb_player, int pos_x, int pos_y, int new_pos_x, int new_pos_y)
{
    kill_by_ice(new_pos_x,new_pos_y,(*ice).player_source,arr_player,nb_player);     //on change le score et la variable mort des joueurs concernes
    (*board).matrix[new_pos_y][new_pos_x] = ICE;                    //cette nouvelle case du plateau de jeu est occupee par le glacon
    (*board).matrix[pos_y][pos_x] = PACKED_ICE;                     //l'ancienne case du plateau de jeu occupé par le glason se libere (redevient banquise)
    (*ice).position.x = new_pos_x;                                  //on affecte cette nouvelle position en x au glacon
    (*ice).position.y = new_pos_y;                                  //on affecte cette nouvelle position en y au glacon
}

//HENINTSOA - FONCTION VERIFIANT SI LE GLACON NE PEUT PAS SE DEPLACER - O(1)

int case_ICE_verif(t_banquise *board, int new_pos_x, int new_pos_y, int next_new_pos_x, int next_new_pos_y)
{
    if (verif_exit_board_ice(next_new_pos_x,next_new_pos_y,(*board).banquise_size) ||   //vraie si dans 2 deplacements, la position du glacon est hors plateau de jeu
                        verif_ice_heap(next_new_pos_x,next_new_pos_y,board))            //vraie s'il y a entassement de glacons sur un rocher (ou pas)
    return 1;
    else return 0;
}

//HENINTSOA - FONCTION S'OCCUPANT DU CAS OU UN GLACON NE RENCONTRE RIEN (SOIT DE LA BANQUISE) - O(1)

void case_PACKED_ICE(t_ice *ice, t_banquise *board, int pos_x, int pos_y, int new_pos_x, int new_pos_y)
{
    (*board).matrix[new_pos_y][new_pos_x] = ICE;                    //cette nouvelle case du plateau de jeu est occupee par le glacon
    (*board).matrix[pos_y][pos_x] = PACKED_ICE;                     //l'ancienne case du plateau de jeu occupé par le glacon se libere (redevient banquise)
    (*ice).position.x = new_pos_x;                                  //on affecte cette nouvelle position en x au glacon
    (*ice).position.y = new_pos_y;                                  //on affecte cette nouvelle position en y au glacon
}

//HENINTSOA - FONCTION S'OCCUPANT DU CAS OU UN GLACON RENCONTRE DE L'EAU - O(1)

void case_SPRING(t_ice *ice, t_banquise *board, int pos_x, int pos_y, int new_pos_x, int new_pos_y)
{
    (*board).matrix[pos_y][pos_x] = PACKED_ICE;                     //l'ancienne case du plateau de jeu occupé par le glacon se libere (redevient banquise)

    t_spring* spring = malloc(sizeof(t_spring));
    spring = WhichSpringIsIt(board, new_pos_x, new_pos_y);          //cherche quel ressort le glacon a touché

    RotationSpringIce(ice, spring);                                 //change le vecteur du glacon
    (*board).matrix[(*ice).position.y][(*ice).position.x] = ICE;    //cette nouvelle case du plateau de jeu est occupee par le glacon
}

//HENINTSOA - FONCTION S'OCCUPANT DU CAS OU UN GLACON RENCONTRE DE LA TETE D'UN MARTEAU - O(n)

void case_HAMMER_HEAD(t_ice *ice, t_banquise *board, t_player *arr_player, int nb_player, int new_pos_x, int new_pos_y)
{
    t_hammer* hammer = malloc(sizeof(t_hammer));
    hammer = WhichHammerIsIt(board, new_pos_x, new_pos_y);          //cherche quel marteau le glacon a touche

    StopIceHammer(ice, hammer);                                     //stoppe le glacon si le socle eest derriere sa tete
    if((*ice).is_moving == 1)
    {
        InteractionHammer(ice, hammer, board, arr_player, nb_player);//joue les animations du marteau puis change le vecteur du glacon
    }
}

//HENINTSOA - FONCTION S'OCCUPANT DU DEPLACEMENT D'UN GLACON - O(n)

void displacement_ice(t_ice *ice, t_banquise *board, t_player *arr_player, int nb_player)
{
    while((*ice).is_moving == 1)                                                //condition permettant de savoir si le glacon se deplace encore
    {
        int pos_x = (*ice).position.x,
            pos_y = (*ice).position.y,

            dx = (*ice).vect.dx,
            dy = (*ice).vect.dy,

            new_pos_x = pos_x + dx,
            new_pos_y = pos_y + dy,

            next_new_pos_x = new_pos_x + dx,
            next_new_pos_y = new_pos_y + dy;;

        if (verif_exit_board_ice(new_pos_x,new_pos_y,(*board).banquise_size))   //vraie si le glacon veut sortir du plateau de jeu
        {
            (*ice).is_moving = 0;                                               //si condition vraie, arrete le deplacement du glacon
        }
        else
        {
            system("cls");
            DisplayWithColors(board, arr_player, nb_player);

            int obstacle = (*board).matrix[new_pos_y][new_pos_x];

            switch (obstacle){                                                      //evalue l'obsatacle que va rencontrer le glacon dans son deplacement
                case ROCK :                                                         //si c'est un rocher
                case HAMMER_PLINTH :                                                //ou le socle d'un marteau,
                    (*ice).is_moving = 0;                                           //on ne bouge plus le glacon
                break;

                case WATER :                                                        //si c'est de l'eau,
                    case_WATER(board,pos_x,pos_y,new_pos_x,new_pos_y);              //on fait les changements necessaires
                    (*ice).is_moving = 0;                                           //on ne bouge plus le glacon
                break;

                case PLAYER :                                                       //si c'est un joueur,
                    case_PLAYER(ice,board,arr_player,nb_player,pos_x,pos_y,new_pos_x,new_pos_y);    //on fait les actions et changements necessaires
                break;

                case FINAL_POINT :                                                  //si c'est un point d'arrivee,
                    (*board).matrix[pos_y][pos_x] = PACKED_ICE;                     //l'ancienne case du plateau de jeu occupé par le glason se libere (redevient banquise)
                    (*ice).is_moving = 0;                                           //on ne bouge plus le glacon
                break;

                case PACKED_ICE :                                                   //si c'est de la banquise,
                    case_PACKED_ICE(ice,board,pos_x,pos_y,new_pos_x,new_pos_y);     //on fait les actions et changements necessaires
                break;

                case SPRING :                                                       //si c'est un ressort,
                    case_SPRING(ice,board,pos_x,pos_y,new_pos_x,new_pos_y);         //on fait les actions et changements necessaires
                break;

                case HAMMER_HEAD :                                                  //si c'est une tete de marteau
                    case_HAMMER_HEAD(ice,board,arr_player,nb_player,new_pos_x,new_pos_y); //on fait les actions et changements necessaires
                break;

                case ICE :                                                          //si c'est un autre glacon,
                    if(case_ICE_verif(board,new_pos_x,new_pos_y,next_new_pos_x,next_new_pos_y)) //verifie s'il est impossible pour le glacon de se deplacer
                    {
                        (*ice).is_moving = 0;                                       //si condition vraie, on ne bouge plus le glacon
                    }
                    else                                                            //sinon le glacon peu continuer a se deplacer
                    {
                        (*ice).position.x = new_pos_x;                              //on affecte cette nouvelle position en x au glacon
                        (*ice).position.y = new_pos_y;                              //on affecte cette nouvelle position en y au glacon
                        displacement_ice(ice,board,arr_player,nb_player);           //on rapelle recursivement la fonction avec les parametres ainsi modifies
                        (*ice).is_moving = 0;                                       //on casse le bouclage (while) pour rendre uniquement effectif le depacement du glacon dans l'appel recursive
                    }
                break;

            default:
            printf("ERROR with displacement_ice(t_ice *ice, t_banquise *board, t_player *arr_player, int nb_player) \n");
            }
        }
    }
}
