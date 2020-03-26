#include <stdio.h>
#include <stdlib.h>

/******* STRUCTURES *******/

//type d'une position
typedef struct
{
    int x;                          // position en x
    int y;                          // position en y
} t_pos;

// type d'un vecteur
typedef struct
{
    int dx;                         // deplacement en x
    int dy;                         // deplacement en y
} t_vector;

//type des couleurs
typedef enum
{
    RED,                            // Couleur du Premier joueur
    GREEN,                          // Couleur du Second joueur
    BLUE,                           // Couleur du Troisieme joueur
    YELLOW,                         // Couleur du Quatrieme joueur
    COLOR_DEFAULT,                  // Couleur de base du terminal
    WATER_COLOR,                    // Couleur de l'eau
    ICE_COLOR,                      // Couleur d'un glaçon
    ROCK_COLOR,                     // Couleur d'un rocher
    SPRING_COLOR,                   // Couleur d'un ressort
    FINAL_POINT_COLOR,              // Couleur du point final
    HAMMER_COLOR                    // Couleur d'un marteau
} t_color;


/******* PROTOTYPES *******/

int RandomInt(int rmin, int rmax);  // Retourne un nombre au hasard entre rmin et rmax
void textcolor(int color);          // Fonction trouvé sur Internet, Permet de changer la couleur d'écriture
