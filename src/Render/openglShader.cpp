#include "Core/Core.h"
#include "openglShader.h"

openglShader::openglShader(const std::filesystem::path& vertexShaderPath, const std::filesystem::path& fragShaderPath, const std::filesystem::path& geoShaderPath)
{
	if (geoShaderPath.empty())
	{
		MakeShader(vertexShaderPath, fragShaderPath);
	}
	else
	{
		MakeShader(vertexShaderPath, fragShaderPath, geoShaderPath);
	}

	::GLint uniformCount{};
	::glGetProgramiv(mProgram, GL_ACTIVE_UNIFORMS, &uniformCount);

	if (uniformCount != 0)
	{
		::GLint maxNameLength{};
		::glGetProgramiv(mProgram, GL_ACTIVE_UNIFORM_MAX_LENGTH, &maxNameLength);

		::GLsizei length{};
		::GLsizei count{};
		::GLenum type{};

		for (auto i = 0; i < uniformCount; i++)
		{
			std::string name(maxNameLength, '\O');
			::glGetActiveUniform(mProgram, i, maxNameLength, &length, &count, &type, name.data());

			name.resize(length);

			const auto location = ::glGetUniformLocation(mProgram, name.c_str());

			mUniformCache[name] = location;
		}
	}
}

void openglShader::MakeShader(const std::filesystem::path& vertexShaderPath, const std::filesystem::path& fragShaderPath, const std::filesystem::path& geoShaderPath)
{
	if (geoShaderPath.empty())
	{
		Create(mVertex, vertexShaderPath.string().c_str(), GL_VERTEX_SHADER);
		Create(mFragment, fragShaderPath.string().c_str(), GL_FRAGMENT_SHADER);
		LinkShader();
	}
	else
	{
		Create(mVertex, vertexShaderPath.string().c_str(), GL_VERTEX_SHADER);
		Create(mFragment, fragShaderPath.string().c_str(), GL_FRAGMENT_SHADER);
		Create(mGeometry, fragShaderPath.string().c_str(), GL_GEOMETRY_SHADER);
		LinkShader();
	}
}

void openglShader::Attach() const
{
	glUseProgram(mProgram);
}

void openglShader::SetVec3(std::string_view name, const glm::vec3& value) const
{
	const auto uniform = mUniformCache.find(name.data());
	const auto string = std::format("Failed to find uniform {}", name);
	//Verify::Update(string, uniform != std::ranges::cend(mUniformCache));

	::glUniform3fv(uniform->second, 1, &value[0]);
}

void openglShader::SetMat4(std::string_view name, const glm::mat4& value) const
{
	const auto uniform = mUniformCache.find(name.data());
	const auto string = std::format("Failed to find uniform {}", name);
	//Verify::Update(string, uniform != std::ranges::cend(mUniformCache));

	::glUniformMatrix4fv(uniform->second, 1, GL_FALSE, glm::value_ptr(value));
}

void openglShader::SetInt(std::string_view name, int value) const
{
	const auto uniform = mUniformCache.find(name.data());
	const auto string = std::format("Failed to find uniform {}", name);
	//Verify::Update(string, uniform != std::ranges::cend(mUniformCache));

	::glUniform1i(uniform->second, value);
}

void openglShader::SetFloat(std::string_view name, float value) const
{
	const auto uniform = mUniformCache.find(name.data());
	const auto string = std::format("Failed to find uniform {}", name);
	//Verify::Update(string, uniform != std::ranges::cend(mUniformCache));

	::glUniform1f(uniform->second, value);
}

void openglShader::Create(uint32_t& shader, const char* path, uint32_t type)
{
	std::ifstream file;

	std::stringstream ssfile;

	std::string code;

	file.open(path);
	std::stringstream vShaderStream;
	ssfile << file.rdbuf();

	file.close();
	code = ssfile.str();
	const char* glShader = code.c_str();

	shader = glCreateShader(type);
	glShaderSource(shader, 1, &glShader, NULL);
	glCompileShader(shader);

	glGetShaderiv(shader, GL_COMPILE_STATUS, &mSuccess);

	glGetShaderInfoLog(shader, 512, NULL, mInfoLog);
	std::string error = std::format("Failed to compile shader {}", mInfoLog);

	//Verify::Update(error, mSuccess);

}

void openglShader::LinkShader()
{
	mProgram = glCreateProgram();
	glAttachShader(mProgram, mVertex);
	glAttachShader(mProgram, mFragment);
	glLinkProgram(mProgram);

	glGetProgramiv(mProgram, GL_LINK_STATUS, &mSuccess);

	glGetProgramInfoLog(mProgram, 512, NULL, mInfoLog);
	std::string error = std::format("Failed to link program {}", mInfoLog);

	//Verify::Update(error, mSuccess);

	glDeleteShader(mVertex);
	glDeleteShader(mFragment);
}