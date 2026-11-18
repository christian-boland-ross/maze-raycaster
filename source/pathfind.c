#include "pathfind.h"
#include "robot.h"

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