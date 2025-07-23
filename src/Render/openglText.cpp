#include "Core/Core.h"
#include "openglText.h"
#include "Core/Error.h"
#include "glfwWindow.h"

openglText::openglText(const Material& material, const Transform& transform, std::string_view message, const int height) : mMaterial(material), mTransform(transform), Message(message.data())
	, mHeight(height)
{

}

void openglText::LoadFont(const std::filesystem::path& path)
{
    FT_Library ft;
    if (FT_Init_FreeType(&ft))
    {
        Error error("Freetype failed to initialize");
    }

    std::string font_name = path.string();
    if (font_name.empty())
    {
        Error error("Freetype failed to load font_name");
    }

    FT_Face face;
    if (FT_New_Face(ft, font_name.c_str(), 0, &face))
    {
        Error error("Freetype failed to load font");
    }
    else
    {
        FT_Set_Pixel_Sizes(face, 0, mHeight);

        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        for (unsigned char c = 0; c < 128; c++)
        {
            if (FT_Load_Char(face, c, FT_LOAD_RENDER))
            {
                Error error("Freetype failed to load glyph");
                continue;
            }
            uint32_t texture;
            glGenTextures(1, &texture);
            glBindTexture(GL_TEXTURE_2D, texture);
            glTexImage2D(
                GL_TEXTURE_2D,
                0,
                GL_RED,
                face->glyph->bitmap.width,
                face->glyph->bitmap.rows,
                0,
                GL_RED,
                GL_UNSIGNED_BYTE,
                face->glyph->bitmap.buffer
            );
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            Character character =
            {
                texture,
                glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
                glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
                static_cast<uint32_t>(face->glyph->advance.x)
            };
            Characters.insert(std::pair<char, Character>(c, character));
        }
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    FT_Done_Face(face);
    FT_Done_FreeType(ft);

    float vertex_data[] =
    {
        0.0f,1.0f,
        0.0f,0.0f,
        1.0f,1.0f,
        1.0f,0.0f
    };

    glGenVertexArrays(1, &mVertexArrayObject);
    glBindVertexArray(mVertexArrayObject);

    glGenBuffers(1, &mVertexBufferOject);
    glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferOject);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_data), vertex_data, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

}

void openglText::RenderFont()
{
    auto copyX = mTransform.GetPosition().x;
    mMaterial.Attach();
    mMaterial.AttachColors();
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(mVertexArrayObject);

    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(glfwWindow::GetSize().Width), 0.0f, static_cast<float>(glfwWindow::GetSize().Height));
    mMaterial.Attach();
    mMaterial.SetMat4("projection", projection);

    std::string::const_iterator c;
    for (c = Message.begin(); c != Message.end(); c++)
    {
        Character ch = Characters[*c];

        if (*c == '\n')
        {
            mTransform.SetPosition(glm::vec3(copyX, mTransform.GetPosition().y -= ((ch.Size.y)) * 1.3 * mTransform.GetScale().x, mTransform.GetPosition().z));
        }
        else if (*c == ' ')
        {
            mTransform.SetPosition(glm::vec3(mTransform.GetPosition().x += ((ch.Advance >> 6)) * mTransform.GetScale().x,mTransform.GetPosition().y,mTransform.GetPosition().z));
        }
        else
        {

            float xpos = mTransform.GetPosition().x + ch.Bearing.x * mTransform.GetScale().x;
            float ypos = mTransform.GetPosition().y - (ch.Size.y - ch.Bearing.y) * mTransform.GetScale().x;

            mWorld = glm::translate(glm::mat4(1.0f), glm::vec3(xpos, ypos, 0.0f)) * glm::scale(glm::mat4(1.0f), glm::vec3(ch.Size.x * mTransform.GetScale().x, ch.Size.y * mTransform.GetScale().x, 0));
            mMaterial.SetMat4("transform", mWorld);

            glBindTexture(GL_TEXTURE_2D, ch.TextureID);
            glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferOject);

            glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, 1);
            mTransform.SetPosition(glm::vec3(mTransform.GetPosition().x += (ch.Advance >> 6) * mTransform.GetScale().x, mTransform.GetPosition().y, mTransform.GetPosition().z));
        }
    }
    mTransform.SetPosition(glm::vec3(copyX, mTransform.GetPosition().y, mTransform.GetPosition().z));

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindTexture(GL_TEXTURE_2D, 0);
}
