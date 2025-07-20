#include "Core/Core.h"
#include "Material.h"

Material::Material(Color color, const std::vector<openglTexture>& textures) : mColor{}, mMaterialTextures(textures)
{
	if (mMaterialTextures.size() >= 1)
	{
		mShader = openglShader("res/Shaders/BasicTextured.vert", "res/Shaders/BasicTextured.frag");
	}
	else
	{
		mShader = openglShader("res/Shaders/Basic.vert", "res/Shaders/Basic.frag");
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
