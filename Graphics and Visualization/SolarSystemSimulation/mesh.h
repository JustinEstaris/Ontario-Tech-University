#ifndef MESH_H
#define MESH_H

#include <GLM/glm.hpp>

#include <string>
#include <vector>
#include <GL/gl3w.h>

class Mesh
{
public:
    static std::vector<Mesh> LoadOBJ(std::string baseLoc, std::string fileName);
    void DrawMesh();

private:
    unsigned int vao, vbo;
    unsigned int vertexCount;
};

class Primitive
{
public:
    static void DrawSphere();
    static void DrawBox();
    static void DrawFullscreenQuad();
    static void DrawSkybox();

private:
    static bool sInit; static Primitive sphere;
    static bool bInit; static Primitive box;
    static bool qInit; static Primitive quad;
    static bool xInit; static Primitive skybox;

private:
    unsigned int vao, vbo;
    unsigned int vertexCount;
};

#endif