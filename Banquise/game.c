#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "game.h"

/******* INITIALISATION *******/

// BENJAMIN - INITIALISE UN JEU - O(n)

t_game* InitGame()
{
    t_game* game = malloc(sizeof(t_game));                                          // créer un t_game* et alloue l'espace associé

    t_banquise* banquise = malloc(sizeof(t_banquise));                              // créer un t_banquise* et alloue l'espace associé
    banquise = InitBanquise();                                                      // Initialise une banquise

    int nb_players;
    do{
    printf("Combien de joueurs voulez-vous pour cette partie? (entre 1 et 4) : ");  // Demande le nombre de joueurs à l'utilisateur
    fflush(stdin);
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

/******* FIN DU JEU *******/


//HENINTSOA - FONCTION POUR TRIER UN TABLEAU A 2 DIMENSIONS - O(n²)

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

//HENINTSOA - FONCTION POUR EFFECTUER LE CLASSEMENT DES JOUEURS - O(2n)

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

//HENINTSOA - FONCRION VERIFIANT SI UN JOUEUR EST ARRIVE AU POINT D'ARRIVEE - O(n)

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

//HENINTSOA - FONCTION PERMETTANT D'ETABLIR ET D'AFFICHER LE CLASSEMENT EN FIN DE JEU - O(n)

void display_end_game(t_game *game)
{
    int size_tab = (*game).nb_player;

    sort_ranking(game);                 //effectue le classement des joueurs

    system("cls");
    printf(" ******** FIN DU JEU ******** \n");
    printf("\nLe vainqueur est %s.\n", (*game).arr_player[(*game).ranking[0]].name);  //affichage du vainqueur
    printf("\nVoici le classement:");

    for (int i=0; i<size_tab; i++)      //affichage du classement
    {
        int id_player = (*game).ranking[i];

        if (i==0)
        {
            printf("\n%der: %s avec un score de %d points.", i+1, (*game).arr_player[id_player].name, (*game).arr_player[id_player].score);
        }
        else
        {
            printf("\n%de : %s avec un score de %d points.", i+1, (*game).arr_player[id_player].name, (*game).arr_player[id_player].score);
        }
    }
}

/******* JEU *******/

//BENJAMIN & HENINTSOA - TOUR DE JEU - O(n)

void PlayLap(t_game* game)
{
    if((*game).nb_lap % 4 == 0)
    {   // Genere un glacon aléatoirement tous les 4 tours
        GenerateRandomIce((*game).banquise);
    }

    for(int i=0; i<(*game).nb_player; i++)
    {
        system("cls");                                                              // clear la console

        IceMelting((*game).banquise);

        DisplayWithColors((*game).banquise, (*game).arr_player, (*game).nb_player); // Affiche la matrice avec les couleurs

        printf("Tour n%c%d\n", 248, (*game).nb_lap);                                // Affiche du numéro de tour
        printf("%s, %c vous de jouer !\n", (*game).arr_player[i].name, 133);        // Affiche quel joueur doit jouer
        printf("Votre score : %d\n", (*game).arr_player[i].score);                  // Affiche le score du joueur

        displacement_player(&(*game).arr_player[i],(*game).banquise,(*game).arr_player,(*game).nb_player);   //Demande aux joueur de se deplacer

        for(int j=0; j<(*game).nb_player; j++)
        {
            RespawnPlayer(&(*game).arr_player[j], (*game).banquise);                // Regarde si un des joueurs est mort et le rescussite
        }

        if ((*game).arr_player[i].win == 1)                                         // Casse la boucle for
            break;
    }

    (*game).nb_lap += 1;                                                            // Compte le nombre de tour
}

// HENINTSOA - JOUE UNE PARTIE - O(n)

void PlayGame(t_game* game)
{
    while(verif_victory(game) == 0)    // boucle le jeu tant que les conditions de fin de jeu ne sont pas verifiees
    {
        PlayLap(game);
    }

    display_end_game(game);             // etablit et affiche le classement des joueurs lorsque le jeu est finie
}
