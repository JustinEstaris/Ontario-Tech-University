#include "Loaders.h"

#include <GLM/glm.hpp>
#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>

#include <fstream>
#include <cstdint>
#include <iostream>

int LoadBMP(const char * fileLoc, Texture & tex)
{
    typedef int8_t Uint8;

    Uint8* datBuff[2] = { nullptr, nullptr }; // Header buffers
    Uint8* pixels = nullptr; // Pixels

    BITMAPFILEHEADER* bmpHeader = nullptr; // Header
    BITMAPINFOHEADER* bmpInfo = nullptr; // Info 

    // The file... We open it with it's constructor
    std::ifstream file(fileLoc, std::ios::binary);
    if (!file)
    {
        std::cout << "Failure to open bitmap file.\n";

        return 1;
    }

    // Allocate byte memory that will hold the two headers
    datBuff[0] = new Uint8[sizeof(BITMAPFILEHEADER)];
    datBuff[1] = new Uint8[sizeof(BITMAPINFOHEADER)];

    file.read((char*)datBuff[0], sizeof(BITMAPFILEHEADER));
    file.read((char*)datBuff[1], sizeof(BITMAPINFOHEADER));

    // Construct the values from the buffers
    bmpHeader = (BITMAPFILEHEADER*)datBuff[0];
    bmpInfo = (BITMAPINFOHEADER*)datBuff[1];

    // Check if the file is an actual BMP file
    if (bmpHeader->bfType != 0x4D42)
    {
        std::cout << "File \"" << fileLoc << "\" isn't a BMP\n";
        return 2;
    }

    // First allocate pixel memory
    pixels = new Uint8[bmpInfo->biSizeImage];

    // Go to where image data starts, then read in image data
    file.seekg(bmpHeader->bfOffBits);
    file.read((char*)pixels, bmpInfo->biSizeImage);

    // We're almost done. We have our image loaded, however it's
    // not in the right format. *.bmp files store image data in the
    // BGR format, and we have to convert it to RGB. Since we have 
    // the value in bytes, this shouldn't be to hard to accomplish
    Uint8 tmpRGB = 0; // Swap buffer
    for (unsigned long i = 0; i < bmpInfo->biSizeImage; i += 3)
    {
        tmpRGB = pixels[i];
        pixels[i] = pixels[i + 2];
        pixels[i + 2] = tmpRGB;
    }

    // Set width and height to the values loaded from the file
    tex.width   = bmpInfo->biWidth;
    tex.height  = bmpInfo->biHeight;

    /*******************GENERATING TEXTURES*******************/

    glGenTextures(1, &tex.texture);     // Generate a texture
    glBindTexture(GL_TEXTURE_2D, tex.texture); // Bind that texture

    GLint mode = GL_RGB;    // Set the mode

    glTexParameteri(    // Set the minification filtering
        GL_TEXTURE_2D,
        GL_TEXTURE_MIN_FILTER,
        GL_LINEAR_MIPMAP_LINEAR);
    
    glTexParameteri(    // Set the magnification filtering
        GL_TEXTURE_2D,
        GL_TEXTURE_MAG_FILTER,
        GL_LINEAR);

    // Change the wrap mode here
    glTexParameteri(
        GL_TEXTURE_2D,
        GL_TEXTURE_WRAP_S, // HORIZONTALLY
		GL_REPEAT);

    // and also change the wrap mode here
    glTexParameteri(
        GL_TEXTURE_2D,
        GL_TEXTURE_WRAP_T, // VERTICALLY
		GL_REPEAT); // textures to change

    // Create the texture. We get the offsets from the image, then
    // we use it with the image's pixel data to create it.
    glTexImage2D(GL_TEXTURE_2D, 0, mode, tex.width, tex.height,
        0, mode, GL_UNSIGNED_BYTE, pixels);

	//glTexImage2D();

    glGenerateMipmap(GL_TEXTURE_2D);

    // Unbind the texture
    glBindTexture(GL_TEXTURE_2D, NULL);

    // Output a successful message
    std::cout << "Texture \"" << fileLoc << "\" loaded success.\n";

    // Delete the two buffers.
    delete[] datBuff[0];
    delete[] datBuff[1];
    delete[] pixels;

    return 0; // Return success code 
}

/*---------------------------- Functions ----------------------------*/
Model Load3DModel(std::string basedir, std::string filename)
{
    Model m;

    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec2> uvs;

    {   // We're going to use TinyObjLoader to load in a wavefront OBJ file
        using namespace std;
        using namespace glm;

        // TinyObjLoader: http://syoyo.github.io/tinyobjloader/
        tinyobj::attrib_t attrib;
        vector< tinyobj::shape_t> shapes;
        vector< tinyobj::material_t> materials;

        string err;
        bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &err, (basedir + filename).c_str(), basedir.c_str());

        if (!err.empty()) {
            std::cerr << err << std::endl;
        }

        // Loop over shapes
        for (size_t s = 0; s < shapes.size(); s++)
        {
            // Loop over faces(polygon)
            size_t index_offset = 0;
            for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++)
            {
                int fv = shapes[s].mesh.num_face_vertices[f];

                // Loop over vertices in the face.
                for (size_t v = 0; v < fv; v++) {
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
        }
    }

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

    glGenVertexArrays(1, &m.vao);
    glBindVertexArray(m.vao);

    glGenBuffers(1, &m.vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m.vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * interleavedVBO.size(), &interleavedVBO[0], GL_STATIC_DRAW);

    // Vertex info
    glVertexAttribPointer(VERTEX_LOC, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)0);
    glEnableVertexAttribArray(VERTEX_LOC);
    // Normal info
    glVertexAttribPointer(NORMAL_LOC, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)sizeof(glm::vec3));
    glEnableVertexAttribArray(NORMAL_LOC);
    // UV info
    glVertexAttribPointer(UV_LOC, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(sizeof(glm::vec3) * 2));
    glEnableVertexAttribArray(UV_LOC);

    m.vertexCount = vertices.size();

    return m;
}