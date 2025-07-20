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

	//openglShader mBasicShader = openglShader("res/Shaders/BasicTextured.vert", "res/Shaders/BasicTextured.frag");

	openglTexture mRockTexture = openglTexture("Image","res/Textures/rocks.jpg");

	Material mTexturedMaterial = Material({ .Red = 0, .Green = 0, .Blue = 0 }, { mRockTexture });

	Cube mCube = Cube(Transform(glm::vec3(0.0,2.0,0.0), glm::vec3(1.0f, 0.3f, 0.5f),glm::vec3(0.5)));

	Material mColouredMaterial = Material({ .Red = 0.89, .Green = 0.67, .Blue = 0.340 });

	Plane mPlane = Plane(Transform());

	Camera mGameCamera = Camera(glm::vec3(0.0,0.0,12.0));

	openglUniformBuffer mUniformBuffer;

	openglShader mSpriteShader = openglShader("res/Shaders/Sprites/SpriteTextured.vert", "res/Shaders/Sprites/SpriteTextured.frag");

	openglSprite mTexturedSprite = openglSprite(mSpriteShader);
};

