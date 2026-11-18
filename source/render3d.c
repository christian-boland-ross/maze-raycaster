#include "render3d.h"
#include "graphics.h"
#include "config.h"
#include "robot.h"
#include "maze.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static TextureSet textures;

static void drawSky(void);
static void drawGround(void);
static void loadTextureSet(void);

void draw3DBackground()
{
    loadTextureSet();

    drawSky();
    drawGround();
}

static void drawColumn(double distance, int x, bool horizontalSide, int texX)
{
    if(distance < 0.01)
        distance = 0.01;

    int wallHeight = (int)(WINDOW_HEIGHT / distance) * 0.4;

    int wallTop = (WINDOW_HEIGHT - wallHeight) / 2;
    int wallBottom = (WINDOW_HEIGHT + wallHeight) / 2;

    double brightness = 255.0 / (1.0 + distance * 0.5);

    //darken horizontal wall faces slightly for increased depth perception
    if(horizontalSide)
        brightness *= 0.7;

    for(int y = wallTop; y < wallBottom; y++)
    {
        if(y < 0 || y >= WINDOW_HEIGHT)
            continue;

        int texY = (y - wallTop) * TEXTURE_SIZE / wallHeight;
        Pixel pixel = textures.wall.pixels[texY][texX];
        
        int r = (int)(pixel.r * brightness / 255.0);
        int g = (int)(pixel.g * brightness / 255.0);
        int b = (int)(pixel.b * brightness / 255.0);

        setRGBColour(r, g, b);
        drawLine(x, y, x, y);
    }
}

void draw3DWalls(Robot* r)
{
    double angleIncrement = FOV * PI/180 / WINDOW_WIDTH;
    double robotAngle = r->orientation * PI / 2.0 - PI/2.0;
    double rayAngle = robotAngle - FOV * PI/180 / 2.0;

    double robotX = r->x + 0.5; //the + 0.5 starts ray at the center of the robot's square
    double robotY = r->y + 0.5;

    int x = -1;
    while(x < WINDOW_WIDTH)
    {
        x++;
        
        double rayDirX = cos(rayAngle);
        double rayDirY = sin(rayAngle);

        double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1.0 / rayDirX); //avoid division by zero
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

        bool horizontalSide;

        //DDA algorithm: https://lodev.org/cgtutor/raycasting.html
        while(!isWall(mapY, mapX))
        {
            if(sideDistX < sideDistY)
            {
                sideDistX += deltaDistX;
                mapX += stepX;
                horizontalSide = false;
            }
            else
            {
                sideDistY += deltaDistY;
                mapY += stepY;
                horizontalSide = true;
            }
        }

        double distance;
        if(!horizontalSide)
            distance = sideDistX - deltaDistX;
        else
            distance = sideDistY - deltaDistY;

        double wallX;
        if(!horizontalSide)
            wallX = robotY + distance * rayDirY;
        else
            wallX = robotX + distance * rayDirX;

        wallX -= floor(wallX);

        //convert wall position into a texture coordinate.
        int texX = (int)(wallX * TEXTURE_SIZE);
        if ((!horizontalSide && rayDirX > 0) || (horizontalSide && rayDirY < 0))
            texX = TEXTURE_SIZE - texX - 1;

        //correct distance for the fish-eye effect
        distance *= cos(rayAngle - robotAngle);
        
        drawColumn(distance, x, horizontalSide, texX);

        rayAngle += angleIncrement;
    }
}


static void drawSky(void)
{
    double horizon = WINDOW_HEIGHT / 2.0;
    double cameraHeight = WINDOW_HEIGHT / 2.0;

    for (int y = 0; y < (int)horizon; y++)
    {
        double distance = cameraHeight / (horizon - y);

        double ceilingX = -distance;
        double ceilingY = -distance;

        double stepX = (distance * 2.0) / WINDOW_WIDTH;

        for (int x = 0; x < WINDOW_WIDTH; x++)
        {
            int texX = (int)(ceilingX * TEXTURE_SIZE) % TEXTURE_SIZE;
            int texY = (int)(ceilingY * TEXTURE_SIZE) % TEXTURE_SIZE;

            if (texX < 0) texX += TEXTURE_SIZE;
            if (texY < 0) texY += TEXTURE_SIZE;

            Pixel pixel = textures.sky.pixels[texY][texX];

            double brightness = 255.0 / (1.0 + distance * 0.2);

            setRGBColour(
                pixel.r * brightness / 255.0,
                pixel.g * brightness / 255.0,
                pixel.b * brightness / 255.0
            );

            drawLine(x, y, x, y);

            ceilingX += stepX;
        }
    }
}

static void drawGround(void)
{
    double horizon = WINDOW_HEIGHT / 2.0;
    double cameraHeight = WINDOW_HEIGHT / 2.0;

    for (int y = (int)horizon + 1; y < WINDOW_HEIGHT; y++)
    {
        double distance = cameraHeight / (y - horizon);

        double groundX = -distance;
        double groundY = distance;

        double stepX = (distance * 2.0) / WINDOW_WIDTH;

        for (int x = 0; x < WINDOW_WIDTH; x++)
        {
            int texX = (int)(groundX * TEXTURE_SIZE) % TEXTURE_SIZE;
            int texY = (int)(groundY * TEXTURE_SIZE) % TEXTURE_SIZE;

            if (texX < 0) texX += TEXTURE_SIZE;
            if (texY < 0) texY += TEXTURE_SIZE;

            Pixel pixel = textures.ground.pixels[texY][texX];

            double brightness = 255.0 / (1.0 + distance * 0.2);

            setRGBColour(
                (int)(pixel.r * brightness / 255.0),
                (int)(pixel.g * brightness / 255.0),
                (int)(pixel.b * brightness / 255.0)
            );

            drawLine(x, y, x, y);

            groundX += stepX;
        }
    }
}

static bool loadTexture(Texture* texture, const char* filename)
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
            unsigned char rgb[3];

            if(fread(rgb, 1, 3, file) != 3)
            {
                fclose(file);
                return false;
            }

            texture->pixels[y][x].r = rgb[0];
            texture->pixels[y][x].g = rgb[1];
            texture->pixels[y][x].b = rgb[2];
        }
    }

    fclose(file);

    return true;
}

static void loadTextureSet(void)
{
    const char* textureSet = getenv("TEXTURE_SET");

    char wallPath[100];
    char floorPath[100];
    char skyPath[100];

    sprintf(wallPath, "textures/%s/wall.ppm", textureSet);
    sprintf(floorPath, "textures/%s/ground.ppm", textureSet);
    sprintf(skyPath, "textures/%s/sky.ppm", textureSet);

    loadTexture(&textures.wall, wallPath);
    loadTexture(&textures.ground, floorPath);
    loadTexture(&textures.sky, skyPath);
}