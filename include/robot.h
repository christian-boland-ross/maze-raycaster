#ifndef ROBOT_H
#define ROBOT_H

typedef enum
{
    SOUTH = 0,
    EAST = 1,
    NORTH = 2,
    WEST = 3
} Orientation;

typedef struct robot
{
    int x;
    int y;
    Orientation orientation;
} Robot;

void updateRobot(Robot* r);
void forward(Robot* r);
void left(Robot* r);
void right(Robot* r);
bool atMarker(Robot* r);
bool canMoveForward(Robot* r);

#endif