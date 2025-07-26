#pragma once

#include "glfwWindow.h"
#include "Render/openglShader.h"
#include "Render/openglTexture.h"
#include "Models/Cube.h"
#include "Models/Plane.h"
#include "Render/Material.h"
#include "Render/Camera.h"
#include "Render/openglUniformBuffer.h"
#include "Render/openglSprite.h"
#include "Render/openglText.h"
#include "Models/Sphere.h"
#include "Models/Box.h"
#include "Gameplay/AmmoText.h"
#include "World/Level.h"
#include "Core/imgui.h"

class Application
{
public:
	Application();
	~Application();

private:
	void FixedUpdate();
	void Update();
	void Init();
	
	void LoadMeshes();
	void LoadShaders();
	void LoadTextures();
	void LoadSounds();
	void LoadSprites();
	void LoadTexts();

private:
	glfwWindow mGameWindow = glfwWindow("OpenGL", 800, 600);

	double mDeltaTime = 0.0f;
	double mLastFrame = 0.0f;
	double mTimeStep = 0.0f;

	//openglShader mBasicShader = openglShader("res/Shaders/BasicTextured.vert", "res/Shaders/BasicTextured.frag");

	openglTexture mRockTexture = openglTexture("Image","res/Textures/rocks.jpg");

	Material mTexturedMaterial = Material({ .Red = 0, .Green = 0, .Blue = 0 }, MaterialType::Model3d, { mRockTexture });

	Cube mCube = Cube(Transform(glm::vec3(0.0,2.0,0.0), glm::vec3(1.0f, 0.3f, 0.5f),glm::vec3(0.5)),mGameCamera);

	Material mColouredMaterial = Material({ .Red = 0.89, .Green = 0.67, .Blue = 0.340 }, MaterialType::Model3d);

	Plane mPlane = Plane(Transform(),mGameCamera);

	Camera mGameCamera = Camera(glm::vec3(0.0,0.0,12.0));

	openglUniformBuffer mUniformBuffer;

	Material mSpriteTexturedShader = Material({ .Red = 0.0, .Green = 0.0, .Blue = 0.0 }, MaterialType::Sprite2d, { mRockTexture });

	openglSprite mTexturedSprite = openglSprite{};

	Material mSpriteColoredShader = Material({ .Red = 0.59, .Green = 0.79, .Blue = 0.28 }, MaterialType::Sprite2d);

	openglSprite mColoredSprite = openglSprite{};

	Material mTrollMaterial = Material({ .Red = 0.59, .Green = 0.79, .Blue = 0.28 }, MaterialType::AssimpModel);

	Model mTroll = Model(Transform(glm::vec3(5.0,1.0f,0.0f),glm::vec3(0.0,0,0.0),glm::vec3(0.01)),mGameCamera);

	Material mM4Material = Material({ .Red = 0.59, .Green = 0.79, .Blue = 0.88 }, MaterialType::AssimpModelColored);

	Model mM4 = Model(Transform(glm::vec3(-5.0, 1.0f, 0.0f), glm::vec3(0.0), glm::vec3(0.01)),mGameCamera);



	Material mTextMaterial = Material({ .Red = 1.0,.Green = 1.0,.Blue = 1.0 }, MaterialType::Text);
	//openglText mHelloText = openglText(mTextMaterial, Transform(glm::vec3(540.0f, 570.0f, 0.0f), glm::vec3(0.0), glm::vec3(1.0f)), "Hello World", 25);



	Material mColouredMaterial2 = Material({ .Red = 0.29, .Green = 0.57, .Blue = 0.90 }, MaterialType::Model3d);
	Sphere mSphere = Sphere(Transform(glm::vec3(-2.5,2.0,0.0),glm::vec3(0.0),glm::vec3(0.05)),mGameCamera);

	openglShader instancedShader = openglShader("res/Shaders/Models/ModelInstanced.vert", "res/Shaders/Models/ModelInstanced.frag");
	openglShader mBoxShader = openglShader("res/Shaders/Models/Box.vert", "res/Shaders/Models/Box.frag");

	openglShader mFireShader = openglShader("res/Shaders/Noise/Fire.vert","res/Shaders/Noise/Fire.frag");
	openglTexture mFireNoiseTexture = openglTexture("uDiffuseSampler","res/Textures/flame.png");
	Cube mFireCube = Cube(Transform(glm::vec3(-4.5, 2.5, 0.0), glm::vec3(0.0,0.0,180), glm::vec3(0.5)), mGameCamera);

	openglShader mMarbleShader = openglShader("res/Shaders/Noise/Marble.vert", "res/Shaders/Noise/Marble.frag");
	Cube mMarbleCube = Cube(Transform(glm::vec3(2.5, 0.5, 5.0), glm::vec3(0.0, 0.0, 1), glm::vec3(0.5)), mGameCamera);

	Box mBox{};

	// Levels
	Level mActiveLevel{};

	// Gameplay Entities
	AmmoText mAmmoCounterText{};

	imgui mImGui = imgui(mGameWindow);

	bool mRenderImGui = false;

};

