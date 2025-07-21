#pragma once


#include "Render/openglShader.h"
#include "Render/openglTexture.h"

struct Color
{
	float Red;
	float Green;
	float Blue;
};

enum class MaterialType
{
	None = -1,
	Model3d,
	AssimpModel,
	AssimpModelColored,
	Sprite2d,
};

class Material
{
public:
	Material(Color color, MaterialType type, const std::vector<openglTexture>& textures = std::vector<openglTexture>{});

	void Attach() const;

	void AttachColors();

	void AttachTextures();

	void SetVec3(std::string_view name, const glm::vec3& value) const;

	void SetMat4(std::string_view name, const glm::mat4& value) const;

	void SetInt(std::string_view name, int value) const;

	void SetFloat(std::string_view name, float value) const;

	uint32_t GetHandle() { return mShader.GetProgram(); }

private:
	openglShader mShader;

	glm::vec3 mColor;

	std::vector<openglTexture> mMaterialTextures;
};

