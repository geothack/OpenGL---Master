#include "Core/Core.h"
#include "openglSprite.h"
#include "glfwWindow.h"

openglSprite::~openglSprite()
{
	//glDeleteVertexArrays(1,&mVertexArrayObject);
}

void openglSprite::Render(Material& material, Transform& transform, const openglTexture& texture)
{
    material.Attach();
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(transform.GetPosition()));  

    model = glm::translate(model, glm::vec3(0.5f * transform.GetScale().x, 0.5f * transform.GetScale().y, 0.0f));
    model = glm::rotate(model, glm::radians(transform.GetRotation().x), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::translate(model, glm::vec3(-0.5f * transform.GetScale().x, -0.5f * transform.GetScale().y, 0.0f));

    model = glm::scale(model, glm::vec3(transform.GetScale())); 

    material.SetMat4("Model", model);

    if (texture.GetHandle() != 0)
    {
        texture.Attach();
        glBindTextureUnit(0, texture.GetHandle());
    }

    glBindVertexArray(mVertexArrayObject);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

void openglSprite::Init(Material& material)
{
    uint32_t vertexBufferObject;
    float vertices[] =
    {
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f,

        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f
    };

    glGenVertexArrays(1, &mVertexArrayObject);
    glGenBuffers(1, &vertexBufferObject);

    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(mVertexArrayObject);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);


    mSpriteCamera.Projection = glm::ortho(0.0f, static_cast<float>(glfwWindow::GetSize().Width), static_cast<float>(glfwWindow::GetSize().Height), 0.0f, -1.0f, 1.0f);

    mUniformBuffer.CreateUBO("SpriteCamera", sizeof(mSpriteCamera), 1);

    mUniformBuffer.UpdateUBOData("SpriteCamera", 0, glm::value_ptr(mSpriteCamera.Projection), sizeof(mSpriteCamera.Projection));

    mUniformBuffer.BindUBOToShader("SpriteCamera", material.GetHandle(), "SpriteCamera");
}
