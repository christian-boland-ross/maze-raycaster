#include "robot.h"
#include "config.h"
#include "maze.h"

void initialiseRobot(Robot* r, int x, int y, int orientation)
{
    r->x = x;
    r->y = y;
    r->orientation = orientation;
}

//wall following maze solver algorithm
void updateRobot(Robot* r)
{
    right(r);

    if (canMoveForward(r))
    {
        forward(r);
    }
    else
    {
        left(r);

        if (canMoveForward(r))
        {
            forward(r);
        }
        else
        {
            // Try turning left
            left(r);

            if (canMoveForward(r))
            {
                forward(r);
            }
            else
            {
                // Dead end: turn around
                left(r);
            }
        }
    }
}

void forward(Robot* r)
{
    if(canMoveForward(r)) 
    {
        switch (r->orientation)
        {
            case 0: r->y++; break;
            case 1: r->x++; break;
            case 2: r->y--; break;
            case 3: r->x--; break;
        }
    }
}

void left(Robot* r)
{
    r->orientation = (r->orientation + 3) % 4;
}

void right(Robot* r)
{
    r->orientation = (r->orientation + 1) % 4;
}

bool atMarker(Robot* r)
{
    return r->x == GRID_SIZE - 1 && r->y == GRID_SIZE - 1;
}

bool canMoveForward(Robot* r) 
{
    int nextX = r->x;
    int nextY = r->y;

    switch (r->orientation)
    {
        case 0: nextY++; break;
        case 1: nextX++; break;
        case 2: nextY--; break;
        case 3: nextX--; break;
    }

    if (nextX < 0 || nextX >= GRID_SIZE || nextY < 0 || nextY >= GRID_SIZE)
    {
        return false;
    }

    return !isWall(nextY, nextX);
}