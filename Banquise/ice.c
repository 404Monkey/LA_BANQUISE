#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "ice.h"

int RandomInt(int rmin, int rmax)
{
    return rand() % (rmax - rmin) + rmin;
}

void GenerateRandomIce(t_banquise* banquise)
{
    int b_size = (*banquise).banquise_size;
    t_ground** matrix = (*banquise).matrix;

    int N = b_size - WATER_LIMIT;

    int rx = RandomInt(WATER_LIMIT, N-1);
    int ry = RandomInt(WATER_LIMIT, N-1);

    if(matrix[ry][rx] == PACKED_ICE)
    {
    matrix[ry][rx] = ICE;
    }
}

t_ice* InitIce(t_player* player)
{
    t_ice* ice = malloc(sizeof(t_ice*));

    int posx = (*player).position.x;
    int posy = (*player).position.y;
    int playerdx = (*player).vect.dx;
    int playerdy = (*player).vect.dy;

    (*ice).is_moving = 1;
    (*ice).position.x = posx;
    (*ice).position.y = posy;
    (*ice).vect.dx = playerdx;
    (*ice).vect.dy = playerdy;
    (*ice).player_source = player;

    return ice;
}

void MoveIce(t_ice* ice, t_banquise* banquise, t_player* player)
{
    int b_size = (*banquise).banquise_size;
    t_ground** matrix = (*banquise).matrix;

    int ice_posx = (*player).position.x;
    int ice_posy = (*player).position.y;

    while((*ice).is_moving == 1)
    {
        if(matrix[ice_posy][ice_posx] == PACKED_ICE)
        {
            (*ice).position.x += (*ice).vect.dx;
            (*ice).position.y += (*ice).vect.dy;
            matrix[(*ice).position.y][(*ice).position.x] = ICE;
        }
    }
}
