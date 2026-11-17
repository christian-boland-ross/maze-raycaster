#include "graphics.h"
#include "render2d.h"
#include "render3d.h"
#include "config.h"
#include "maze.h"
#include "robot.h"

#include <time.h>
#include <stdlib.h>

int main(void)
{
    srand((unsigned int)time(NULL));

    setWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    initialiseMaze();
    Robot robot = {
        ENTRANCE_MARKER_X,
        ENTRANCE_MARKER_Y,
        1
    };
    
    //main game loop
    while(true)
    {
        clear();

        draw3DWorld(&robot);

        draw2DWorld();
        drawRobot(&robot);

        sleep(1000);

        if(atMarker(&robot))
        {
            break;
        }
        updateRobot(&robot);
    }

    drawString("Maze Solved.", WINDOW_WIDTH/2 - 30, WINDOW_HEIGHT/2);

    return 0;
}