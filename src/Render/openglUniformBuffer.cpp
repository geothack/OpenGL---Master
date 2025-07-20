#include "Core/Core.h"
#include "openglUniformBuffer.h"
#include "Core/Error.h"


openglUniformBuffer::openglUniformBuffer()
{
}

void openglUniformBuffer::CreateUBO(std::string_view handle, size_t size, GLuint bindingPoint)
{
    if (mUniformBufferCache.find(handle.data()) != mUniformBufferCache.end())
    {
        Error error("Uniform buffer already exists");
        return;
    }

    GLuint ubo;
    glGenBuffers(1, &ubo); 
    glBindBuffer(GL_UNIFORM_BUFFER, ubo);
    glBufferData(GL_UNIFORM_BUFFER, size, nullptr, GL_DYNAMIC_DRAW); 
    glBindBufferBase(GL_UNIFORM_BUFFER, bindingPoint, ubo);
    glBindBuffer(GL_UNIFORM_BUFFER, 0); 

    mUniformBufferCache[handle.data()] = {ubo, size, bindingPoint};
}

void openglUniformBuffer::UpdateUBOData(std::string_view handle, size_t offset, const void* data, size_t dataSize)
{
    if (mUniformBufferCache.find(handle.data()) == mUniformBufferCache.end())
    {
        Error error("Uniform buffer not found");
        return;
    }

    glBindBuffer(GL_UNIFORM_BUFFER, mUniformBufferCache[handle.data()].Handle);
    glBufferSubData(GL_UNIFORM_BUFFER, offset, dataSize, data);
    glBindBuffer(GL_UNIFORM_BUFFER, 0); 
}

void openglUniformBuffer::BindUBOToShader(std::string_view handle, GLuint shaderID, const std::string& uboName)
{
    if (mUniformBufferCache.find(handle.data()) == mUniformBufferCache.end())
    {
        Error error("Uniform buffer not found");
        return;
    }

    GLuint blockIndex = glGetUniformBlockIndex(shaderID, uboName.c_str());

    if (blockIndex == GL_INVALID_INDEX)
    {
        Error error("Uniform buffer not found in shader");
        return;
    }

    glUniformBlockBinding(shaderID, blockIndex, mUniformBufferCache[handle.data()].BindingPoint);
}

void openglUniformBuffer::Free()
{
    for (auto& [tag, uboData] : mUniformBufferCache)
    {
        glDeleteBuffers(1, &uboData.Handle);
    }
    mUniformBufferCache.clear();
}
