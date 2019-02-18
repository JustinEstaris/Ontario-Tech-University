#include "Mesh.h"

#include <GLM/glm.hpp>

#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>

#include <vector>
#include <fstream>
#include <cstdint>
#include <iostream>

#define VERTEX_LOC      0
#define NORMAL_LOC      1
#define TEXCOORD_LOC    2

std::vector<Mesh> Mesh::LoadOBJ(std::string baseLoc, std::string fileName)
{
    std::vector<Mesh> meshVector;
        
    {   // We're going to use TinyObjLoader to load in a wavefront OBJ file
        using namespace std;
        using namespace glm;

        // TinyObjLoader: http://syoyo.github.io/tinyobjloader/
        tinyobj::attrib_t attrib;
        vector< tinyobj::shape_t> shapes;
        vector< tinyobj::material_t> materials;

        string err;
        bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &err, (baseLoc + fileName).c_str(), baseLoc.c_str());

        if (!err.empty()) {
            std::cerr << err << std::endl;
        }

        // Loop over shapes
        for (size_t s = 0; s < shapes.size(); s++)
        {
            Mesh mesh_object;

            std::vector<glm::vec3> vertices;
            std::vector<glm::vec3> normals;
            std::vector<glm::vec2> uvs;

            int meshCount = 0;
            std::map<int, unsigned int> idRemap;
            std::map<unsigned int, glm::vec3> center;

            ////////////////////////////////////////////////////////////////////////////////////////////////////////

            // Loop over faces(polygon)
            size_t index_offset = 0;
            for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++)
            {
                int id = shapes[s].mesh.material_ids[f];
                int fv = shapes[s].mesh.num_face_vertices[f];

                // Loop over vertices in the face.
                for (size_t v = 0; v < fv; v++)
                {
                    // access to vertex
                    tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];

                    vertices.push_back(vec3(
                        attrib.vertices[3 * idx.vertex_index + 0],  // Vertex X
                        attrib.vertices[3 * idx.vertex_index + 1],  // Vertex Y
                        attrib.vertices[3 * idx.vertex_index + 2]   // Vertex Z
                    ));

                    normals.push_back(vec3(
                        attrib.normals[3 * idx.normal_index + 0],   // Normal X
                        attrib.normals[3 * idx.normal_index + 1],   // Normal Y
                        attrib.normals[3 * idx.normal_index + 2]    // Normal Z
                    ));

                    uvs.push_back(vec2(
                        attrib.texcoords[2 * idx.texcoord_index + 0],   // UV X
                        attrib.texcoords[2 * idx.texcoord_index + 1]    // UV Y
                    ));

                }
                index_offset += fv;
            }

            // Get the center pos of the mesh approximately
            for (int m = 0; m < idRemap.size(); m++)
            {

                ////////////////////////////////////////////////////////////////////////////////////////////////////////

                // 9 because vec3 has 3 parts, and there are 2 vec3s. and a vec2 3x2 + 2 =8
                std::vector<float> interleavedVBO(8 * vertices.size());
                // Create an interleaved VBO. This is layout out the following way
                /*
                vec3_vertices, vec3_normals, vec2_uvs, vec3_vertices, vec3_normals, vec2_uvs, etc...
                */
                for (int i = 0; i < vertices.size(); i++)
                {
                    interleavedVBO[i * 8 + 0] = vertices[i].x;
                    interleavedVBO[i * 8 + 1] = vertices[i].y;
                    interleavedVBO[i * 8 + 2] = vertices[i].z;
                    interleavedVBO[i * 8 + 3] = normals[i].x;
                    interleavedVBO[i * 8 + 4] = normals[i].y;
                    interleavedVBO[i * 8 + 5] = normals[i].z;
                    interleavedVBO[i * 8 + 6] = uvs[i].x;
                    interleavedVBO[i * 8 + 7] = uvs[i].y;
                }

                glGenVertexArrays(1, &mesh_object.vao);
                glBindVertexArray(mesh_object.vao);

                glGenBuffers(1, &mesh_object.vbo);
                glBindBuffer(GL_ARRAY_BUFFER, mesh_object.vbo);
                glBufferData(GL_ARRAY_BUFFER, sizeof(float) * interleavedVBO.size(), &interleavedVBO[0], GL_STATIC_DRAW);

                // Vertex info
                glVertexAttribPointer(VERTEX_LOC, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)0);
                glEnableVertexAttribArray(VERTEX_LOC);
                // Normal info
                glVertexAttribPointer(NORMAL_LOC, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)sizeof(glm::vec3));
                glEnableVertexAttribArray(NORMAL_LOC);
                // UV info
                glVertexAttribPointer(TEXCOORD_LOC, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(sizeof(glm::vec3) * 2));
                glEnableVertexAttribArray(TEXCOORD_LOC);

                // Uncomment the line below when you've fixed the code above
                mesh_object.vertexCount = (unsigned int)vertices.size();

                meshVector.push_back(mesh_object);

            }
        }
    }

    return meshVector;
}

void Mesh::DrawMesh()
{
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, vertexCount);
}

bool Primitive::sInit = false;
bool Primitive::bInit = false;
bool Primitive::qInit = false;
bool Primitive::xInit = false;

Primitive Primitive::sphere = Primitive();
Primitive Primitive::box = Primitive();
Primitive Primitive::quad = Primitive();
Primitive Primitive::skybox = Primitive();

void Primitive::DrawSphere()
{
    if (!sInit)
    {
        sInit = true;
        #pragma region Building a procedural sphere
        const float radius  = 0.5f;
        const int nbLong    = 24;
        const int nbLat     = 16;
 
        #pragma region Vertices
        std::vector<glm::vec3> vertices((nbLong+1) * nbLat + 2);
        float _pi = 3.1415f;
        float _2pi = _pi * 2.0f;
 
        vertices[0] = glm::vec3(0,1,0) * radius;
        for( int lat = 0; lat < nbLat; lat++ )
        {
	        float a1 = _pi * (float)(lat+1) / (nbLat+1);
	        float sin1 = sin(a1);
	        float cos1 = cos(a1);
 
	        for( int lon = 0; lon <= nbLong; lon++ )
	        {
		        float a2 = _2pi * (float)(lon == nbLong ? 0 : lon) / nbLong;
		        float sin2 = sin(a2);
		        float cos2 = cos(a2);
 
		        vertices[ lon + lat * (nbLong + 1) + 1] = glm::vec3( sin1 * cos2, cos1, sin1 * sin2 ) * radius;
	        }
        }
        vertices[vertices.size() - 1] = glm::vec3(0,1,0) * -radius;
        #pragma endregion
 
        #pragma region Normales		
        std::vector<glm::vec3> normales(vertices.size());
        for( unsigned int n = 0; n < vertices.size(); n++ )
	        normales[n] = glm::normalize(vertices[n]);
        #pragma endregion
 
        #pragma region UVs
        std::vector<glm::vec2> uvs(vertices.size());
        uvs[0] = glm::vec2(0,1);
        uvs[uvs.size()-1] = glm::vec2(0);
        for( int lat = 0; lat < nbLat; lat++ )
	        for( int lon = 0; lon <= nbLong; lon++ )
		        uvs[lon + lat * (nbLong + 1) + 1] = glm::vec2( (float)lon / nbLong, 1.0f - (float)(lat+1) / (nbLat+1) );
        #pragma endregion
 
        #pragma region Triangles
        int nbFaces = (int)vertices.size();
        int nbTriangles = nbFaces * 2;
        int nbIndexes = nbTriangles * 3;
        std::vector<int> triangles(nbIndexes);
 
        //Top Cap
        int i = 0;
        for( int lon = 0; lon < nbLong; lon++ )
        {
	        triangles[i++] = lon+2;
	        triangles[i++] = lon+1;
	        triangles[i++] = 0;
        }
 
        //Middle
        for( int lat = 0; lat < nbLat - 1; lat++ )
        {
	        for( int lon = 0; lon < nbLong; lon++ )
	        {
		        int current = lon + lat * (nbLong + 1) + 1;
		        int next = current + nbLong + 1;
 
		        triangles[i++] = current;
		        triangles[i++] = current + 1;
		        triangles[i++] = next + 1;
 
		        triangles[i++] = current;
		        triangles[i++] = next + 1;
		        triangles[i++] = next;
	        }
        }
 
        //Bottom Cap
        for( int lon = 0; lon < nbLong; lon++ )
        {
	        triangles[i++] = (int)vertices.size() - 1;
	        triangles[i++] = (int)vertices.size() - (lon+2) - 1;
	        triangles[i++] = (int)vertices.size() - (lon+1) - 1;
        }
        #pragma endregion

        #pragma region interleavedVBO

        std::vector<float> interleavedVBO(triangles.size() * 8);
        for (size_t i = 0; i < triangles.size(); i++)
        {
            interleavedVBO[i * 8 + 0] = vertices[triangles[i]].x;
            interleavedVBO[i * 8 + 1] = vertices[triangles[i]].y;
            interleavedVBO[i * 8 + 2] = vertices[triangles[i]].z;
            interleavedVBO[i * 8 + 3] = normales[triangles[i]].x;
            interleavedVBO[i * 8 + 4] = normales[triangles[i]].y;
            interleavedVBO[i * 8 + 5] = normales[triangles[i]].z;
            interleavedVBO[i * 8 + 6] = uvs[triangles[i]].x;
            interleavedVBO[i * 8 + 7] = uvs[triangles[i]].y;
        }

        #pragma endregion

        ////////////////////////////////////////////////////////////////////////////////////////////////////////

        glGenVertexArrays(1, &sphere.vao);
        glBindVertexArray(sphere.vao);

        glGenBuffers(1, &sphere.vbo);
        glBindBuffer(GL_ARRAY_BUFFER, sphere.vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * interleavedVBO.size(), &interleavedVBO[0], GL_STATIC_DRAW);

        // Vertex info
        glVertexAttribPointer(VERTEX_LOC, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)0);
        glEnableVertexAttribArray(VERTEX_LOC);
        // Normal info
        glVertexAttribPointer(NORMAL_LOC, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)sizeof(glm::vec3));
        glEnableVertexAttribArray(NORMAL_LOC);
        // UV info
        glVertexAttribPointer(TEXCOORD_LOC, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(sizeof(glm::vec3) * 2));
        glEnableVertexAttribArray(TEXCOORD_LOC);

        // Uncomment the line below when you've fixed the code above
        sphere.vertexCount = (unsigned int)triangles.size();
        #pragma endregion
    }

    glBindVertexArray(sphere.vao);
    glDrawArrays(GL_TRIANGLES, 0, sphere.vertexCount);
}

void Primitive::DrawBox()
{
    if (!bInit)
    {
        bInit = true;
        #pragma region Building a procedural box
        float length    = 1.0f;
        float width     = 1.0f;
        float height    = 1.0f;
 
        #pragma region Vertices
        glm::vec3 p0 = glm::vec3(-length * 0.5f, -width * 0.5f,  height * 0.5f);
        glm::vec3 p1 = glm::vec3( length * 0.5f, -width * 0.5f,  height * 0.5f);
        glm::vec3 p2 = glm::vec3( length * 0.5f, -width * 0.5f, -height * 0.5f);
        glm::vec3 p3 = glm::vec3(-length * 0.5f, -width * 0.5f, -height * 0.5f);	
        glm::vec3 p4 = glm::vec3(-length * 0.5f,  width * 0.5f,  height * 0.5f);
        glm::vec3 p5 = glm::vec3( length * 0.5f,  width * 0.5f,  height * 0.5f);
        glm::vec3 p6 = glm::vec3( length * 0.5f,  width * 0.5f, -height * 0.5f);
        glm::vec3 p7 = glm::vec3(-length * 0.5f,  width * 0.5f, -height * 0.5f);
 
        glm::vec3 vertices[] = 
        {
	        // Bottom
	        p0, p1, p2, p3,
	        // Left
	        p7, p4, p0, p3,
	        // Front
	        p4, p5, p1, p0,
	        // Back
	        p6, p7, p3, p2,
	        // Right
	        p5, p6, p2, p1,
	        // Top
	        p7, p6, p5, p4
        };
        #pragma endregion
 
        #pragma region Normales		
        glm::vec3 up 	= glm::vec3( 0, 1, 0);
        glm::vec3 down 	= glm::vec3( 0,-1, 0);
        glm::vec3 front = glm::vec3( 0, 0, 1);
        glm::vec3 back 	= glm::vec3( 0, 0,-1);
        glm::vec3 right = glm::vec3( 1, 0, 0);
        glm::vec3 left 	= glm::vec3(-1, 0, 0);
 
        glm::vec3 normales[] =
        {
	        // Bottom
	        down, down, down, down,
	        // Left
	        left, left, left, left,
	        // Front
	        front, front, front, front,
	        // Back
	        back, back, back, back,
	        // Right
	        right, right, right, right,
	        // Top
	        up, up, up, up
        };
        #pragma endregion
 
        #pragma region UVs
        glm::vec2 _00 = glm::vec2(0.0f, 0.0f);
        glm::vec2 _10 = glm::vec2(1.0f, 0.0f);
        glm::vec2 _01 = glm::vec2(0.0f, 1.0f);
        glm::vec2 _11 = glm::vec2(1.0f, 1.0f);

        glm::vec2 uvs[] =
        {
            // Bottom
            _11, _01, _00, _10,
            // Left
            _11, _01, _00, _10,
            // Front
            _11, _01, _00, _10,
            // Back
            _11, _01, _00, _10,
            // Right
            _11, _01, _00, _10,
            // Top
            _11, _01, _00, _10,
        };
        #pragma endregion
 
        #pragma region Triangles
        std::vector<int> triangles =
        {
            // Bottom
            3, 1, 0,
            3, 2, 1,
            // Left
            3 + 4 * 1, 1 + 4 * 1, 0 + 4 * 1,
            3 + 4 * 1, 2 + 4 * 1, 1 + 4 * 1,
            // Front
            3 + 4 * 2, 1 + 4 * 2, 0 + 4 * 2,
            3 + 4 * 2, 2 + 4 * 2, 1 + 4 * 2,
            // Back
            3 + 4 * 3, 1 + 4 * 3, 0 + 4 * 3,
            3 + 4 * 3, 2 + 4 * 3, 1 + 4 * 3,
            // Right
            3 + 4 * 4, 1 + 4 * 4, 0 + 4 * 4,
            3 + 4 * 4, 2 + 4 * 4, 1 + 4 * 4,
            // Top
            3 + 4 * 5, 1 + 4 * 5, 0 + 4 * 5,
            3 + 4 * 5, 2 + 4 * 5, 1 + 4 * 5,

        };
        #pragma endregion

        #pragma region interleavedVBO
        std::vector<float> interleavedVBO(triangles.size() * 8);
        for (size_t i = 0; i < triangles.size(); i++)
        {
            interleavedVBO[i * 8 + 0] = vertices[triangles[i]].x;
            interleavedVBO[i * 8 + 1] = vertices[triangles[i]].y;
            interleavedVBO[i * 8 + 2] = vertices[triangles[i]].z;
            interleavedVBO[i * 8 + 3] = normales[triangles[i]].x;
            interleavedVBO[i * 8 + 4] = normales[triangles[i]].y;
            interleavedVBO[i * 8 + 5] = normales[triangles[i]].z;
            interleavedVBO[i * 8 + 6] = uvs[triangles[i]].x;
            interleavedVBO[i * 8 + 7] = uvs[triangles[i]].y;
        }
        #pragma endregion

        ////////////////////////////////////////////////////////////////////////////////////////////////////////

        glGenVertexArrays(1, &box.vao);
        glBindVertexArray(box.vao);

        glGenBuffers(1, &box.vbo);
        glBindBuffer(GL_ARRAY_BUFFER, box.vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * interleavedVBO.size(), &interleavedVBO[0], GL_STATIC_DRAW);

        // Vertex info
        glVertexAttribPointer(VERTEX_LOC, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)0);
        glEnableVertexAttribArray(VERTEX_LOC);
        // Normal info
        glVertexAttribPointer(NORMAL_LOC, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)sizeof(glm::vec3));
        glEnableVertexAttribArray(NORMAL_LOC);
        // UV info
        glVertexAttribPointer(TEXCOORD_LOC, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(sizeof(glm::vec3) * 2));
        glEnableVertexAttribArray(TEXCOORD_LOC);

        // Uncomment the line below when you've fixed the code above
        box.vertexCount = (unsigned int)triangles.size();
        #pragma endregion
    }

    glBindVertexArray(box.vao);
    glDrawArrays(GL_TRIANGLES, 0, box.vertexCount);
}

void Primitive::DrawFullscreenQuad()
{
    if (!qInit)
    {
        qInit = true;
        #pragma region Building a procedural quad
        float width     = 1.0f;
        float height    = 1.0f;
 
        #pragma region Vertices
        glm::vec3 p0 = glm::vec3(-width, -height, 0.0f);
        glm::vec3 p1 = glm::vec3(-width,  height, 0.0f);
        glm::vec3 p2 = glm::vec3( width, -height, 0.0f);
        glm::vec3 p3 = glm::vec3( width,  height, 0.0f);
 
        glm::vec3 vertices[] = 
        {
	        // Face
	        p0, p1, p2, p3,
        };
        #pragma endregion
 
        #pragma region Normales		
        glm::vec3 front = glm::vec3( 0, 0, 1);
 
        glm::vec3 normales[] = { front, front, front, front };
        #pragma endregion
 
        #pragma region UVs
        glm::vec2 _00 = glm::vec2(0.0f, 0.0f);
        glm::vec2 _01 = glm::vec2(0.0f, 1.0f);
        glm::vec2 _10 = glm::vec2(1.0f, 0.0f);
        glm::vec2 _11 = glm::vec2(1.0f, 1.0f);

        glm::vec2 uvs[] = { _00, _01, _10, _11 };
        #pragma endregion
 
        #pragma region Triangles
        std::vector<int> triangles = { 3, 1, 0, 2, 3, 0 };
        #pragma endregion

        #pragma region interleavedVBO
        std::vector<float> interleavedVBO(triangles.size() * 8);
        for (size_t i = 0; i < triangles.size(); i++)
        {
            interleavedVBO[i * 8 + 0] = vertices[triangles[i]].x;
            interleavedVBO[i * 8 + 1] = vertices[triangles[i]].y;
            interleavedVBO[i * 8 + 2] = vertices[triangles[i]].z;
            interleavedVBO[i * 8 + 3] = normales[triangles[i]].x;
            interleavedVBO[i * 8 + 4] = normales[triangles[i]].y;
            interleavedVBO[i * 8 + 5] = normales[triangles[i]].z;
            interleavedVBO[i * 8 + 6] = uvs[triangles[i]].x;
            interleavedVBO[i * 8 + 7] = uvs[triangles[i]].y;
        }
        #pragma endregion

        ////////////////////////////////////////////////////////////////////////////////////////////////////////

        glGenVertexArrays(1, &quad.vao);
        glBindVertexArray(quad.vao);

        glGenBuffers(1, &quad.vbo);
        glBindBuffer(GL_ARRAY_BUFFER, quad.vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * interleavedVBO.size(), &interleavedVBO[0], GL_STATIC_DRAW);

        // Vertex info
        glVertexAttribPointer(VERTEX_LOC, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)0);
        glEnableVertexAttribArray(VERTEX_LOC);
        // Normal info
        glVertexAttribPointer(NORMAL_LOC, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)sizeof(glm::vec3));
        glEnableVertexAttribArray(NORMAL_LOC);
        // UV info
        glVertexAttribPointer(TEXCOORD_LOC, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(sizeof(glm::vec3) * 2));
        glEnableVertexAttribArray(TEXCOORD_LOC);

        // Uncomment the line below when you've fixed the code above
        quad.vertexCount = (unsigned int)triangles.size();
        #pragma endregion
    }
    glBindVertexArray(quad.vao);
    glDrawArrays(GL_TRIANGLES, 0, quad.vertexCount);
}

void Primitive::DrawSkybox()
{
    if (!xInit)
    {
        xInit = true;

        float points[] =
        {
          -10.0f,  10.0f, -10.0f,
          -10.0f, -10.0f, -10.0f,
           10.0f, -10.0f, -10.0f,
           10.0f, -10.0f, -10.0f,
           10.0f,  10.0f, -10.0f,
          -10.0f,  10.0f, -10.0f,
  
          -10.0f, -10.0f,  10.0f,
          -10.0f, -10.0f, -10.0f,
          -10.0f,  10.0f, -10.0f,
          -10.0f,  10.0f, -10.0f,
          -10.0f,  10.0f,  10.0f,
          -10.0f, -10.0f,  10.0f,
  
           10.0f, -10.0f, -10.0f,
           10.0f, -10.0f,  10.0f,
           10.0f,  10.0f,  10.0f,
           10.0f,  10.0f,  10.0f,
           10.0f,  10.0f, -10.0f,
           10.0f, -10.0f, -10.0f,
   
          -10.0f, -10.0f,  10.0f,
          -10.0f,  10.0f,  10.0f,
           10.0f,  10.0f,  10.0f,
           10.0f,  10.0f,  10.0f,
           10.0f, -10.0f,  10.0f,
          -10.0f, -10.0f,  10.0f,
  
          -10.0f,  10.0f, -10.0f,
           10.0f,  10.0f, -10.0f,
           10.0f,  10.0f,  10.0f,
           10.0f,  10.0f,  10.0f,
          -10.0f,  10.0f,  10.0f,
          -10.0f,  10.0f, -10.0f,
  
          -10.0f, -10.0f, -10.0f,
          -10.0f, -10.0f,  10.0f,
           10.0f, -10.0f, -10.0f,
           10.0f, -10.0f, -10.0f,
          -10.0f, -10.0f,  10.0f,
           10.0f, -10.0f,  10.0f
        };

        GLuint vbo;
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, 3 * 36 * sizeof(float), &points, GL_STATIC_DRAW);

        GLuint vao;
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

        skybox.vao = vao;
        skybox.vbo = vbo;
    }

    glDepthMask(GL_FALSE);
    glBindVertexArray(skybox.vao);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
    glDepthMask(GL_TRUE);
}
