#pragma once
class openglShader
{
public:
    openglShader() = default;

    openglShader(const std::filesystem::path& vertexShaderPath, const std::filesystem::path& fragShaderPath, const std::filesystem::path& geoShaderPath = "");

    void MakeShader(const std::filesystem::path& vertexShaderPath, const std::filesystem::path& fragShaderPath, const std::filesystem::path& geoShaderPath = "");

    void Attach() const;

public:
    void SetVec3(std::string_view name, const glm::vec3& value) const;

    void SetMat4(std::string_view name, const glm::mat4& value) const;

    void SetInt(std::string_view name, int value) const;

    void SetFloat(std::string_view name, float value) const;

public:
    inline uint32_t GetProgram() const { return mProgram; }

private:
    void Create(uint32_t& shader, const char* path, uint32_t type);

    void LinkShader();

private:
    uint32_t mProgram{};
    uint32_t mVertex{};
    uint32_t mFragment{};
    uint32_t mGeometry{};


    int mSuccess{};
    char mInfoLog[512];

    std::unordered_map<std::string, ::uint32_t> mUniformCache;
};

