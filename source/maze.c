#include "maze.h"
#include "config.h"

#include <stdlib.h>

typedef enum
{
    SPACE = 0,
    WALL = 1
} Tile;

typedef struct
{
    int x;
    int y;
} Position;

static Tile maze[GRID_SIZE][GRID_SIZE];

void initialiseMaze(void)
{
    //need at least a 3x3 grid for an entrance and exit
    if (GRID_SIZE < 3)
        return;

    for (int y = 0; y < GRID_SIZE; y++)
    {
        for (int x = 0; x < GRID_SIZE; x++)
        {
            maze[y][x] = WALL;
        }
    }

    bool visited[GRID_SIZE][GRID_SIZE] = {false};

    Position stack[GRID_SIZE * GRID_SIZE];
    int stackSize = 0;

    stack[stackSize++] = (Position){
    ENTRANCE_MARKER_X,
    ENTRANCE_MARKER_Y
    };
    
    visited[ENTRANCE_MARKER_Y][ENTRANCE_MARKER_X] = true;
    maze[ENTRANCE_MARKER_Y][ENTRANCE_MARKER_X] = SPACE;

    //possible movement directions
    const int dx[] = {0, 0, -2, 2};
    const int dy[] = {-2, 2, 0, 0};

    // Randomized depth-first search carves passages between cells two squares apart.
    while (stackSize > 0)
    {
        Position current = stack[stackSize - 1];

        Position neighbours[4];
        int neighbourCount = 0;

        for (int i = 0; i < 4; i++)
        {
            int nx = current.x + dx[i];
            int ny = current.y + dy[i];

            if (nx > 0 && nx < GRID_SIZE - 1 &&
                ny > 0 && ny < GRID_SIZE - 1 &&
                !visited[ny][nx])
            {
                neighbours[neighbourCount++] = (Position){nx, ny};
            }
        }

        if (neighbourCount == 0)
        {
            stackSize--;
            continue;
        }

        Position next = neighbours[rand() % neighbourCount];

        int wallX = (current.x + next.x) / 2;
        int wallY = (current.y + next.y) / 2;

        maze[wallY][wallX] = SPACE;
        maze[next.y][next.x] = SPACE;

        visited[next.y][next.x] = true;
        stack[stackSize++] = next;
    }

    //ensure exit is open
    maze[EXIT_MARKER_Y][EXIT_MARKER_X] = SPACE;
    maze[EXIT_MARKER_Y][EXIT_MARKER_X - 1] = SPACE;
    maze[EXIT_MARKER_Y][EXIT_MARKER_X - 2] = SPACE;
}

bool isWall(int row, int col)
{
    return row < 0 || row >= GRID_SIZE || col < 0 || col >= GRID_SIZE || maze[row][col];
}