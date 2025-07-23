#include "Core/Core.h"
#include "Application.h"
#include "Input/Input.h"
#include "Core/ResourceCache.h"

Application::Application()
{
	Init();
	Update();
}

Application::~Application()
{
}

void Application::FixedUpdate()
{
    mTimeStep += mDeltaTime * 150.0f;
    while (mTimeStep >= mGameWindow.GetVideoMode()->refreshRate)
    {
        mTimeStep -= mGameWindow.GetVideoMode()->refreshRate;

        // Run entity fixed update here
    }
}

void Application::Update()
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	while (!glfwWindowShouldClose(&mGameWindow.Get()))
	{
		mGameWindow.Events();

        double currentTime = glfwGetTime();
        mDeltaTime = currentTime - mLastFrame;
        mLastFrame = currentTime;

        FixedUpdate();

        mBox.GetPositions().clear();
        mBox.GetScales().clear();

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

        if (GInput->KeyWentDown(GLFW_KEY_LEFT_SHIFT))
        {
            mGameCamera.MoveUp(-1.0f);
        }

        /*if (GInput->KeyWentDown(GLFW_KEY_B))
        {
            mBox.GetPositions().push_back(glm::vec3(mBox.GetPositions().size() * 1.0f));
            mBox.GetScales().push_back(glm::vec3(mBox.GetScales().size() * 0.5f));
        }*/


        mCube.Render(mTexturedMaterial,mGameCamera, mBox, mDeltaTime);


        mColouredMaterial.Attach();
        mColouredMaterial.AttachColors();
        mPlane.Render(mColouredMaterial,mGameCamera, mBox, mDeltaTime);

        mColouredMaterial2.Attach();
        mColouredMaterial2.AttachColors();
        mSphere.Render(mColouredMaterial2, mGameCamera, mBox, mDeltaTime);


        glm::mat4 view = mGameCamera.GetViewMatrix();
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)glfwWindow::GetSize().Width / (float)glfwWindow::GetSize().Height, 0.1f, 100.0f);

        mTrollMaterial.Attach();
        mTrollMaterial.SetMat4("View",view);
        mTrollMaterial.SetMat4("Projection",projection);

        mTroll.Render(mTrollMaterial,mBox,mDeltaTime);

        mM4Material.Attach();
        mM4Material.SetMat4("View", view);
        mM4Material.SetMat4("Projection", projection);
        mM4Material.AttachColors();

        mM4.Render(mM4Material,mBox,mDeltaTime);

        if (mBox.GetPositions().size() > 0)
        {
            mBoxShader.Attach();
            mBoxShader.SetMat4("View", view);
            mBoxShader.SetMat4("Projection", projection);

            mBox.Render(mBoxShader);
        }

        glDisable(GL_DEPTH_TEST);


        auto spriteTransform = Transform(glm::vec3(10.0f, 540.0f, 0.0f), glm::vec3(270.0f, 0.0f, 0.0f), glm::vec3(50.0f, 50.0f, 0.0f));
        mTexturedSprite.Render(mSpriteTexturedShader,spriteTransform, mRockTexture);

        mSpriteColoredShader.Attach();
        mSpriteColoredShader.AttachColors();
        spriteTransform = Transform(glm::vec3(glfwWindow::GetSize().Width - 60, 540.0f, 0.0f), glm::vec3(270.0f, 0.0f, 0.0f), glm::vec3(50.0f, 50.0f, 0.0f));
        mColoredSprite.Render(mSpriteColoredShader,spriteTransform);

        mHelloText.RenderFont();

        glEnable(GL_DEPTH_TEST);

		mGameWindow.SwapBuffers();
	}

    mBox.Free();
    Cache.Free();
    GInput->Free();
    mCube.Free();
    mPlane.Free();
    mSphere.Free();
}

void Application::Init()
{
    LoadSprites();
    LoadTextures();
	LoadShaders();
    LoadMeshes();
	LoadSounds();
    LoadTexts();
}

void Application::LoadMeshes()
{
    mCube.Init(mTexturedMaterial, mGameCamera);
    mPlane.Init(mColouredMaterial, mGameCamera);
    mSphere.Init(mColouredMaterial2, mGameCamera);
    mBox.Init();

    mTroll.Load("res/Models/Troll","scene.gltf");
    mM4.Load("res/Models/M4A1","scene.gltf");
}

void Application::LoadShaders()
{
    // 3D
    Cache.Insert<Material>("Textured", Material({ .Red = 0.0, .Green = 0.0, .Blue = 0.0 }, MaterialType::Model3d, { Cache.Find<openglTexture>("Rock") }));
    Cache.Insert<Material>("Colored", Material({ .Red = 0.89, .Green = 0.67, .Blue = 0.340 }, MaterialType::Model3d));
    // 2D
    Cache.Insert<Material>("SpriteTextured", Material({ .Red = 0.0, .Green = 0.0, .Blue = 0.0 }, MaterialType::Sprite2d, { Cache.Find<openglTexture>("Rock") }));
    Cache.Insert<Material>("SpriteColored", Material({ .Red = 0.0, .Green = 0.0, .Blue = 0.0 }, MaterialType::Sprite2d));
}

void Application::LoadTextures()
{
    Cache.Insert<openglTexture>("Rock", openglTexture("Image", "res/Textures/rocks.jpg"));
}

void Application::LoadSounds()
{
}

void Application::LoadSprites()
{
    Cache.Insert<openglSprite>("Sprite", openglSprite{});
    mTexturedSprite.Init(mSpriteTexturedShader);
    mColoredSprite.Init(mSpriteColoredShader);
}

void Application::LoadTexts()
{
    mHelloText.LoadFont("res/Fonts/Hey Comic.ttf");
}
