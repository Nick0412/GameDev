#ifndef UNIFORM_H
#define UNIFORM_H

#include "glad/glad.h"

namespace CoreGL
{
    class Uniform
    {
    private:
        GLint m_location;

    public:
        Uniform() = delete;
        Uniform(const GLint location);

        GLint getLocation() const;

    public:
        template<typename T>
        void setVector(GLuint program, const T& value, GLsizei count = 1) const;

        template<typename T>
        void setMatrix(GLuint program, const T& value, GLsizei count = 1, GLboolean transpose = GL_FALSE) const;
    };
}

#endif