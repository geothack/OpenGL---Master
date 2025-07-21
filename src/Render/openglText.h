#pragma once


#include "Render/Material.h"
#include "World/Transform.h"

struct Character
{
	uint32_t TextureID;
	glm::ivec2   Size;
	glm::ivec2   Bearing;
	uint32_t Advance;
};

class openglText
{
public:
	openglText() = default;
	openglText(const openglShader& shader, const Transform& transform, std::string_view message, const int height, Color color);
	~openglText() = default;

	void LoadFont(const std::filesystem::path& path);
	void RenderFont();

	std::string Message = "";

	std::map<GLchar, Character> Characters;

	uint32_t GetVertexArray() { return mVertexArrayObject; }
	uint32_t GetVertexBuffer() { return mVertexBufferOject; }

private:
	openglShader mShader;
	Transform mTransform;

	glm::mat4 mWorld;

	glm::vec3 mColor;

	uint32_t mVertexArrayObject;
	uint32_t mVertexBufferOject;

	int mHeight;
};

