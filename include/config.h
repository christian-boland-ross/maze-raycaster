#ifndef CONFIG_H
#define CONFIG_H

#define PI 3.14159265358979323846

#define FOV 130.0 // Field of view in degrees

#define WINDOW_WIDTH 400
#define WINDOW_HEIGHT 200

#define GRID_SIZE 10
#define GRID_PIXELS 100
#define CELL_SIZE GRID_PIXELS/GRID_SIZE

#define ENTRANCE_MARKER_X 0
#define ENTRANCE_MARKER_Y 1
#define EXIT_MARKER_X (GRID_SIZE - 1)
#define EXIT_MARKER_Y (GRID_SIZE - 2)

#define TEXTURE_SIZE 64

#endif