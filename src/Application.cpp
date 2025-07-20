#include "Core/Core.h"
#include "Application.h"
#include "Input/Input.h"

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
    glEnable(GL_DEPTH_TEST);

	while (!glfwWindowShouldClose(mGameWindow.Get()))
	{
		mGameWindow.Events();

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        mTexturedMaterial.Attach();

        //mRockTexture.Attach();
        //glBindTextureUnit(0, mRockTexture.GetHandle());

        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 projection = glm::mat4(1.0f);
        projection = glm::perspective(glm::radians(45.0f), (float)800 / (float)600, 0.1f, 100.0f);
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
        mTexturedMaterial.SetMat4("Projection", projection);
        mTexturedMaterial.SetMat4("View", view);

        mCube.Render(mTexturedMaterial);

        mColouredMaterial.Attach();
        mColouredMaterial.AttachColors();
        mColouredMaterial.SetMat4("Projection", projection);
        mColouredMaterial.SetMat4("View", view);
        mPlane.Render(mColouredMaterial);

		mGameWindow.SwapBuffers();
	}

    GInput->Free();
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
