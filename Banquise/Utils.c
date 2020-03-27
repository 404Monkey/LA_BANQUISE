#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "Utils.h"

// BENJAMIN - RETOURNE AU HASARD UN NOMBRE ENTRE LES DEUX PARAMETRES - O(1)

int RandomInt(int rmin, int rmax)
{
    return rand() % (rmax - rmin) + rmin;
}

// BENJAMIN - CHANGE LA COULEUR - O(1)

void textcolor(int color)
{
    HANDLE h=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h,color);
}
