#include "render3d.h"
#include "graphics.h"
#include "config.h"
#include "robot.h"
#include "maze.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    unsigned char r;
    unsigned char g;
    unsigned char b;
} Pixel;

static Pixel texture[TEXTURE_SIZE][TEXTURE_SIZE];
static bool textureLoaded = false;

static void drawWalls(Robot* r);
static void drawSky(void);
static void drawGround(void);
static void drawColumn(double distance, int x, bool side, int texX);
static bool loadTexture(const char* filename);

void draw3DWorld(Robot* r)
{
    if(!textureLoaded)
    {
        textureLoaded = loadTexture("textures/default/red.ppm");

        if(!textureLoaded)
        {
            printf("Failed to load texture. Exiting.\n");
            exit(1);
        }
    }

    drawSky();
    drawGround();
    drawWalls(r);
}

static void drawWalls(Robot* r)
{
    double angleIncrement = FOV * PI/180 / WINDOW_WIDTH;
    double robotAngle = r->orientation * PI / 2.0 - PI/2.0;
    double rayAngle = robotAngle - FOV * PI/180 / 2.0;

    double robotX = r->x + 0.5; // the + 0.5 starts ray at the center of the robot's square
    double robotY = r->y + 0.5;

    int x = -1;
    while(x < WINDOW_WIDTH)
    {
        x++;
        
        double rayDirX = cos(rayAngle);
        double rayDirY = sin(rayAngle);

        double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1.0 / rayDirX); // avoid division by zero
        double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1.0 / rayDirY);

        int stepX = (rayDirX < 0) ? -1 : 1;
        int stepY = (rayDirY < 0) ? -1 : 1;

        int mapX = r->x;
        int mapY = r->y;

        double sideDistX;
        double sideDistY;

        if(stepX < 0)
            sideDistX = (robotX - mapX) * deltaDistX;
        else
            sideDistX = (mapX + 1.0 - robotX) * deltaDistX;

        if(stepY < 0)
            sideDistY = (robotY - mapY) * deltaDistY;
        else
            sideDistY = (mapY + 1.0 - robotY) * deltaDistY;

        bool side; // 0 for vertical, 1 for horizontal

        // DDA algorithm: https://lodev.org/cgtutor/raycasting.html
        while(!isWall(mapY, mapX))
        {
            if(sideDistX < sideDistY)
            {
                sideDistX += deltaDistX;
                mapX += stepX;
                side = 0;
            }
            else
            {
                sideDistY += deltaDistY;
                mapY += stepY;
                side = 1;
            }
        }

        double distance;
        if(side == 0)
            distance = sideDistX - deltaDistX;
        else
            distance = sideDistY - deltaDistY;

        double wallX;

        if(side == 0)
            wallX = robotY + distance * rayDirY;
        else
            wallX = robotX + distance * rayDirX;

        wallX -= floor(wallX);

        //convert wall position into a texture coordinate.
        int texX = (int)(wallX * TEXTURE_SIZE);

        if(side == 0 && rayDirX > 0)
            texX = TEXTURE_SIZE - texX - 1;

        if(side == 1 && rayDirY < 0)
            texX = TEXTURE_SIZE - texX - 1;

        //correct distance for the fish-eye effect
        distance *= cos(rayAngle - robotAngle);

        // Draw the textured column.
        drawColumn(distance, x, side, texX);

        rayAngle += angleIncrement;
    }
}

static void drawColumn(double distance, int x, bool side, int texX)
{
    if(distance < 0.01)
        distance = 0.01;

    int wallHeight = (int)(WINDOW_HEIGHT / distance) * 0.4;

    int wallTop = (WINDOW_HEIGHT - wallHeight) / 2;
    int wallBottom = (WINDOW_HEIGHT + wallHeight) / 2;

    double brightness = 255.0 / (1.0 + distance * 0.5);

    //darken horizontal wall faces slightly for increased depth perception
    if(side == 1)
        brightness *= 0.7;

    for(int y = wallTop; y < wallBottom; y++)
    {
        if(y < 0 || y >= WINDOW_HEIGHT)
            continue;

        int texY = (y - wallTop) * TEXTURE_SIZE / wallHeight;
        Pixel pixel = texture[texY][texX];

        int r = (int)(pixel.r * brightness / 255.0);
        int g = (int)(pixel.g * brightness / 255.0);
        int b = (int)(pixel.b * brightness / 255.0);

        setRGBColour(r, g, b);
        drawLine(x, y, x, y);
    }
}

static void drawSky(void)
{
    for(int i = 0; i < WINDOW_HEIGHT/2; i++)
    {
        int r = 135 + (120 * i / (WINDOW_HEIGHT/2));
        int g = 205 + (50 * i / (WINDOW_HEIGHT/2));
        int b = 235 + (20 * i / (WINDOW_HEIGHT/2));
        setRGBColour(r, g, b);
        drawLine(0, i, WINDOW_WIDTH, i);
    }
}

static void drawGround(void)
{
    for(int i = WINDOW_HEIGHT/2; i < WINDOW_HEIGHT; i++)
    {
        int shade = 20 + (80 * (i - WINDOW_HEIGHT/2) / (WINDOW_HEIGHT/2));

        setRGBColour(shade, shade, shade);
        drawLine(0, i, WINDOW_WIDTH, i);
    }
}

static bool loadTexture(const char* filename)
{
    FILE* file = fopen(filename, "rb");

    if(file == NULL)
    {
        printf("Could not load texture: %s\n", filename);
        return false;
    }

    int width, height, maxValue;

    if(fscanf(file, "P6 %d %d %d", &width, &height, &maxValue) != 3)
    {
        fclose(file);
        return false;
    }

    //consume the whitespace after the PPM header.
    fgetc(file);

    if(width != TEXTURE_SIZE || height != TEXTURE_SIZE || maxValue != 255)
    {
        printf("Texture must be 64x64 with max value 255\n");
        fclose(file);
        return false;
    }

    for(int y = 0; y < TEXTURE_SIZE; y++)
    {
        for(int x = 0; x < TEXTURE_SIZE; x++)
        {
            if(fread(&texture[y][x], sizeof(Pixel), 1, file) != 1)
            {
                fclose(file);
                return false;
            }
        }
    }

    fclose(file);

    return true;
}