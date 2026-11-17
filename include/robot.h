#ifndef ROBOT_H
#define ROBOT_H

typedef struct robot
{
    int x;
    int y;
    int orientation; // 0=south, 1=east, 2=north, 3=west
} Robot;

void updateRobot(Robot* r);
void forward(Robot* r);
void left(Robot* r);
void right(Robot* r);
bool atMarker(Robot* r);
bool canMoveForward(Robot* r);

#endif