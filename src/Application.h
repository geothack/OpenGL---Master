#pragma once

#include "glfwWindow.h"
#include "Render/openglShader.h"

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

	openglShader mBasicShader = openglShader("res/Shaders/Basic.vert", "res/Shaders/Basic.frag");
};

