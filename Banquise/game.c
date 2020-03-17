#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "game.h"

t_game* InitGame()
{
    t_game* game = malloc(sizeof(t_game));                                          // créer un t_game* et alloue l'espace associé

    t_banquise* banquise = malloc(sizeof(t_banquise));                              // créer un t_banquise* et alloue l'espace associé
    banquise = InitBanquise();                                                      // Initialise une banquise

    int nb_players;
    do{
    printf("Combien de joueurs voulez-vous pour cette partie? (entre 1 et 4) : ");  // Demande le nombre de joueurs à l'utilisateur
    scanf("%d", &nb_players);
    } while ((nb_players<1)||(nb_players>4));

    t_player *arr_players = malloc(sizeof(t_player)*nb_players);                    // créer un t_player* (tableau de joueurs) et alloue l'espace associé
    CreateArrPlayer(arr_players, nb_players);                                       // Créer le tableau de joueurs

    int* game_ranking = malloc(sizeof(int)*nb_players);

    (*game).banquise = banquise;                                                    // Implementation des valeurs du t_game*
    (*game).arr_player = arr_players;
    (*game).nb_player = nb_players;
    (*game).nb_lap = 1;
    (*game).ranking = game_ranking;

    ImplementPlayerMatrix((*game).banquise, (*game).arr_player, (*game).nb_player); // Implemente les joueurs dans la matrice

    return game;
}

/*********** LANCEMENT DU JEU ************/


/* Foncrion qui permet de choper l'ID du joueur ayant atteint la case d'arrivée
int ranking_player(t_player *arr_player, int nb_player)
{
    int win = 0,
        i = 0;
    while ((win == 0) || (i<nb_player))
    {
        win = arr_player[i].win;
        i += 1;
    }
    return i-1;
}*/

/* FONCTIONS AUXILIERES*/


// FONCTION POUR TRIER UN TABLEAU A 2 DIMENSIONS //

void sort_tab(int tab[4][2], int size_tab)  //ici, le nb de lignes (nb de joueurs maximum) ainsi que le nb de colonnes sont rentre en dur
{
     int temp0,
         temp1;

     for (int i=0; i<size_tab-1; i++)
     {
        for(int j=i+1; j<size_tab; j++)
        {
            if(tab[j][1]>tab[i][1])
            {
                temp0 = tab[i][0];
                temp1 = tab[i][1];
                tab[i][0] = tab[j][0];
                tab[i][1] = tab[j][1];
                tab[j][0] = temp0;
                tab[j][1] = temp1;
            }
        }
     }
}

// FONCTION POUR EFFECTUER LE CLASSEMENT DES JOUEURS //

void sort_ranking(t_game *game)
{
    int sort_player[(*game).nb_player][2];                  //cree un tableau de 2 dimensions (nb-colonnes = 2 et nb-colonnes = nb de joueurs)

    for (int i=0; i<(*game).nb_player; i++)
    {
            sort_player[i][0]=i;                            //inscrit dans la 1er colonne du tableau l'ID de chaque joueur
            sort_player[i][1]=(*game).arr_player[i].score;  //inscrit dans la 2e colonne d
    }

    sort_tab(sort_player,(*game).nb_player);                //fait un tri decroissant (des lignes) du tableur selon le score

    for (int i=0; i<(*game).nb_player; i++)
    {
        (*game).ranking[i]=sort_player[i][0];               //place l'ID des joueurs, trié selon leur score, dans le tableau du "t_game" dedie au classemenr
    }
}

// FONCRION VERIFIANT SI UN JOUEUR EST ARRIVE AU POINT D'ARRIVEE //

int verif_victory(t_game *game)
{
    int nb_player = (*game).nb_player,
        win = 0;

    for (int i=0; i<nb_player; i++)         //verifie si un joueur est arrive a la case final
    {
        if ((*game).arr_player[i].win == 1)
        {
            win = 1;                        //affecte la valeur booleene "vrai" à la variable si condition vraie
        }
    }
    if (win == 1)                           //verification super caca mais ca marche seulement comme ça
    {
      return 1;                             //retourne "vrai" si un joueur est arrive au point d'arrivee
    }
    else return 0;                          //sinon "faux"
}

// TOUR DE JEU //

void PlayLap(t_game* game)
{
    int i;

    if((*game).nb_lap%3 == 1)
    {
        GenerateRandomIce((*game).banquise);
    }

    for(i=0; i<(*game).nb_player; i++)
    {
        //system("cls");                                                              //clear la console
        DisplayWithPlayers((*game).banquise, (*game).arr_player, (*game).nb_player);//Affiche la matrices

        printf("Tour n%c%d\n", 248, (*game).nb_lap);                                //Affiche du numéro de tour
        printf("%s, %c toi de jouer !\n", (*game).arr_player[i].name, 133);         //Affiche quel joueur doit jouer

         //affichage test **                                                       // Si on veut afficher faire avant displacement, le scanf retarde le clear
        printf("P%d_win : %d\n", i+1, (*game).arr_player[i].win);
        printf("P%d_death : %d\n", i+1, (*game).arr_player[i].death);
        printf("P%d_score : %d\n", i+1, (*game).arr_player[i].score);

        displacement_player(&(*game).arr_player[i], (*game).banquise);              //Demande aux joueur de se deplacer
        RespawnPlayer(&(*game).arr_player[i], (*game).banquise);

        if ((*game).arr_player[i].win == 1)
            break;
    }
    (*game).nb_lap += 1;                                                            // Compte le nombre de tour
}

void PlayGame(t_game* game)
{
    int size_tab = (*game).nb_player;

    while(verif_victory(game) == 0)
    {
        //printf("Je boucle car verif_victory = %d ==0 \n", verif_victory(game));
        PlayLap(game);
    }

    //printf("Je ne boucle pas car verif_victory = %d !=0 \n", verif_victory(game));

    sort_ranking(game);                 //effectue le classement des joueurs

    system("cls");
    printf(" ******** FIN DU JEU ******** \n");
    printf("Le vainqueur est %s.\n", (*game).arr_player[(*game).ranking[0]].name);  //affichage du vainqueur
    printf("Voici le classement:");

    for (int i=0; i<size_tab; i++)      //affichage du classement
    {
        int id_player = (*game).ranking[i];
        if (i==0)
        {
            printf("\n%der: %s avec un score de %d points.\n", i+1, (*game).arr_player[id_player].name, (*game).arr_player[id_player].score);
        }
        else
        {
            printf("\n%de: %s avec un score de %d points.\n", i+1, (*game).arr_player[id_player].name, (*game).arr_player[id_player].score);
        }
    }
}
