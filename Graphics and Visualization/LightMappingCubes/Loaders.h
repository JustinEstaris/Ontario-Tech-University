#ifndef LOADERS_H
#define LOADERS_H

#include "GL/gl3w.h"
#include <string>

static const int VERTEX_LOC = 0;
static const int NORMAL_LOC = 1;
static const int UV_LOC = 2;

struct Texture
{
    GLuint texture;
    int width;
    int height;
};

struct Model
{
    GLuint vao;
    GLuint vbo; // interleaved. This means vertex, normal, and colors are all in one

    unsigned int vertexCount;
};

int LoadBMP(const char* fileLoc, Texture& tex);
Model Load3DModel(std::string basedir, std::string filename);

#endif
