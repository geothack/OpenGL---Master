#pragma once

#include "Core/Core.h"

#include "World/Transform.h"
#include "Render/Material.h"

class Box
{
public:


	void Init()
	{
        mVertices = 
        {
            // position             x   y   z   i
             0.5f,  0.5f,  0.5f, // +   +   +   0
            -0.5f,  0.5f,  0.5f, // -   +   +   1
            -0.5f, -0.5f,  0.5f, // -   -   +   2
             0.5f, -0.5f,  0.5f, // +   -   +   3
             0.5f,  0.5f, -0.5f, // +   +   -   4
            -0.5f,  0.5f, -0.5f, // -   +   -   5
            -0.5f, -0.5f, -0.5f, // -   -   -   6
             0.5f, -0.5f, -0.5f  // +   -   -   7
        };

        mIndices = 
        { // 12 lines
            // front face (+ve z)
            0, 1,
            1, 2,
            2, 3,
            3, 0,
            // back face (-ve z)
            4, 5,
            5, 6,
            6, 7,
            7, 4,
            // right face (+ve x)
            0, 4,
            3, 7,
            // left face (-ve x)
            1, 5,
            2, 6
        };


        glGenVertexArrays(1, &mVertexArrayObject);
        glBindVertexArray(mVertexArrayObject);

        glGenBuffers(1, &mVertexBufferObject);
        glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferObject);
        glBufferData(GL_ARRAY_BUFFER, mVertices.size() * sizeof(float), &mVertices[0], GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glGenBuffers(1, &mOffsetVertexBufferObject);
        glBindBuffer(GL_ARRAY_BUFFER, mOffsetVertexBufferObject);
        glBufferData(GL_ARRAY_BUFFER, 100 * 3 * sizeof(float), NULL, GL_DYNAMIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glGenBuffers(1, &mScaleVertexBufferObject);
        glBindBuffer(GL_ARRAY_BUFFER, mScaleVertexBufferObject);
        glBufferData(GL_ARRAY_BUFFER, 100 * 3 * sizeof(float), NULL, GL_DYNAMIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glGenBuffers(1, &mElementBufferObject);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mElementBufferObject);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, mIndices.size() * sizeof(uint32_t), &mIndices[0], GL_STATIC_DRAW);
        //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferObject);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(0));
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, mOffsetVertexBufferObject);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(0));
        glEnableVertexAttribArray(1);

        glBindBuffer(GL_ARRAY_BUFFER, mScaleVertexBufferObject);
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(0));
        glEnableVertexAttribArray(2);

        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glVertexAttribDivisor(1, 1); // Reset third attrib every 1 instance
        glVertexAttribDivisor(2, 1);

        glBindVertexArray(0);
	}

    void Render(Material& material)
    {
        material.SetMat4("Model", glm::mat4(1.0));

        auto size = std::min(100, static_cast<int>(mTransforms.size()));

        if (size != 0)
        {
            glBindBuffer(GL_ARRAY_BUFFER, mOffsetVertexBufferObject);
            glBufferSubData(GL_ARRAY_BUFFER, 0, size * 3 * sizeof(float), &mTransforms[0].GetPosition());

            glBindBuffer(GL_ARRAY_BUFFER, mScaleVertexBufferObject);
            glBufferSubData(GL_ARRAY_BUFFER, 0, size * 3 * sizeof(float), &mTransforms[0].GetScale());

            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }

        
        glBindVertexArray(mVertexArrayObject);
        glDrawElementsInstanced(GL_LINES, mIndices.size(), GL_UNSIGNED_INT, 0, size);
        glBindVertexArray(0);
        
    }

    void Render(openglShader& shader)
    {
        shader.SetMat4("Model", glm::mat4(1.0));

        auto size = std::min(100, static_cast<int>(mTransforms.size()));

        if (size != 0)
        {
            glBindBuffer(GL_ARRAY_BUFFER, mOffsetVertexBufferObject);
            glBufferSubData(GL_ARRAY_BUFFER, 0, size * 3 * sizeof(float), &mTransforms[0].GetPosition());

            glBindBuffer(GL_ARRAY_BUFFER, mScaleVertexBufferObject);
            glBufferSubData(GL_ARRAY_BUFFER, 0, size * 3 * sizeof(float), &mTransforms[0].GetScale());

            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }


        glBindVertexArray(mVertexArrayObject);
        glDrawElementsInstanced(GL_LINES, mIndices.size(), GL_UNSIGNED_INT, 0, size);
        glBindVertexArray(0);
    }


    void Free()
    {
        glDeleteVertexArrays(1, &mVertexArrayObject);
        glDeleteBuffers(1, &mVertexBufferObject);
        glDeleteBuffers(1, &mElementBufferObject);
        glDeleteBuffers(1, &mOffsetVertexBufferObject);
        glDeleteBuffers(1, &mScaleVertexBufferObject);
    }

    std::vector<Transform>& GetTransforms() { return mTransforms; }

private:
	uint32_t mVertexArrayObject;
	uint32_t mVertexBufferObject;
	uint32_t mElementBufferObject;

	uint32_t mOffsetVertexBufferObject;
	uint32_t mScaleVertexBufferObject;

	std::vector<float> mVertices;
	std::vector<uint32_t> mIndices;

    std::vector<Transform> mTransforms;
};