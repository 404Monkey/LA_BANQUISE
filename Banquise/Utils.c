#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "Utils.h"

int RandomInt(int rmin, int rmax)
{
    return rand() % (rmax - rmin) + rmin;
}

void textcolor(int color)
{
HANDLE h=GetStdHandle(STD_OUTPUT_HANDLE);
   SetConsoleTextAttribute(h,color);
}
