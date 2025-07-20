#pragma once


class openglUniformBuffer
{
public:
	openglUniformBuffer();

    void CreateUBO(std::string_view handle, size_t size, GLuint bindingPoint);
    void UpdateUBOData(std::string_view handle, size_t offset, const void* data, size_t dataSize);
    void BindUBOToShader(std::string_view handle, GLuint shaderID, const std::string& uboName);

    void Free(); 

private:
    struct UBOData 
    {
        GLuint Handle;
        size_t Size;
        GLuint BindingPoint;
    };

    std::unordered_map<std::string, UBOData> mUniformBufferCache;
};

