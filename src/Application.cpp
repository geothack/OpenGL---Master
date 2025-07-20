#include "Core/Core.h"
#include "Application.h"
#include "Input/Input.h"

struct CameraData
{
    alignas(16) glm::mat4 Projection;
    alignas(16) glm::mat4 View;
};

CameraData cameraData;

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
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

       
        if (GInput->KeyWentDown(GLFW_KEY_A))
        {
            mGameCamera.MoveLeft(-1.0f);
        }

        if (GInput->KeyWentDown(GLFW_KEY_D))
        {
            mGameCamera.MoveLeft(1.0f);
        }

        if (GInput->KeyWentDown(GLFW_KEY_W))
        {
            mGameCamera.MoveForward(-1.0f);
        }

        if (GInput->KeyWentDown(GLFW_KEY_S))
        {
            mGameCamera.MoveForward(1.0f);
        }

        if (GInput->KeyWentDown(GLFW_KEY_SPACE))
        {
            mGameCamera.MoveUp(1.0f);
        }

        mTexturedMaterial.Attach();

        cameraData.View = mGameCamera.GetViewMatrix();
        
        mUniformBuffer.UpdateUBOData("CameraData", sizeof(cameraData.View), glm::value_ptr(cameraData.View), sizeof(cameraData.View));
        


        mCube.Render(mTexturedMaterial);

        mColouredMaterial.Attach();
        mColouredMaterial.AttachColors();
        

        mPlane.Render(mColouredMaterial);

        glDisable(GL_DEPTH_TEST);

        glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(800), static_cast<float>(600), 0.0f, -1.0f, 1.0f);

        mSpriteShader.Attach();
        mSpriteShader.SetMat4("Projection", projection);

        auto spriteTransform = Transform(glm::vec3(10.0f, 540.0f, 0.0f), glm::vec3(270.0f,0.0f,0.0f), glm::vec3(50.0f, 50.0f, 0.0f));

        mTexturedSprite.Render(mRockTexture, spriteTransform);

        glEnable(GL_DEPTH_TEST);

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
    cameraData.View = mGameCamera.GetViewMatrix();
    cameraData.Projection = glm::perspective(glm::radians(45.0f), (float)800 / (float)600, 0.1f, 100.0f);

    mUniformBuffer.CreateUBO("CameraData", sizeof(CameraData), 1);

    mUniformBuffer.UpdateUBOData("CameraData", 0, glm::value_ptr(cameraData.Projection), sizeof(cameraData.Projection));
    mUniformBuffer.UpdateUBOData("CameraData", sizeof(cameraData.View), glm::value_ptr(cameraData.View), sizeof(cameraData.View));

    mUniformBuffer.BindUBOToShader("CameraData", mTexturedMaterial.GetHandle(), "Camera");
    mUniformBuffer.BindUBOToShader("CameraData", mColouredMaterial.GetHandle(), "Camera");
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
