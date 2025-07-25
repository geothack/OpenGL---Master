#include "Core/Core.h"
#include "openglText.h"
#include "Core/Error.h"
#include "glfwWindow.h"

openglText::openglText(std::string_view message, const int height) : Message(message.data()), mHeight(height)
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

    mArrayObject.Generate();
    mArrayObject.Attach();

    mArrayObject["VBO"].Generate();
    mArrayObject["VBO"].Attach();
    mArrayObject["VBO"].SetData(vertex_data,GL_STATIC_DRAW);
    //glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_data), vertex_data, GL_STATIC_DRAW);


    mArrayObject["VBO"].SetAttPointer<GLfloat>(0, 2, GL_FLOAT, 0, 0);
    mArrayObject["VBO"].Detach();
    ArrayObject::Detach();
   

}

void openglText::RenderFont(Material& material, Transform& transform)
{
    auto copyX = transform.GetPosition().x;
    material.Attach();
    material.AttachColors();
    glActiveTexture(GL_TEXTURE0);
    mArrayObject.Attach();

    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(glfwWindow::GetSize().Width), 0.0f, static_cast<float>(glfwWindow::GetSize().Height));
    material.Attach();
    material.SetMat4("projection", projection);

    std::string::const_iterator c;
    for (c = Message.begin(); c != Message.end(); c++)
    {
        Character ch = Characters[*c];

        if (*c == '\n')
        {
            transform.SetPosition(glm::vec3(copyX, transform.GetPosition().y -= ((ch.Size.y)) * 1.3 * transform.GetScale().x, transform.GetPosition().z));
        }
        else if (*c == ' ')
        {
            transform.SetPosition(glm::vec3(transform.GetPosition().x += ((ch.Advance >> 6)) * transform.GetScale().x,transform.GetPosition().y,transform.GetPosition().z));
        }
        else
        {

            float xpos = transform.GetPosition().x + ch.Bearing.x * transform.GetScale().x;
            float ypos = transform.GetPosition().y - (ch.Size.y - ch.Bearing.y) * transform.GetScale().x;

            mWorld = glm::translate(glm::mat4(1.0f), glm::vec3(xpos, ypos, 0.0f)) * glm::scale(glm::mat4(1.0f), glm::vec3(ch.Size.x * transform.GetScale().x, ch.Size.y * transform.GetScale().x, 0));
            material.SetMat4("transform", mWorld);

            glBindTexture(GL_TEXTURE_2D, ch.TextureID);
            mArrayObject["VBO"].Attach();

            glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, 1);
            transform.SetPosition(glm::vec3(transform.GetPosition().x += (ch.Advance >> 6) * transform.GetScale().x, transform.GetPosition().y, transform.GetPosition().z));
        }
    }
    transform.SetPosition(glm::vec3(copyX, transform.GetPosition().y, transform.GetPosition().z));

    ArrayObject::Detach();
    mArrayObject["VBO"].Detach();
    glBindTexture(GL_TEXTURE_2D, 0);
}
