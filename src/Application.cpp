#include "Core/Core.h"
#include "Application.h"
#include "Input/Input.h"
#include "Core/ResourceCache.h"

float counter = 0;

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

        if (GInput->KeyWentDown(GLFW_KEY_B))
        {
            /*mBox.GetPositions().push_back(glm::vec3(mBox.GetPositions().size() * 1.0f));
            mBox.GetScales().push_back(glm::vec3(mBox.GetScales().size() * 0.5f));*/
            
        }

        BoxCollider collider = BoxCollider(BoundTypes::AABB, mBox, glm::vec3(0.0, 2.0, 0.0), glm::vec3(0.5));
        mCube.Render(mTexturedMaterial,mGameCamera, mBox, mDeltaTime);


        mColouredMaterial.Attach();
        mColouredMaterial.AttachColors();
        mPlane.Render(mColouredMaterial,mGameCamera, mBox, mDeltaTime);

        mColouredMaterial2.Attach();
        mColouredMaterial2.AttachColors();
        mSphere.Render(mColouredMaterial2, mGameCamera, mBox, mDeltaTime);

        mFireNoiseTexture.Attach();
        glBindTextureUnit(0, mFireNoiseTexture.GetHandle());

        mFireShader.Attach();
        mFireShader.SetFloat("time", counter * 0.1);
        mFireShader.SetInt("uDiffuseSampler", 0);

        mFireCube.Render(mFireShader, mGameCamera, mBox, mDeltaTime);

        mMarbleCube.Render(mMarbleShader, mGameCamera, mBox, mDeltaTime);

        counter += 0.25f;

        if (counter > 2)
        {
            counter = 0;
        }

        mTroll.Render(mTrollMaterial,mGameCamera,mBox,mDeltaTime);

        mM4Material.Attach();
        mM4Material.AttachColors();
        mM4.Render(mM4Material,mGameCamera,mBox,mDeltaTime);

        glm::mat4 view = mGameCamera.GetViewMatrix();
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)glfwWindow::GetSize().Width / (float)glfwWindow::GetSize().Height, 0.1f, 100.0f);

        if (mBox.GetPositions().size() > 0)
        {
            mBox.Render(mBoxShader,mGameCamera);
        }

        glDisable(GL_DEPTH_TEST);


        auto spriteTransform = Transform(glm::vec3(10.0f, 540.0f, 0.0f), glm::vec3(270.0f, 0.0f, 0.0f), glm::vec3(50.0f, 50.0f, 0.0f));
        mTexturedSprite.Render(mSpriteTexturedShader,spriteTransform, mRockTexture);

        mSpriteColoredShader.Attach();
        mSpriteColoredShader.AttachColors();
        spriteTransform = Transform(glm::vec3(glfwWindow::GetSize().Width - 60, 540.0f, 0.0f), glm::vec3(270.0f, 0.0f, 0.0f), glm::vec3(50.0f, 50.0f, 0.0f));
        mColoredSprite.Render(mSpriteColoredShader,spriteTransform);

        //mHelloText.RenderFont();
        mAmmoCounterText.GetComponent<openglText>().RenderFont(mAmmoCounterText.GetComponent<Material>(), mAmmoCounterText.GetComponent<Transform>());

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
    mCube.Init(mTexturedMaterial);
    mPlane.Init(mColouredMaterial);
    mSphere.Init(mColouredMaterial2);
    mBox.Init(mGameCamera);

    mFireCube.Init(mFireShader);
    mMarbleCube.Init(mMarbleShader);

    mTroll.Load("res/Models/Troll","scene.gltf");
    mM4.Load("res/Models/M4A1","scene.gltf");
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

void Application::LoadSprites()
{
    mTexturedSprite.Init(mSpriteTexturedShader);
    mColoredSprite.Init(mSpriteColoredShader);
}

void Application::LoadTexts()
{
    static_cast<Entity&>(mAmmoCounterText) = mActiveLevel.CreateUiTextEntity(Transform(glm::vec3(540.0f, 570.0f, 0.0f), glm::vec3(0.0), glm::vec3(1.0f)),openglText("Ammo 30", 25), Material({ .Red = 1.0,.Green = 1.0,.Blue = 1.0 }, MaterialType::Text));
    mAmmoCounterText.GetComponent<openglText>().LoadFont("res/Fonts/Hey Comic.ttf");
}
