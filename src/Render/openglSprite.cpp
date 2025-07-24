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

    mSpriteCamera.Projection = glm::ortho(0.0f, static_cast<float>(glfwWindow::GetSize().Width), static_cast<float>(glfwWindow::GetSize().Height), 0.0f, -1.0f, 1.0f);

    mUniformBuffer.UpdateUBOData("SpriteCamera", 0, glm::value_ptr(mSpriteCamera.Projection), sizeof(mSpriteCamera.Projection));

    if (texture.GetHandle() != 0)
    {
        texture.Attach();
        glBindTextureUnit(0, texture.GetHandle());
    }

    mArrayObject.Attach();
    glDrawArrays(GL_TRIANGLES, 0, 6);
    ArrayObject::Detach();
}

void openglSprite::Init(Material& material)
{
    mArrayObject.Generate();

    mArrayObject["VBO"] = BufferObject(GL_ARRAY_BUFFER);
    mArrayObject["VBO"].Generate();

    float vertices[] =
    {
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f,

        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f
    };


    mArrayObject["VBO"].Attach();
    mArrayObject["VBO"].SetData(vertices, GL_STATIC_DRAW);

    mArrayObject.Attach();
    mArrayObject["VBO"].SetAttPointer<GLfloat>(0, 4, GL_FLOAT, 4, 0);
    mArrayObject["VBO"].Detach();
    ArrayObject::Detach();


    mSpriteCamera.Projection = glm::ortho(0.0f, static_cast<float>(glfwWindow::GetSize().Width), static_cast<float>(glfwWindow::GetSize().Height), 0.0f, -1.0f, 1.0f);

    mUniformBuffer.CreateUBO("SpriteCamera", sizeof(mSpriteCamera), 1);

    mUniformBuffer.UpdateUBOData("SpriteCamera", 0, glm::value_ptr(mSpriteCamera.Projection), sizeof(mSpriteCamera.Projection));

    mUniformBuffer.BindUBOToShader("SpriteCamera", material.GetHandle(), "SpriteCamera");
}
