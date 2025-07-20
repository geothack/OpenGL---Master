#include "Core/Core.h"
#include "openglSprite.h"

openglSprite::openglSprite(Material& material) : mMaterial(material)
{
	Init();
}

openglSprite::~openglSprite()
{
	glDeleteVertexArrays(1,&mVertexArrayObject);
}

void openglSprite::Render(openglTexture& texture, Transform& transform)
{
    mMaterial.Attach();
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(transform.GetPosition()));  

    model = glm::translate(model, glm::vec3(0.5f * transform.GetScale().x, 0.5f * transform.GetScale().y, 0.0f));
    model = glm::rotate(model, glm::radians(transform.GetRotation().x), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::translate(model, glm::vec3(-0.5f * transform.GetScale().x, -0.5f * transform.GetScale().y, 0.0f));

    model = glm::scale(model, glm::vec3(transform.GetScale())); 

    mMaterial.SetMat4("Model", model);

    texture.Attach();
    glBindTextureUnit(0, texture.GetHandle());

    glBindVertexArray(mVertexArrayObject);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

void openglSprite::Init()
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
}
