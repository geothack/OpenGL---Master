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
