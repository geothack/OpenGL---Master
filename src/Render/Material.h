#pragma once


#include "Render/openglShader.h"
#include "Render/openglTexture.h"

struct Color
{
	double Red;
	double Green;
	double Blue;
};

class Material
{
public:
	Material(Color color, const std::vector<openglTexture>& textures = std::vector<openglTexture>{});

	void Attach();

	void SetVec3(std::string_view name, const glm::vec3& value) const;

	void SetMat4(std::string_view name, const glm::mat4& value) const;

	void SetInt(std::string_view name, int value) const;

	void SetFloat(std::string_view name, float value) const;

private:
	openglShader mShader;

	glm::vec3 mColor;

	std::vector<openglTexture> mMaterialTextures;
};

