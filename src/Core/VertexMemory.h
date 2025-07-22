#pragma once

#include "Core/Core.h"

class BufferObject {
public:
    BufferObject(GLenum type = GL_ARRAY_BUFFER)
        : type(type)
    {
    }

    void generate() 
    {
        glGenBuffers(1, &val);
    }

    void Attach()
    {
        glBindBuffer(type, val);
    }

    template<typename T>
    void setData(GLuint noElements, T* data, GLenum usage)
    {
        glBufferData(type, noElements * sizeof(T), data, usage);
    }

    template<typename T>
    void updateData(GLintptr offset, GLuint noElements, T* data) 
    {
        glBufferSubData(type, offset, noElements * sizeof(T), data);
    }

    template<typename T>
    void setAttPointer(GLuint idx, GLint size, GLenum type, GLuint stride, GLuint offset, GLuint divisor = 0)
    {
        glVertexAttribPointer(idx, size, type, GL_FALSE, stride * sizeof(T), (void*)(offset * sizeof(T)));
        glEnableVertexAttribArray(idx);
        if (divisor > 0)
        {
            glVertexAttribDivisor(idx, divisor);
        }
    }

    void Detach()
    {
        glBindBuffer(type, 0);
    }

    void Free() 
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

    void generate() 
    {
        glGenVertexArrays(1, &val);
    }

    void Attach() 
    {
        glBindVertexArray(val);
    }

    void draw(GLenum mode, GLuint first, GLuint count)
    {
        glDrawArrays(mode, first, count);
    }

    void draw(GLenum mode, GLuint count, GLenum type, GLint indices, GLuint instancecount = 1)
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