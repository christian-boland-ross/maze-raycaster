#include "robot.h"
#include "config.h"
#include "maze.h"

//right-hand wall following guides the robot through the generated maze
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
            left(r);

            if (canMoveForward(r))
            {
                forward(r);
            }
            else
            {
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
            case SOUTH: r->y++; break;
            case EAST: r->x++; break;
            case NORTH: r->y--; break;
            case WEST: r->x--; break;
        }
    }
}

void left(Robot* r)
{
    r->orientation = (Orientation)((r->orientation + 3) % 4);
}

void right(Robot* r)
{
    r->orientation = (Orientation)((r->orientation + 1) % 4);
}

bool atMarker(Robot* r)
{
    return r->x == EXIT_MARKER_X && r->y == EXIT_MARKER_Y;
}

bool canMoveForward(Robot* r) 
{
    int nextX = r->x;
    int nextY = r->y;

    switch (r->orientation)
    {
        case SOUTH: nextY++; break;
        case EAST: nextX++; break;
        case NORTH: nextY--; break;
        case WEST: nextX--; break;
    }

    if (nextX < 0 || nextX >= GRID_SIZE || nextY < 0 || nextY >= GRID_SIZE)
    {
        return false;
    }

    return !isWall(nextY, nextX);
}