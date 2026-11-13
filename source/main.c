#include "graphics.h"
#include "render2d.h"
#include "render3d.h"
#include "config.h"
#include "maze.h"
#include "robot.h"

int main(void)
{
    setWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    initialiseMaze();
    Robot robot;
    initialiseRobot(&robot, 0, 0, 1); // x, y, orientation
    
    //main game loop
    while(true)
    {
        clear();

        draw3DWorld(&robot);

        draw2DWorld();
        drawRobot(&robot);

        sleep(100);

        if(atMarker(&robot))
        {
            break;
        }
        updateRobot(&robot);
    }

    drawString("Maze Solved.", WINDOW_WIDTH/2 - 30, WINDOW_HEIGHT/2);

    return 0;
}