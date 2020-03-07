#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "players.h"


void textcolor(int color)
{
HANDLE h=GetStdHandle(STD_OUTPUT_HANDLE);
   SetConsoleTextAttribute(h,color);
}

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


void AffectePositionJoueur(t_player* player, int posx, int posy)
{
    (*player).position.x = posx;
    (*player).position.y = posy;
}

void AffectePositionJoueursMatrice(t_banquise* banquise, t_player* tab_players, int size_array)
{
    int i;
    for(i=0; i<size_array; i++)
    {
        //printf("%d\n", tab_players[i].color);
    }
}
