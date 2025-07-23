#include "Core/Core.h"
#include "Material.h"

Material::Material(Color color, MaterialType type, const std::vector<openglTexture>& textures) : mColor{}, mMaterialTextures(textures)
{
	using enum MaterialType;
	if (mMaterialTextures.size() >= 1)
	{
		switch (type)
		{
		case Model3d:
			mShader = openglShader("res/Shaders/BasicTextured.vert", "res/Shaders/BasicTextured.frag");
			break;

		case AssimpModel:
			mShader = openglShader("res/Shaders/Models/AssimpModel.vert", "res/Shaders/Models/AssimpModel.frag");
			break;

		case Sprite2d:
			mShader = openglShader("res/Shaders/Sprites/SpriteTextured.vert", "res/Shaders/Sprites/SpriteTextured.frag");
			break;
		}
	}
	else
	{
		switch (type)
		{
		case Model3d:
			mShader = openglShader("res/Shaders/Basic.vert", "res/Shaders/Basic.frag");
			break;

		case AssimpModel:
			mShader = openglShader("res/Shaders/Models/AssimpModel.vert", "res/Shaders/Models/AssimpModel.frag");
			break;

		case AssimpModelColored:
			mShader = openglShader("res/Shaders/Models/AssimpModelColored.vert", "res/Shaders/Models/AssimpModelColored.frag");
			break;

		case Sprite2d:
			mShader = openglShader("res/Shaders/Sprites/SpriteColored.vert", "res/Shaders/Sprites/SpriteColored.frag");
			break;

		case Text:
			mShader = openglShader("res/Shaders/Fonts/Text.vert", "res/Shaders/Fonts/Text.frag");
			break;
		}
		mColor.x = color.Red;
		mColor.y = color.Green;
		mColor.z = color.Blue;
	}

}

void Material::Attach() const
{
	mShader.Attach();
}

void Material::AttachColors()
{
	mShader.SetVec3("Color", mColor);
}

void Material::AttachTextures()
{
	for (uint32_t i = 0; i < mMaterialTextures.size(); i++)
	{
		mShader.SetInt(mMaterialTextures[i].GetName(), i);
		mMaterialTextures[i].Attach();
		glBindTextureUnit(i, mMaterialTextures[i].GetHandle());
	}
}

void Material::SetVec3(std::string_view name, const glm::vec3& value) const
{
	mShader.SetVec3(name, value);
}

void Material::SetMat4(std::string_view name, const glm::mat4& value) const
{
	mShader.SetMat4(name, value);
}

void Material::SetInt(std::string_view name, int value) const
{
	mShader.SetInt(name, value);
}

void Material::SetFloat(std::string_view name, float value) const
{
	mShader.SetFloat(name, value);
}
