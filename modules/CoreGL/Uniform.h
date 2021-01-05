#ifndef UNIFORM_H
#define UNIFORM_H

#include "glad/glad.h"

#include <string>
namespace CoreGL
{
    class Uniform
    {
    private:
        GLint m_location;
        GLuint m_program_id;
        std::string m_uniform_name;

    public:
        Uniform() = default;
        Uniform(GLuint program_id, const std::string& uniform_name);

        GLint getLocation() const;

    public:
        template<typename T>
        void setVector(GLuint program, const T& value, GLsizei count = 1) const;

        template<typename T>
        void setMatrix(GLuint program, const T& value, GLsizei count = 1, GLboolean transpose = GL_FALSE) const;
    };
}

#endif