#include <stdio.h>
#include <stdlib.h>

#include "Utils.h"

int RandomInt(int rmin, int rmax)
{
    return rand() % (rmax - rmin) + rmin;
}
