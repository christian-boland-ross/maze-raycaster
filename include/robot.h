#ifndef ROBOT_H
#define ROBOT_H

typedef struct robot
{
    int x;
    int y;
    int orientation;
} Robot;

void updateRobot(Robot* r); // find the next step in solving the maze and move the robot.

void forward(Robot* r); // move forward to the next square in the direction the robot is facing. If there is a maze wall in front of the robot it does not move.
void left(Robot* r); // turn the robot direction left (anti-clockwise) by 90 degrees, while remaining in the same position.
void right(Robot* r); // turn the robot direction right (clockwise) by 90 degrees, while remaining in the same position.
bool atMarker(Robot* r); // return true if the robot is on the exit marker, otherwise false.
bool canMoveForward(Robot* r); // return true if the robot can move forward as there is no maze wall in front of it. Return false otherwise.

#endif