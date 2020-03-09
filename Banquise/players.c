#include <stdio.h>
#include <stdlib.h>

#include "players.h"

t_player* CreerJoueur(t_color color, int id)
{
    t_player* player = malloc(sizeof(t_player));

    char* name = malloc(sizeof(char));
    printf("Joueur %d, Veuillez rentrer votre nom : ", id+1);
    scanf("%s", name);
    (*player).name = name;

    (*player).color = color;
    (*player).id = id;
    (*player).position.x = (*player).position.y = 0;
    (*player).vect.dx = (*player).vect.dy = 0;
    (*player).score = 0;

    return player;
}

void CreerTabJoueurs_aux(t_player* tab_joueurs, int nb_joueurs)
{
    for (int i=0; i<nb_joueurs; i++)
    {
        tab_joueurs[i] = *CreerJoueur(i,i);
        tab_joueurs[i].position.x = i; //Init les positions de x pour chaque joueurs
    }
}

int CreerTabJoueurs(t_player* tab_joueurs){
    int nb_joueurs;

    do{
    printf("Combien de joueurs voulez-vous pour cette partie? (entre 1 et 4) : ");
    scanf("%d", &nb_joueurs);
    } while ((nb_joueurs<1)||(nb_joueurs>4));

    tab_joueurs = malloc(sizeof(t_player)*nb_joueurs); // MEEEEHHHHH cest legit ??

    CreerTabJoueurs_aux(tab_joueurs, nb_joueurs);

    return nb_joueurs;
    }

/************** FONCTIONS AUX DE DEPLACEMENT ****************/

void deplacement_y(t_player *player, int displacement)
{
    int y_new =(player->position.y)+displacement; //la nouvelle position du joueur en Y
    player->position.y = y_new;                       //affecte cette nouvelle position au joueur => le joueur monte ou descend
}

void deplacement_x(t_player *player, int displacement)
{
    int x_new=((*player).position.x)+displacement;     //la nouvelle position du joueur en X
    (*player).position.x = x_new;                       //affecte cette nouvelle position au joueur => le joueur se déplace a gauche ou a droite
}

/*********** FONCTION PRINCIPALE DE DEPLACEMENT *************/

void deplacement_player (t_player* player)
{
    char touch = getchar();
    printf("test1");

    while ( (touch!='z') && (touch!='s') && (touch!='q') && (touch!='d')){
    printf("Votre deplacement (Z,S,Q ou D): ");
    printf("test2");
    scanf("%c", &touch);
    printf("test3");
    }

printf("test4");

    switch (touch){
        case 'z':
        deplacement_y(player,-1);
        break;
        switch (touch)
        case 's':
        deplacement_y(player,1);
        break;
        switch (touch)
        case 'q':
        deplacement_x(player,-1);
        break;
        case 'd':
        deplacement_x(player,1);
        break;
    default:
    printf("ERROR with deplacement_player(t_player player, t_board game_board) \n");
    }
}
