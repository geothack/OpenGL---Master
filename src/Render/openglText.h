#pragma once


#include "Render/Material.h"
#include "World/Transform.h"
#include "Core/VertexMemory.h"

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
	openglText(const Material& material, const Transform& transform, std::string_view message, const int height);
	~openglText() = default;

	void LoadFont(const std::filesystem::path& path);
	void RenderFont();

	std::string Message = "";

	std::map<GLchar, Character> Characters;

	GLuint GetVertexArray() { return mArrayObject.val; }
	GLuint GetVertexBuffer() { return mArrayObject["VBO"].val; }

private:
	Material mMaterial;
	Transform mTransform;

	glm::mat4 mWorld;

	ArrayObject mArrayObject;

	int mHeight;
};

