#pragma once

#include "Core/Core.h"

class BufferObject {
public:
    BufferObject(GLenum type = GL_ARRAY_BUFFER)
        : type(type)
    {
    }

    void Generate() 
    {
        glGenBuffers(1, &val);
    }

    void Attach() const
    {
        glBindBuffer(type, val);
    }

    template<typename T>
    void SetData(GLuint noElements, T* data, GLenum usage)
    {
        glBufferData(type, noElements * sizeof(T), data, usage);
    }

    template<typename T>
    void SetData(T& data, GLenum usage)
    {
        glBufferData(type, sizeof(data), data, usage);
    }

    template<typename T>
    void UpdateData(GLintptr offset, GLuint noElements, T* data) 
    {
        glBufferSubData(type, offset, noElements * sizeof(T), data);
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
        glBindBuffer(type, 0);
    }

    void Free() const
    {
        glDeleteBuffers(1, &val);
    }

    GLuint val;
    GLenum type;
};

class ArrayObject
{
public:
    BufferObject& operator[](const char* key)
    {
        return buffers[key];
    }

    void Generate() 
    {
        glGenVertexArrays(1, &val);
    }

    void Attach() const
    {
        glBindVertexArray(val);
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
        glDeleteVertexArrays(1, &val);
        for (auto& pair : buffers)
        {
            pair.second.Free();
        }
    }

    static void Detach() 
    {
        glBindVertexArray(0);
    }


    GLuint val;

    std::map<const char*, BufferObject> buffers;
};