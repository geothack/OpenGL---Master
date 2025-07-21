#include "Core/Core.h"
#include "openglTexture.h"
#include "Core/Error.h"

openglTexture::openglTexture(std::string_view samplerName, const std::filesystem::path& path, bool flip) : mSamplerName(samplerName.data())
{
    glGenTextures(1, &mHandle);
    Load(path, flip);
}

openglTexture::openglTexture(const std::filesystem::path& path, aiTextureType type) : mPath(path), mType(type)
{
    glGenTextures(1, &mHandle);
    Load(path);
}

void openglTexture::Attach() const
{
    glBindTexture(GL_TEXTURE_2D, mHandle);
}

void openglTexture::Load(const std::filesystem::path& path, bool flip)
{
    stbi_set_flip_vertically_on_load(flip);

    auto pathString = path.string();
    unsigned char* data = stbi_load(pathString.c_str(), &mWidth, &mHeight, &mChannels, 0);
    if (data)
    {
        uint32_t format;
        if (mChannels == 1)
        {
            format = GL_RED;
        }
        else if (mChannels == 3)
        {
            format = GL_RGB;
        }
        else if (mChannels == 4)
        {
            format = GL_RGBA;
        }

        glBindTexture(GL_TEXTURE_2D, mHandle);
        glTexImage2D(GL_TEXTURE_2D, 0, format, mWidth, mHeight, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, format == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, format == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::string string = std::format("Failed to load texture at {}", pathString);
        Error error(string);
        stbi_image_free(data);
    }
}
