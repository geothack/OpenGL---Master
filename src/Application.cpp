#include "Core/Core.h"
#include "Application.h"

uint32_t VAO;

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

        mBasicShader.Attach();
        glBindVertexArray(VAO); 
        glDrawArrays(GL_TRIANGLES, 0, 3);

		mGameWindow.SwapBuffers();
	}
}

void Application::Init()
{
    LoadMeshes();
	LoadShaders();
	LoadTextures();
	LoadSounds();
}

void Application::LoadMeshes()
{
    float vertices[] = {
        -0.5f, -0.5f, 0.0f, 
         0.5f, -0.5f, 0.0f, 
         0.0f,  0.5f, 0.0f  
    };

    unsigned int VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
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
