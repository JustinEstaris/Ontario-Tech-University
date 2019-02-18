/*
	Graphics - Assignment 3
	Francis Hackenberger, Ryan Goulding, Ryan Schuette, Andre Dallaire, Justin Estaris
*/
// OpenGL libraries
#define GLM_ENABLE_EXPERIMENTAL

#include <GL/gl3w.h>
#include <GLFW/glfw3.h>
#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/matrix_access.hpp>
#include <GLM/gtx/rotate_vector.hpp>
#include <GLM/gtc/constants.hpp>
#include <SOIL.h>

// GUI Library
#include <imgui.h>
#include <imgui_impl_glfw_gl3.h>

// Standard Libraries
#include <iostream> // Used for std::cout
#include <vector>   // Used for std::vector<vec3>
#include <map>      // Used for std::map

// Custom headers
#include "shaders.h"
#include "mesh.h"

using namespace glm;

/*---------------------------- Variables ----------------------------*/
// GLFW window
GLFWwindow* window;
int width = 1280, height = 720;

// Shader programs
GLuint phongProgram, skyboxProgram, emissiveProgram;

// Variables for uniforms
mat4 projectionMatrix, viewMatrix, modelMatrix[11], v;
vec3 cameraPosition, cameraTarget, lightPosition;
vec3 eyePos = vec3(-35, 0, 35);

// Solar system variables
float earthDays = 17.62f;
float moonRotation = 0.0f;
float simulationSpeed = 0.01f;
float gravityStrength = 9.6f;

//asteroid variable's
float ASTEROID_SIZE = 0.5f;// 2.25f;
const float ASTEROID_SPEED = 5.0f;
float distanceFromCenterX;
float distanceFromCenterZ;
float xDirection;
float zDirection;
float asteroidAngle;
float asteroidRotate;
vec3 asteroidPosition;
bool asteroidSpawned = false;

// Textures
GLuint skyboxTexture;
GLuint earthDiffuseTexture, earthSpecularTexture;

GLuint moonTexture, sunTexture, jupiterDiffuseTexture, mercuryDiffuseTexture, marsDiffuseTexture,
	   neptuneDiffuseTexture, saturnDiffuseTexture, uranusDiffuseTexture, venusDiffuseTexture, asteroidDiffuseTexture;

GLuint jupiterSpecularTexture, mercurySpecularTexture, marsSpecularTexture,
	   neptuneSpecularTexture, saturnSpecularTexture, uranusSpecularTexture, 
	   venusSpecularTexture, asteroidSpecularTexture;

//PLUTO ISN'T A PLANET!
enum
{
	EARTH = 0,
	SUN = 1,
	MOON = 2,
	MERCURY = 3,
	VENUS = 4,
	MARS = 5,
	JUPITER = 6,
	SATURN = 7,
	URANUS = 8,
	NEPTUNE = 9,
	ASTEROID = 10,
};

void Initialize()
{
	// Make a simple shader for the sphere we're drawing
	{
		GLuint vs = buildShader(GL_VERTEX_SHADER, ASSETS"simpleLights.vert");
		GLuint fs = buildShader(GL_FRAGMENT_SHADER, ASSETS"simpleLights.frag");
		phongProgram = buildProgram(vs, fs, 0);
		phongProgram = linkProgram(phongProgram);
		dumpProgram(phongProgram, "Simple program for phong lighting");
	}

	// Make a simple shader for the skybox
	{
		GLuint vs = buildShader(GL_VERTEX_SHADER, ASSETS"skybox.vert");
		GLuint fs = buildShader(GL_FRAGMENT_SHADER, ASSETS"skybox.frag");
		skyboxProgram = buildProgram(vs, fs, 0);
		skyboxProgram = linkProgram(skyboxProgram);
		dumpProgram(skyboxProgram, "Simple program for the skybox");
	}

	// Make a simple shader for the sun
	{
		GLuint vs = buildShader(GL_VERTEX_SHADER, ASSETS"emissive.vert");
		GLuint fs = buildShader(GL_FRAGMENT_SHADER, ASSETS"emissive.frag");
		emissiveProgram = buildProgram(vs, fs, 0);
		emissiveProgram = linkProgram(emissiveProgram);
		dumpProgram(emissiveProgram, "Simple program for the sun");
	}

	// Load in all 6 faces of the skybox cube
	skyboxTexture = SOIL_load_OGL_cubemap
	(
		ASSETS"textures/star_sky/stars.png", // posx
		ASSETS"textures/star_sky/stars.png", // negx
		ASSETS"textures/star_sky/stars.png", // posy
		ASSETS"textures/star_sky/stars.png", // negy
		ASSETS"textures/star_sky/stars.png", // posz
		ASSETS"textures/star_sky/stars.png", // negz
		SOIL_LOAD_RGB,      // This means we're expecting it to have RGB channels
		SOIL_CREATE_NEW_ID, // This means we want to create a new texture instead of overwriting one 
		SOIL_FLAG_MIPMAPS   // This means we want it to generate mip-maps.
	);

	//Bind textures
	{
		/**************************************************************************************************
			SUN / MOON TEXTURES
		**************************************************************************************************/
		moonTexture = SOIL_load_OGL_texture
		(
			ASSETS"textures/moonTexture.png",
			SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID,
			SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
		);
		sunTexture = SOIL_load_OGL_texture
		(
			ASSETS"textures/sunTexture.png",
			SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID,
			SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
		);

		/**************************************************************************************************
			EARTH TEXTURES
		**************************************************************************************************/
		earthDiffuseTexture = SOIL_load_OGL_texture
		(
			ASSETS"textures/earthDiffuse.png",
			SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID,
			SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
		);
		earthSpecularTexture = SOIL_load_OGL_texture
		(
			ASSETS"textures/earthSpecular.png",
			SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID,
			SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
		);

		/**************************************************************************************************
			JUPITER TEXTURES
		**************************************************************************************************/
		jupiterDiffuseTexture = SOIL_load_OGL_texture
		(
			ASSETS"textures/jupiterDiffuse.png",
			SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID,
			SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
		);
		jupiterSpecularTexture = SOIL_load_OGL_texture
		(
			ASSETS"textures/jupiterSpecular.png",
			SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID,
			SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
		);

		/**************************************************************************************************
			MERCURY TEXTURES
		**************************************************************************************************/
		mercuryDiffuseTexture = SOIL_load_OGL_texture
		(
			ASSETS"textures/mercuryDiffuse.png",
			SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID,
			SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
		);
		mercurySpecularTexture = SOIL_load_OGL_texture
		(
			ASSETS"textures/mercurySpecular.png",
			SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID,
			SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
		);

		/**************************************************************************************************
			MARS TEXTURES
		**************************************************************************************************/
		marsDiffuseTexture = SOIL_load_OGL_texture
		(
			ASSETS"textures/marsDiffuse.png",
			SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID,
			SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
		);
		marsSpecularTexture = SOIL_load_OGL_texture
		(
			ASSETS"textures/marsSpecular.png",
			SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID,
			SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
		);

		/**************************************************************************************************
			NEPTUNE TEXTURES
		**************************************************************************************************/
		neptuneDiffuseTexture = SOIL_load_OGL_texture
		(
			ASSETS"textures/neptuneDiffuse.png",
			SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID,
			SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
		);
		neptuneSpecularTexture = SOIL_load_OGL_texture
		(
			ASSETS"textures/neptuneSpecular.png",
			SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID,
			SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
		);

		/**************************************************************************************************
			SATURN TEXTURES
		**************************************************************************************************/
		saturnDiffuseTexture = SOIL_load_OGL_texture
		(
			ASSETS"textures/saturnDiffuse.png",
			SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID,
			SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
		);
		saturnSpecularTexture = SOIL_load_OGL_texture
		(
			ASSETS"textures/saturnSpecular.png",
			SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID,
			SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
		);

		/**************************************************************************************************
			URANUS TEXTURES
		**************************************************************************************************/
		uranusDiffuseTexture = SOIL_load_OGL_texture
		(
			ASSETS"textures/uranusDiffuse.png",
			SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID,
			SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
		);
		uranusSpecularTexture = SOIL_load_OGL_texture
		(
			ASSETS"textures/uranusSpecular.png",
			SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID,
			SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
		);

		/**************************************************************************************************
			VENUS TEXTURES
		**************************************************************************************************/
		venusDiffuseTexture = SOIL_load_OGL_texture
		(
			ASSETS"textures/venusDiffuse.png",
			SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID,
			SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
		);
		venusSpecularTexture = SOIL_load_OGL_texture
		(
			ASSETS"textures/venusSpecular.png",
			SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID,
			SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
		);

		/**************************************************************************************************
		ASTEROID TEXTURES
		**************************************************************************************************/
		asteroidDiffuseTexture = SOIL_load_OGL_texture
		(
			ASSETS"textures/asteroidDiffuse.png",
			SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID,
			SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
		);
		asteroidSpecularTexture = SOIL_load_OGL_texture
		(
			ASSETS"textures/asteridSpecular.png",
			SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID,
			SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
		);
	}

	v = inverse(lookAt(vec3(8, 15, -39), vec3(0), vec3(0, 1, 0)));
	cameraPosition = vec3(0, 0, 0);
    cameraTarget = vec3(0, 0, 0);
}

void Update(float deltaTime)
{
	mat4 identity, translation, scaling, rotation;
	identity = mat4(1.0f);
	const float pi2 = 2.0f * pi<float>();

	// Add to the rotation, in days.
	earthDays += deltaTime * simulationSpeed;

	float planetRotations = earthDays;

	// Compute orbits and rotations
	float earthOrbit = (planetRotations / 365.0f) * pi2;
	float earthRotate = fract(planetRotations) * pi2;
	float moonOrbit = (planetRotations / 27.322f) * pi2;
	float moonRotate = -fract(planetRotations / 27.0f) * pi2;

	vec3 earthPosition = vec3(cos(earthOrbit), 0, sin(earthOrbit)) * 18.0f;
	vec3 moonPosition = earthPosition + vec3(cos(moonOrbit), 0, sin(moonOrbit)) * 4.0f;

	translation = translate(identity, earthPosition);
	scaling = scale(identity, vec3(1)); // The earth stays the same size
	rotation = rotate(identity, earthRotate, vec3(0, 1, 0));
	modelMatrix[EARTH] = translation * rotation * scaling;

	translation = translate(identity, moonPosition);
	scaling = scale(identity, vec3(0.27)); // The moon is 27% the size of earth
	rotation = rotate(identity, moonRotate, vec3(0, 1, 0));
	modelMatrix[MOON] = translation * rotation * scaling;

	scaling = scale(identity, vec3(7)); // Make the sun 10 times larger
	modelMatrix[SUN] = scaling * identity;

	//SET SCALING/POSITION/ROTATION OF NEW PLANETS
	//Mercury
	float mercuryOrbit = (planetRotations / 88.0f) * pi2;
	float mercuryRotate = fract(planetRotations / 59.0f) * pi2;
	vec3 mercuryPosition = vec3(cos(mercuryOrbit), 0, sin(mercuryOrbit)) * 8.0f;
	{
		translation = translate(identity, mercuryPosition);
		scaling = scale(identity, vec3(0.38));
		rotation = rotate(identity, mercuryRotate, vec3(0, 1, 0));
		modelMatrix[MERCURY] = translation * rotation * scaling;
	}

	//Venus
	float venusOrbit = (planetRotations / 225.0f) * pi2;
	float venusRotate = -fract(planetRotations / 243.0f) * pi2; //venus rotate clockwise
	vec3 venusPosition = vec3(cos(venusOrbit), 0, sin(venusOrbit)) * 13.0f;
	{
		translation = translate(identity, venusPosition);
		scaling = scale(identity, vec3(0.815));
		rotation = rotate(identity, venusRotate, vec3(0, 1, 0));
		modelMatrix[VENUS] = translation * rotation * scaling;
	}

	//Mars
	float marsOrbit = (planetRotations / 687.0f) * pi2;
	float marsRotate = fract(planetRotations) * pi2;
	vec3 marsPosition = vec3(cos(marsOrbit), 0, sin(marsOrbit)) * 23.0f;
	{
		translation = translate(identity, marsPosition);
		scaling = scale(identity, vec3(0.70));
		rotation = rotate(identity, marsRotate, vec3(0, 1, 0));
		modelMatrix[MARS] = translation * rotation * scaling;
	}

	//Jupiter
	float jupiterOrbit = (planetRotations / 4380.0f) * pi2;
	float jupiterRotate = fract(planetRotations / 0.39f) * pi2;
	vec3 jupiterPosition = vec3(cos(jupiterOrbit), 0, sin(jupiterOrbit)) * 28.0f;
	{
		translation = translate(identity, jupiterPosition);
		scaling = scale(identity, vec3(2.5));
		rotation = rotate(identity, jupiterRotate, vec3(0, 1, 0));
		modelMatrix[JUPITER] = translation * rotation * scaling;
	}

	//Saturn
	float saturnOrbit = (planetRotations / 10672.0f) * pi2;
	float saturnRotate = fract(planetRotations / 0.42f) * pi2;
	vec3 saturnPosition = vec3(cos(saturnOrbit), 0, sin(saturnOrbit)) * 33.0f;
	{
		translation = translate(identity, saturnPosition);
		scaling = scale(identity, vec3(2.2));
		rotation = rotate(identity, saturnRotate, vec3(0, 1, 0));
		modelMatrix[SATURN] = translation * rotation * scaling;
	}

	//Uranus
	float uranusOrbit = (planetRotations / 30660.0f) * pi2;
	float uranusRotate = fract(planetRotations / 0.725f) * pi2;
	vec3 uranusPosition = vec3(cos(uranusOrbit), 0, sin(uranusOrbit)) * 38.0f;
	{
		translation = translate(identity, uranusPosition);
		scaling = scale(identity, vec3(1.5));
		rotation = rotate(identity, uranusRotate, vec3(0, 1, 0));
		modelMatrix[URANUS] = translation * rotation * scaling;
	}

	//Neptune
	float neptuneOrbit = (planetRotations / 60225.0f) * pi2;
	float neptuneRotate = fract(planetRotations / 0.67f) * pi2;
	vec3 neptunePosition = vec3(cos(neptuneOrbit), 0, sin(neptuneOrbit)) * 43.0f;
	{
		translation = translate(identity, neptunePosition);
		scaling = scale(identity, vec3(1.7));
		rotation = rotate(identity, neptuneRotate, vec3(0, 1, 0));
		modelMatrix[NEPTUNE] = translation * rotation * scaling;
	}

	//spawn asteroid on key press
	static int oldState = GLFW_RELEASE;
	int newState = glfwGetKey(window, GLFW_KEY_P);

	//if the asteroid is spawned
	if (asteroidSpawned == true) {
		distanceFromCenterX += xDirection * (deltaTime*(ASTEROID_SPEED*simulationSpeed));
		distanceFromCenterZ += zDirection * (deltaTime*(ASTEROID_SPEED*simulationSpeed));

		asteroidPosition = vec3(distanceFromCenterX, 0, distanceFromCenterZ);
		asteroidRotate = fract(planetRotations / 200.0f) * pi2;

		translation = translate(identity, asteroidPosition);
		scaling = scale(identity, vec3(ASTEROID_SIZE));
		rotation = rotate(identity, asteroidRotate, vec3(0, 1, 0));

		if (distance(asteroidPosition, vec3(0.0f)) > 500.0f) {
			asteroidSpawned = false;
			std::cout << "ASTEROID OUT OF BOUNDS" << std::endl;
		}

		// Check collision with asteroid for each planet in the system
		if (distance(asteroidPosition, vec3(0, 0, 0)) < 5.5f || // Collision with sun
			distance(asteroidPosition, earthPosition) < 0.5f || 
			distance(asteroidPosition, moonPosition) < 0.5f || 
			distance(asteroidPosition, jupiterPosition) < 0.5f || 
			distance(asteroidPosition, mercuryPosition) < 0.5f || 
			distance(asteroidPosition, venusPosition) < 0.5f || 
			distance(asteroidPosition, saturnPosition) < 0.5f || 
			distance(asteroidPosition, uranusPosition) < 0.5f ||
			distance(asteroidPosition, neptunePosition) < 0.5f) 
		{
			scaling = scale(identity, vec3(0.0f));
			asteroidSpawned = false;
			std::cout << "ASTEROID COLLISION!" << std::endl;
		}
		//find the unit vector between the asteroid and the planet/sun * some amount added to the position of the asteroid
		// ATTEMPT AT GRAVITY:
		else if (distance(asteroidPosition, vec3(0,0,0)) < (gravityStrength * 10.0f))
		{
			asteroidPosition += normalize(vec3(0, 0, 0) - asteroidPosition)  * gravityStrength;
		}
		else if (distance(asteroidPosition, earthPosition) < (gravityStrength * 50.0f))
		{
			asteroidPosition += normalize(earthPosition - asteroidPosition)  * gravityStrength;
		}
		// todo: add more planets gravity

		modelMatrix[ASTEROID] = translation * rotation * scaling;

	} else if (newState == GLFW_RELEASE && oldState == GLFW_PRESS && asteroidSpawned == false) {
		//seed the random function
		srand(glfwGetTime());

		//flip a coin for either 1 or 2
		int coinFlip = (rand() % 2) + 1;	
		distanceFromCenterX = ((rand() % 10) + 40) * ((coinFlip == 1) ? -1 : 1); //random number from 40 to 50 or -40 to -50 depending on coin flip
		coinFlip = (rand() % 2) + 1; // flip again for more randomness
		distanceFromCenterZ = ((rand() % 10) + 40) * ((coinFlip == 1) ? -1 : 1); //same as above but for the z-axis

		//calculate the direction of the asteroid (if its moving from + to - or vice versa)
		xDirection = ((distanceFromCenterX > 0) ? -1 : 1);
		zDirection = ((distanceFromCenterZ > 0) ? -1 : 1);

		//set the position/angle/rotation for the asteroid
		asteroidPosition = vec3(distanceFromCenterX, 0, distanceFromCenterZ);
		asteroidRotate = fract(planetRotations / 200.0f) * pi2;
		asteroidAngle = atan(distanceFromCenterX / distanceFromCenterZ);

		translation = translate(identity, asteroidPosition);
		scaling = scale(identity, vec3(ASTEROID_SIZE));
		rotation = rotate(identity, asteroidRotate, vec3(0, 1, 0));
		modelMatrix[ASTEROID] = translation * rotation * scaling;

		asteroidSpawned = true;
		std::cout << "ASTEROID SPAWNED" <<std::endl;
	}
	oldState = newState;
}

void Render()
{
    //------------------------------------------------------------------------------------------------ Draw Skybox

    {
        // Use the special skybox program
        glUseProgram(skyboxProgram);                                    // <- Use the skybox shader program. This has the vertex and fragment  shader for the skybox

        // Getting uniform locations  
        GLuint sLoc = glGetUniformLocation(skyboxProgram, "skybox");    // <- Get the uniform location for the skybox
        GLuint vLoc = glGetUniformLocation(skyboxProgram, "view");      // <- Get the uniform location for the view matrix
        GLuint pLoc = glGetUniformLocation(skyboxProgram, "proj");      // <- Get the uniform location for the projection matrix

        // Binding skybox texture
        glUniform1i(sLoc, 0);                                           // <- 1) Get the uniform location for the cubemap sampler, and set it to index zero                       
        glActiveTexture(GL_TEXTURE0);                                   // <- 2) Set the active texture to also be index zero, matching above                             
        glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxTexture);              // <- 3) Bind the skybox texture. This texture is bound to zero, so it will be sampled              
                                   
        // Passing up view-projection matrix
		glUniformMatrix4fv(vLoc, 1, GL_FALSE, &inverse(viewMatrix)[0][0]);
        glUniformMatrix4fv(pLoc, 1, GL_FALSE, &projectionMatrix[0][0]); // <- Pass through the projection matrix here to the vertex shader
        // Drawing the skybox
        Primitive::DrawSkybox();                                        // <- Draw the skybox here. It's an inverted cube around the camera                                     
                          
        // Unbinding the texture and program
        glBindTexture(GL_TEXTURE_CUBE_MAP, GL_NONE);                    // <- Unbind the texture after we've drawn the skybox here                                  
        glUseProgram(GL_NONE);                                          // <- Unbind the shader program after we've used it here                                    
    }

    //------------------------------------------------------------------------------------------------ Draw Models

    {   //----------------------------------------------------------- EARTH ----------------------------------------------------------------------
        // Use the phong program
        glUseProgram(phongProgram);                                         // <- Use the phong lighting shader program

        // Getting uniform locations
        GLuint dtLoc = glGetUniformLocation(phongProgram, "diffuseTex");    // <- Get the uniform location for the diffuse texture
        GLuint stLoc = glGetUniformLocation(phongProgram, "specularTex");   // <- Get the uniform location for the diffuse texture
        GLuint cLoc = glGetUniformLocation(phongProgram, "cameraPos");      // <- Get the uniform location for the projection matrix
        GLuint mLoc = glGetUniformLocation(phongProgram, "model");          // <- Get the uniform location for the model matrix
        GLuint vLoc = glGetUniformLocation(phongProgram, "view");           // <- Get the uniform location for the view matrix
        GLuint pLoc = glGetUniformLocation(phongProgram, "proj");           // <- Get the uniform location for the projection matrix
        GLuint nLoc = glGetUniformLocation(phongProgram, "norm");           // <- Get the uniform location for the normal matrix
		GLuint specPowLoc = glGetUniformLocation(phongProgram, "specPower");// <- Get the uniform location for the specular power
		//GLuint lightTypeLoc = glGetUniformLocation(phongProgram, "lightType");		// for lab?
       
		// Binding diffuse texture
        glUniform1i(dtLoc, 0);                                              // <- 1) Get the uniform location for the 2D sampler, and set it to index zero                       
        glActiveTexture(GL_TEXTURE0);                                       // <- 2) Set the active texture to also be index zero, matching above                             
        glBindTexture(GL_TEXTURE_2D, earthDiffuseTexture);                       // <- 3) Bind the diffuse texture (bound to index 0)

        // Binding specular texture
        glUniform1i(stLoc, 1);                                                                     
        glActiveTexture(GL_TEXTURE1);                                                           
        glBindTexture(GL_TEXTURE_2D, earthSpecularTexture);                      

        // Passing MVP matrix
        glUniformMatrix4fv(mLoc, 1, GL_FALSE, &modelMatrix[EARTH][0][0]);   // <- Pass through the model matrix here to the vertex shader
        glUniformMatrix4fv(vLoc, 1, GL_FALSE, &inverse(viewMatrix)[0][0]);  // <- Pass through the inverse of the view matrix here to the vertex shader
        glUniformMatrix4fv(pLoc, 1, GL_FALSE, &projectionMatrix[0][0]);     // <- Pass through the projection matrix here to the vertex shader
        glUniformMatrix4fv(nLoc, 1, GL_FALSE,                               // <- Pass through the transpose of the inverse of the model matrix
            &transpose(inverse(modelMatrix[EARTH]))[0][0]);                 //    so that we correctly transform the normals into world space as well
		glUniformMatrix4fv(vLoc, 1, GL_FALSE, &inverse(v)[0][0]);

        // Passing up additional information
        glUniform3fv(cLoc, 1, &cameraPosition[0]);                          // <- Pass through the camera location to the shader
		glUniform1f(specPowLoc, 300.0f);									// <- Pass through the specular power value
		//glUniform1i(lightTypeLoc, 0); // for lab?

        Primitive::DrawSphere();    // Earth

        // Unbinding textures
        glActiveTexture(GL_TEXTURE1);                               // <- Set Texture 1 to be active, and then                
        glBindTexture(GL_TEXTURE_2D, GL_NONE);                      // <- unbind it here
        glActiveTexture(GL_TEXTURE0);                               // <- Set Texture 0 to be active, and then         
        glBindTexture(GL_TEXTURE_2D, GL_NONE);                      // <- unbind it here            

        //----------------------------------------------------------- THE MOON (see above for comments) --------------------------------------------------
		{
			// Binding diffuse texture
			glUniform1i(dtLoc, 0);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, moonTexture);

			// Binding specular texture
			glUniform1i(stLoc, 1);
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, moonTexture);

			// Passing MVP matrix
			glUniformMatrix4fv(mLoc, 1, GL_FALSE, &modelMatrix[MOON][0][0]);
			glUniformMatrix4fv(vLoc, 1, GL_FALSE, &inverse(viewMatrix)[0][0]);
			glUniformMatrix4fv(pLoc, 1, GL_FALSE, &projectionMatrix[0][0]);
			glUniformMatrix4fv(nLoc, 1, GL_FALSE,
				&transpose(inverse(modelMatrix[MOON]))[0][0]);
			glUniformMatrix4fv(vLoc, 1, GL_FALSE, &inverse(v)[0][0]);

			// Passing up additional information
			glUniform3fv(cLoc, 1, &cameraPosition[0]);

			Primitive::DrawSphere();    // Moon

			// Unbinding textures
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, GL_NONE);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, GL_NONE);
		}

		//----------------------------------------------------------- MERCURY ----------------------------------------------------
		{
			// Binding diffuse texture
			glUniform1i(dtLoc, 0);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, mercuryDiffuseTexture);

			// Binding specular texture
			glUniform1i(stLoc, 1);
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, mercurySpecularTexture);

			// Passing MVP matrix
			glUniformMatrix4fv(mLoc, 1, GL_FALSE, &modelMatrix[MERCURY][0][0]);
			glUniformMatrix4fv(vLoc, 1, GL_FALSE, &inverse(viewMatrix)[0][0]);
			glUniformMatrix4fv(pLoc, 1, GL_FALSE, &projectionMatrix[0][0]);
			glUniformMatrix4fv(nLoc, 1, GL_FALSE, &transpose(inverse(modelMatrix[MERCURY]))[0][0]);
			glUniformMatrix4fv(vLoc, 1, GL_FALSE, &inverse(v)[0][0]);

			glUniform3fv(cLoc, 1, &cameraPosition[0]);
			glUniform1f(specPowLoc, 300.0f);

			Primitive::DrawSphere();

			// Unbinding textures
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, GL_NONE);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, GL_NONE);
		}

		//----------------------------------------------------------- VENUS ----------------------------------------------------
		{
			// Binding diffuse texture
			glUniform1i(dtLoc, 0);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, venusDiffuseTexture);

			// Binding specular texture
			glUniform1i(stLoc, 1);
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, venusSpecularTexture);

			// Passing MVP matrix
			glUniformMatrix4fv(mLoc, 1, GL_FALSE, &modelMatrix[VENUS][0][0]);
			glUniformMatrix4fv(vLoc, 1, GL_FALSE, &inverse(viewMatrix)[0][0]);
			glUniformMatrix4fv(pLoc, 1, GL_FALSE, &projectionMatrix[0][0]);
			glUniformMatrix4fv(nLoc, 1, GL_FALSE, &transpose(inverse(modelMatrix[VENUS]))[0][0]);
			glUniformMatrix4fv(vLoc, 1, GL_FALSE, &inverse(v)[0][0]);

			glUniform3fv(cLoc, 1, &cameraPosition[0]);
			glUniform1f(specPowLoc, 300.0f);

			Primitive::DrawSphere();

			// Unbinding textures
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, GL_NONE);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, GL_NONE);
		}

		//----------------------------------------------------------- MARS ----------------------------------------------------
		{
			// Binding diffuse texture
			glUniform1i(dtLoc, 0);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, marsDiffuseTexture);

			// Binding specular texture
			glUniform1i(stLoc, 1);
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, marsSpecularTexture);

			// Passing MVP matrix
			glUniformMatrix4fv(mLoc, 1, GL_FALSE, &modelMatrix[MARS][0][0]);
			glUniformMatrix4fv(vLoc, 1, GL_FALSE, &inverse(viewMatrix)[0][0]);
			glUniformMatrix4fv(pLoc, 1, GL_FALSE, &projectionMatrix[0][0]);
			glUniformMatrix4fv(nLoc, 1, GL_FALSE, &transpose(inverse(modelMatrix[MARS]))[0][0]);
			glUniformMatrix4fv(vLoc, 1, GL_FALSE, &inverse(v)[0][0]);

			glUniform3fv(cLoc, 1, &cameraPosition[0]);
			glUniform1f(specPowLoc, 300.0f);

			Primitive::DrawSphere();

			// Unbinding textures
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, GL_NONE);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, GL_NONE);
		}

		//----------------------------------------------------------- JUPITER ----------------------------------------------------
		{
			// Binding diffuse texture
			glUniform1i(dtLoc, 0);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, jupiterDiffuseTexture);

			// Binding specular texture
			glUniform1i(stLoc, 1);
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, jupiterSpecularTexture);
			
			// Passing MVP matrix
			glUniformMatrix4fv(mLoc, 1, GL_FALSE, &modelMatrix[JUPITER][0][0]);
			glUniformMatrix4fv(vLoc, 1, GL_FALSE, &inverse(viewMatrix)[0][0]);  
			glUniformMatrix4fv(pLoc, 1, GL_FALSE, &projectionMatrix[0][0]);     
			glUniformMatrix4fv(nLoc, 1, GL_FALSE, &transpose(inverse(modelMatrix[JUPITER]))[0][0]);               
			glUniformMatrix4fv(vLoc, 1, GL_FALSE, &inverse(v)[0][0]);

			glUniform3fv(cLoc, 1, &cameraPosition[0]);                          
			glUniform1f(specPowLoc, 300.0f);

			Primitive::DrawSphere();

			// Unbinding textures
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, GL_NONE);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, GL_NONE);

		}

		//----------------------------------------------------------- SATURN ----------------------------------------------------
		{
			// Binding diffuse texture
			glUniform1i(dtLoc, 0);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, saturnDiffuseTexture);

			// Binding specular texture
			glUniform1i(stLoc, 1);
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, saturnSpecularTexture);

			// Passing MVP matrix
			glUniformMatrix4fv(mLoc, 1, GL_FALSE, &modelMatrix[SATURN][0][0]);
			glUniformMatrix4fv(vLoc, 1, GL_FALSE, &inverse(viewMatrix)[0][0]);
			glUniformMatrix4fv(pLoc, 1, GL_FALSE, &projectionMatrix[0][0]);
			glUniformMatrix4fv(nLoc, 1, GL_FALSE, &transpose(inverse(modelMatrix[SATURN]))[0][0]);
			glUniformMatrix4fv(vLoc, 1, GL_FALSE, &inverse(v)[0][0]);

			glUniform3fv(cLoc, 1, &cameraPosition[0]);
			glUniform1f(specPowLoc, 300.0f);

			Primitive::DrawSphere();

			// Unbinding textures
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, GL_NONE);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, GL_NONE);
		}

		//----------------------------------------------------------- URANUS ----------------------------------------------------
		{
			// Binding diffuse texture
			glUniform1i(dtLoc, 0);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, uranusDiffuseTexture);

			// Binding specular texture
			glUniform1i(stLoc, 1);
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, uranusSpecularTexture);

			// Passing MVP matrix
			glUniformMatrix4fv(mLoc, 1, GL_FALSE, &modelMatrix[URANUS][0][0]);
			glUniformMatrix4fv(vLoc, 1, GL_FALSE, &inverse(viewMatrix)[0][0]);
			glUniformMatrix4fv(pLoc, 1, GL_FALSE, &projectionMatrix[0][0]);
			glUniformMatrix4fv(nLoc, 1, GL_FALSE, &transpose(inverse(modelMatrix[URANUS]))[0][0]);
			glUniformMatrix4fv(vLoc, 1, GL_FALSE, &inverse(v)[0][0]);

			glUniform3fv(cLoc, 1, &cameraPosition[0]);
			glUniform1f(specPowLoc, 300.0f);

			Primitive::DrawSphere();

			// Unbinding textures
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, GL_NONE);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, GL_NONE);
		}

		//----------------------------------------------------------- NEPTUNE ----------------------------------------------------
		{
			// Binding diffuse texture
			glUniform1i(dtLoc, 0);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, neptuneDiffuseTexture);

			// Binding specular texture
			glUniform1i(stLoc, 1);
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, neptuneSpecularTexture);

			// Passing MVP matrix
			glUniformMatrix4fv(mLoc, 1, GL_FALSE, &modelMatrix[NEPTUNE][0][0]);
			glUniformMatrix4fv(vLoc, 1, GL_FALSE, &inverse(viewMatrix)[0][0]);
			glUniformMatrix4fv(pLoc, 1, GL_FALSE, &projectionMatrix[0][0]);
			glUniformMatrix4fv(nLoc, 1, GL_FALSE, &transpose(inverse(modelMatrix[NEPTUNE]))[0][0]);
			glUniformMatrix4fv(vLoc, 1, GL_FALSE, &inverse(v)[0][0]);

			glUniform3fv(cLoc, 1, &cameraPosition[0]);
			glUniform1f(specPowLoc, 300.0f);

			Primitive::DrawSphere();

			// Unbinding textures
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, GL_NONE);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, GL_NONE);
		}

		//----------------------------------------------------------- ASTEROID ----------------------------------------------------
		{
			// Binding diffuse texture
			glUniform1i(dtLoc, 0);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, asteroidDiffuseTexture);

			// Binding specular texture
			glUniform1i(stLoc, 1);
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, asteroidSpecularTexture);

			// Passing MVP matrix
			glUniformMatrix4fv(mLoc, 1, GL_FALSE, &modelMatrix[ASTEROID][0][0]);
			glUniformMatrix4fv(vLoc, 1, GL_FALSE, &inverse(viewMatrix)[0][0]);
			glUniformMatrix4fv(pLoc, 1, GL_FALSE, &projectionMatrix[0][0]);
			glUniformMatrix4fv(nLoc, 1, GL_FALSE, &transpose(inverse(modelMatrix[ASTEROID]))[0][0]);
			glUniformMatrix4fv(vLoc, 1, GL_FALSE, &inverse(v)[0][0]);

			glUniform3fv(cLoc, 1, &cameraPosition[0]);
			glUniform1f(specPowLoc, 300.0f);

			if (asteroidSpawned) {
				Primitive::DrawSphere();
			}
			
		}

        // unbinding the shader program
        glUseProgram(GL_NONE);

        //----------------------------------------------------------- THE SUN (see above for comments) ----------------------------------------------------

        glUseProgram(emissiveProgram);                                        

        mLoc = glGetUniformLocation(emissiveProgram, "model");
        vLoc = glGetUniformLocation(emissiveProgram, "view");
        pLoc = glGetUniformLocation(emissiveProgram, "proj");
        GLuint etLoc = glGetUniformLocation(emissiveProgram, "emissiveTex");

        // Binding emissive texture
        glUniform1i(etLoc, 0);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, sunTexture);

        // Passing MVP matrix
        glUniformMatrix4fv(mLoc, 1, GL_FALSE, &modelMatrix[SUN][0][0]);
        glUniformMatrix4fv(vLoc, 1, GL_FALSE, &inverse(viewMatrix)[0][0]);
        glUniformMatrix4fv(pLoc, 1, GL_FALSE, &projectionMatrix[0][0]);
		glUniformMatrix4fv(vLoc, 1, GL_FALSE, &inverse(v)[0][0]);

        Primitive::DrawSphere();    // Sun

        // Unbinding textures
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, GL_NONE);

        // unbinding the shader program
        glUseProgram(GL_NONE);
    }
}

void Cleanup()
{
    // Cleanup the shader programs here
    glDeleteProgram(skyboxProgram);
    glDeleteProgram(phongProgram);

    // Cleanup the textures here
    glDeleteTextures(1, &skyboxTexture);
    glDeleteTextures(1, &earthDiffuseTexture);
    glDeleteTextures(1, &earthSpecularTexture);
}

void GUI()
{
    ImGui::Begin("Assignment 3");
    {
        ImGui::Text("%.1f FPS", ImGui::GetIO().Framerate);
		ImGui::Text("Up         : Space");
		ImGui::Text("Down       : LShift");
		ImGui::Text("Forward    : W");
		ImGui::Text("Backward   : S");
		ImGui::Text("Left       : A");
		ImGui::Text("Right      : D");
		ImGui::Text("Look Up    : Up Arrow");
		ImGui::Text("Look Down  : Down Arrow");
		ImGui::Text("Look Left  : Left Arrow");
		ImGui::Text("Look Right : Right Arrow");
		ImGui::Text(" ");
		ImGui::Text("P          : Spawn Asteroid");
		ImGui::Text("T          : Camera Position");

        ImGui::Spacing();
        ImGui::DragFloat("Simulation Speed", &simulationSpeed, 0.01f, 100.0f); simulationSpeed = clamp(simulationSpeed, 0.01f, 100.0f);
		ImGui::DragFloat("Gravity Strength", &gravityStrength, 9.8f, 30.0f); gravityStrength = clamp(gravityStrength, 0.01f, 30.0f);
		ImGui::DragFloat("Asteroid Size", &ASTEROID_SIZE, 0.35f, 5.0f); ASTEROID_SIZE = clamp(ASTEROID_SIZE, 0.2f, 5.0f);
    }
    ImGui::End();
}

void OnWindowResized(GLFWwindow* win, int w, int h)
{
    // Set the viewport incase the window size changed
    width = w; height = h;
    glViewport(0, 0, width, height);
    float ratio = width / (float)height;
    projectionMatrix = perspective(radians(40.0f), ratio, 0.1f, 1000.0f);
}

void FreeCam(float deltaTime);

int main()
{
    // start GL context and O/S window using the GLFW helper library
    if (!glfwInit()) {
        fprintf(stderr, "ERROR: could not start GLFW3\n");
        return 1;
    }

    window = glfwCreateWindow(width, height, "Assignment 3", NULL, NULL);
    if (!window) {
        fprintf(stderr, "ERROR: could not open window with GLFW3\n");
        glfwTerminate();
        return 1;
    }
    glfwSetWindowSizeCallback(window, OnWindowResized);
    glfwMakeContextCurrent(window);
    glfwSwapInterval(0); // essentially turn off vsync

    // start GL3W
    gl3wInit();

    // Resize at least once
    OnWindowResized(window, width, height);

    // Setup ImGui binding
    ImGui_ImplGlfwGL3_Init(window, true);
    ImGui::StyleColorsLight();

    // get version info
    const GLubyte* renderer = glGetString(GL_RENDERER); // get renderer string
    const GLubyte* version = glGetString(GL_VERSION); // version as a string
    printf("Renderer: %s\n", renderer);
    printf("OpenGL version supported %s\n", version);

    // tell GL to only draw onto a pixel if the shape is closer to the viewer
    glEnable(GL_DEPTH_TEST); // enable depth-testing
    glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
    glEnable(GL_CULL_FACE);
    glDepthFunc(GL_LESS); // depth-testing interprets a smaller value as "closer"

    Initialize();

    float oldTime = 0.0f, currentTime = 0.0f, deltaTime = 0.0f;
    while (!glfwWindowShouldClose(window))
    {
        do { currentTime = (float)glfwGetTime(); } while (currentTime - oldTime < 1.0f / 120.0f);

		FreeCam(deltaTime);


        // update other events like input handling 
        glfwPollEvents();
        
        // Clear the screen
        glClearColor(0.96f, 0.97f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        ImGui_ImplGlfwGL3_NewFrame();

        deltaTime = currentTime - oldTime; // Difference in time
        oldTime = currentTime;
        
        // Call the helper functions
        Update(deltaTime);
        Render();
        GUI();

        // Finish by drawing the GUI
        ImGui::Render();
        glfwSwapBuffers(window);
    }

    // close GL context and any other GLFW resources
    glfwTerminate();
    ImGui_ImplGlfwGL3_Shutdown();
    Cleanup();
    return 0;
}

void FreeCam(float deltaTime)
{
	using namespace glm;

	auto left = vec3(column(v, 0));
	auto up = vec3(column(v, 1));
	auto forward = vec3(column(v, 2));
	cameraPosition = vec3(column(v, 3));

	if (glfwGetKey(window, GLFW_KEY_W)) // Move forward
		cameraPosition -= forward * deltaTime * 18.0f;
	if (glfwGetKey(window, GLFW_KEY_S)) // Move backward
		cameraPosition += forward * deltaTime * 18.0f;
	if (glfwGetKey(window, GLFW_KEY_A)) // Move Left
		cameraPosition -= left * deltaTime * 18.0f;
	if (glfwGetKey(window, GLFW_KEY_D)) // Move right
		cameraPosition += left * deltaTime * 18.0f;
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT))
		cameraPosition -= up * deltaTime * 18.0f;
	if (glfwGetKey(window, GLFW_KEY_SPACE))
		cameraPosition += up * deltaTime * 18.0f;

	if (glfwGetKey(window, GLFW_KEY_LEFT))
	{
		forward = rotate(forward, deltaTime, vec3(0.0f, 2.0f, 0.0f));
		left = rotate(left, deltaTime, vec3(0.0f, 2.0f, 0.0f));
		up = rotate(up, deltaTime, vec3(0.0f, 2.0f, 0.0f));
	}
	if (glfwGetKey(window, GLFW_KEY_RIGHT))
	{
		forward = rotate(forward, -deltaTime, vec3(0.0f, 2.0f, 0.0f));
		left = rotate(left, -deltaTime, vec3(0.0f, 2.0f, 0.0f));
		up = rotate(up, -deltaTime, vec3(0.0f, 2.0f, 0.0f));
	}
	if (glfwGetKey(window, GLFW_KEY_UP))
	{
		forward = rotate(forward, deltaTime, left);
		up = rotate(up, deltaTime, left);
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN))
	{
		forward = rotate(forward, -deltaTime, left);
		up = rotate(up, -deltaTime, left);
	}

	static int oldState = GLFW_RELEASE;
	int newState = glfwGetKey(window, GLFW_KEY_T);
	if (newState == GLFW_RELEASE && oldState == GLFW_PRESS) {
		std::cout << "Camera Position: " << cameraPosition.x << ", " << cameraPosition.y << ", " << cameraPosition.z << std::endl;
	}
	oldState = newState;

	v = mat4(
		left.x, left.y, left.z, 0.0f,  // Col 1
		up.x, up.y, up.z, 0.0f,  // Col 2
		forward.x, forward.y, forward.z, 0.0f,  // Col 3
		cameraPosition.x, cameraPosition.y, cameraPosition.z, 1.0f); // Col 4

	viewMatrix = mat4(
		left.x, left.y, left.z, 0.0f,  // Col 1
		up.x, up.y, up.z, 0.0f,  // Col 2
		forward.x, forward.y, forward.z, 0.0f,  // Col 3
		0.0f, 0.0f, 0.0f, 1.0f); // Col 4
}