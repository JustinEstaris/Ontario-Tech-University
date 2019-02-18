 #include <GL/gl3w.h>
#include <GLFW/glfw3.h> // GLFW helper library
#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <iostream>

// IMGUI
#include <imgui.h>
#include <imgui_impl_glfw_gl3.h>

#include "Shaders.h"
#include "Loaders.h"
#include "Utils.h"

using namespace glm;

/*---------------------------- Variables ----------------------------*/
// GLFW window
GLFWwindow*     window;
ivec2           windowSize = ivec2(1280, 720);
bool            doWobble = true;

// Shader Program and Uniform Locations
GLuint  shader_program;
GLuint light_loc, color_loc, tex_loc, spec_loc;
GLuint normal_loc, model_loc, vp_loc;
GLuint lightType_loc;

// Shader Uniforms
mat4    viewMatrix;
mat4    projectionMatrix;
vec4    lightPos = vec4(0.0f, 0.0f, cos(0.0f), 0.0f);
vec4    lightCol = vec4(1.0f, 1.0f, 1.0f, 400.0f);

// Model and Texture
Texture metalTexture;
Texture metalSpecTexture;

Texture concreteTexture;
Texture concreteSpecTexture;

Model   boxModel;

int lightType;
float count = 0.0f;

bool useCrateTexture = false;

/*---------------------------- Functions ----------------------------*/
void Initialize()
{
    GLuint vs = buildShader(GL_VERTEX_SHADER, ASSETS"basic.vert");
    GLuint fs = buildShader(GL_FRAGMENT_SHADER, ASSETS"diffuse.frag");
    shader_program = buildProgram(vs, fs, 0);

    glBindAttribLocation(shader_program, VERTEX_LOC, "vPosition");
    glBindAttribLocation(shader_program, NORMAL_LOC, "vNormal");
    glBindAttribLocation(shader_program, UV_LOC, "vUV");

    linkProgram(shader_program);
    dumpProgram(shader_program, "Diffuse Lighting shader program");

    // Load box obj file and texture
    boxModel = Load3DModel(ASSETS"Models/", "Box.obj");

	LoadBMP(ASSETS"Textures/metal_diffuse.bmp", metalTexture);
	LoadBMP(ASSETS"Textures/metal_specular.bmp", metalSpecTexture);

	LoadBMP(ASSETS"Textures/concrete_diffuse.bmp", concreteTexture);
	LoadBMP(ASSETS"Textures/concrete_specular.bmp", concreteSpecTexture);

    light_loc = glGetUniformLocation(shader_program, "lightPosDir");
    color_loc = glGetUniformLocation(shader_program, "lightColor");
    normal_loc = glGetUniformLocation(shader_program, "normalMat");
    model_loc = glGetUniformLocation(shader_program, "modelMat");
    vp_loc = glGetUniformLocation(shader_program, "viewProjMat");
    tex_loc = glGetUniformLocation(shader_program, "diffuseSampler");
	spec_loc = glGetUniformLocation(shader_program, "specSampler");
}

void Update()
{
	if (glfwGetKey(window, GLFW_KEY_S)) {
		count += 0.002;
		lightPos = glm::vec4(sin(count) * 13.0f, 3.0f, cos(count) * 13.0f, 0.0f);
	}
}

void RenderModel(mat4 modelMatrix, Model model)
{
    mat4 normalMat = inverse(transpose(viewMatrix * modelMatrix));
    mat4 modelViewProjMat = projectionMatrix * viewMatrix * modelMatrix;

    glUniformMatrix4fv(normal_loc, 1, 0, &normalMat[0][0]);
    glUniformMatrix4fv(model_loc, 1, 0, &modelMatrix[0][0]);

    glBindVertexArray(model.vao);
    glDrawArrays(GL_TRIANGLES, 0, model.vertexCount);
}

void Render()
{
    glUseProgram(shader_program);
	lightType_loc = glGetUniformLocation(shader_program, "lightType");

    viewMatrix = lookAt(
        vec3(0.0f, 2.0f, 10.0f),
        vec3(0.0f, 1.0f, 0.0f),
        vec3(0.0f, 1.0f, 0.0f));
    float ratio = windowSize.x / (float)windowSize.y;
    projectionMatrix = perspective(DEG2RAD(50.0f), ratio, 0.01f, 100.0f);

    // Set view projection matrix
    glUniformMatrix4fv(vp_loc, 1, 0, &(projectionMatrix * viewMatrix)[0][0]);

    // Set lighting information
    glUniform4fv(light_loc, 1, &lightPos[0]);
    glUniform4fv(color_loc, 1, &lightCol[0]);
	glUniform1i(lightType_loc, lightType);

	mat4 identity = glm::mat4(1.0f);

    {   // Draw the first box
		glUniform1i(tex_loc, 0); // Set to crate texture
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, metalTexture.texture);

		glUniform1i(spec_loc, 1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, metalSpecTexture.texture);

        mat4 modelMat = mat4(1.0f);
		modelMat = translate(identity, glm::vec3(3.0f, 1.0f, 0.0f));
        modelMat = rotate(modelMat, DEG2RAD(90), vec3(0.0f, 1.0f, 0.0f));
        modelMat = scale(modelMat, vec3(3.0f));
        RenderModel(modelMat, boxModel);
    }

	{   // Draw the second box
		glUniform1i(tex_loc, 0); // Set to crate texture
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, concreteTexture.texture);

		glUniform1i(spec_loc, 1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, concreteSpecTexture.texture);

		mat4 modelMat = mat4(1.0f);
		modelMat = translate(identity, glm::vec3(-3.0f, -1.0f, 0.0f));
		modelMat = rotate(modelMat, DEG2RAD(90), vec3(0.0f, 1.0f, 0.0f));
		modelMat = scale(modelMat, vec3(3.0f));
		RenderModel(modelMat, boxModel);
	}
}

void Cleanup()
{
    // cleanup the box
    glDeleteBuffers(1, &boxModel.vbo);
    glDeleteVertexArrays(1, &boxModel.vao);

    // cleanup the shader
    glUseProgram(GL_NONE);
    glDeleteProgram(shader_program);
}

void GUI()
{
    ImGui::Begin("Settings");
    {
        // Show some basic stats in the settings window 
        ImGui::Text("%.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::RadioButton("Directional Light", &lightType, 0);
		ImGui::RadioButton("Point Light", &lightType, 1);
		ImGui::RadioButton("Spotlight", &lightType, 2);
    }
    ImGui::End();
}

static void ResizeEvent(GLFWwindow* a_window, int a_width, int a_height)
{
    // Set the viewport incase the window size changed
    glfwGetFramebufferSize(window, &windowSize.x, &windowSize.y);
    glViewport(0, 0, windowSize.x, windowSize.y);
}

/*---------------------------- Entry Point ----------------------------*/
int main()
{
    // start GL context and O/S window using the GLFW helper library
    if (!glfwInit())
    {
        fprintf(stderr, "ERROR: could not start GLFW3\n");
        return 1;
    }

    window = glfwCreateWindow(windowSize.x, windowSize.y, "Laboratory 5", NULL, NULL);
    if (!window)
    {
        fprintf(stderr, "ERROR: could not open window with GLFW3\n");
        glfwTerminate();
        return 1;
    }
    glfwMakeContextCurrent(window);
    glfwSetWindowSizeCallback(window, ResizeEvent);

    // start GL3W
    gl3wInit();

    // Setup ImGui binding. This is for any parameters you want to control in runtime
    ImGui_ImplGlfwGL3_Init(window, true);
    ImGui::StyleColorsLight();

    // Get version info
    const GLubyte* renderer = glGetString(GL_RENDERER); // get renderer string
    const GLubyte* version = glGetString(GL_VERSION); // version as a string
    printf("Renderer: %s\n", renderer);
    printf("OpenGL version supported %s\n", version);

    // tell GL to only draw onto a pixel if the shape is closer to the viewer
    glEnable(GL_DEPTH_TEST); // enable depth-testing
    glDepthFunc(GL_LESS); // depth-testing interprets a smaller value as "closer"

    Initialize();

    while (!glfwWindowShouldClose(window))
    {
        // update other events like input handling 
        glfwPollEvents();

        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        ImGui_ImplGlfwGL3_NewFrame();

        // Call the helper functions
        Update();
        Render();
        GUI();

        // Finish by drawing the GUI on top of everything
        ImGui::Render();
        glfwSwapBuffers(window);
    }

    // close GL context and any other GLFW resources
    glfwTerminate();
    ImGui_ImplGlfwGL3_Shutdown();
    Cleanup();
    return 0;
}