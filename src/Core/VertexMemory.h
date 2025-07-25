#pragma once

#include "Core/Core.h"

class BufferObject {
public:
    BufferObject(GLenum type = GL_ARRAY_BUFFER)
        : mType(type)
    {
    }

    void Generate() 
    {
        glGenBuffers(1, &mVal);
    }

    void Attach() const
    {
        glBindBuffer(mType, mVal);
    }

    template<typename T>
    void SetData(GLuint noElements, T* data, GLenum usage)
    {
        glBufferData(mType, noElements * sizeof(T), data, usage);
    }

    template<typename T>
    void SetData(T& data, GLenum usage)
    {
        glBufferData(mType, sizeof(data), data, usage);
    }

    template<typename T>
    void UpdateData(GLintptr offset, GLuint noElements, T* data) 
    {
        glBufferSubData(mType, offset, noElements * sizeof(T), data);
    }

    template<typename T>
    void SetAttPointer(GLuint idx, GLint size, GLenum type, GLuint stride, GLuint offset, GLuint divisor = 0)
    {
        glVertexAttribPointer(idx, size, type, GL_FALSE, stride * sizeof(T), (void*)(offset * sizeof(T)));
        glEnableVertexAttribArray(idx);
        if (divisor > 0)
        {
            glVertexAttribDivisor(idx, divisor);
        }
    }

    void Detach() const
    {
        glBindBuffer(mType, 0);
    }

    void Free() const
    {
        glDeleteBuffers(1, &mVal);
    }

    GLuint mVal;
    GLenum mType;
};

class ArrayObject
{
public:
    BufferObject& operator[](const char* key)
    {
        return mBuffers[key];
    }

    void Generate() 
    {
        glGenVertexArrays(1, &mVal);
    }

    void Attach() const
    {
        glBindVertexArray(mVal);
    }

    void Draw(GLenum mode, GLuint first, GLuint count) const
    {
        glDrawArrays(mode, first, count);
    }

    void Draw(GLenum mode, GLuint count, GLenum type, GLint indices, GLuint instancecount = 1) const
    {
        glDrawElementsInstanced(mode, count, type, (void*)indices, instancecount);
    }

    void Free() 
    {
        glDeleteVertexArrays(1, &mVal);
        for (auto& pair : mBuffers)
        {
            pair.second.Free();
        }
    }

    static void Detach() 
    {
        glBindVertexArray(0);
    }


    GLuint mVal;

    std::map<const char*, BufferObject> mBuffers;
};