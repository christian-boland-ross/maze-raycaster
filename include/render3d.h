#ifndef RENDER3D_H
#define RENDER3D_H

#include "robot.h"

void draw3DWorld(Robot* r);

typedef struct
{
    unsigned char r;
    unsigned char g;
    unsigned char b;
} Pixel;

typedef struct
{
    Pixel pixels[TEXTURE_SIZE][TEXTURE_SIZE];
} Texture;

typedef struct
{
    Texture wall;
    Texture ground;
    Texture sky;
} TextureSet;

#endif