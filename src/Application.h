#pragma once

#include "glfwWindow.h"

class Application
{
public:
	Application();
	~Application();

private:
	void Update();
	void Init();
	
	void LoadShaders();
	void LoadTextures();
	void LoadSounds();

private:
	glfwWindow mGameWindow = glfwWindow("OpenGL", 800, 600);
};

