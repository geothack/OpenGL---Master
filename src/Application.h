#pragma once

#include "glfwWindow.h"
#include "Render/openglShader.h"
#include "Render/openglTexture.h"
#include "Models/Cube.h"

class Application
{
public:
	Application();
	~Application();

private:
	void Update();
	void Init();
	
	void LoadMeshes();
	void LoadShaders();
	void LoadTextures();
	void LoadSounds();

private:
	glfwWindow mGameWindow = glfwWindow("OpenGL", 800, 600);

	openglShader mBasicShader = openglShader("res/Shaders/BasicTextured.vert", "res/Shaders/BasicTextured.frag");

	openglTexture mRockTexture = openglTexture("Image","res/Textures/rocks.jpg");

	Cube mCube = Cube(glm::vec3(0.0), glm::vec3(1.0));
};

