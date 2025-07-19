#include "Application.h"

Application::Application()
{
	Init();
	Update();
}

Application::~Application()
{
}

void Application::Update()
{
	while (!glfwWindowShouldClose(mGameWindow.Get()))
	{
		mGameWindow.Events();

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		mGameWindow.SwapBuffers();
	}
}

void Application::Init()
{
	LoadShaders();
	LoadTextures();
	LoadSounds();
}

void Application::LoadShaders()
{
}

void Application::LoadTextures()
{
}

void Application::LoadSounds()
{
}
