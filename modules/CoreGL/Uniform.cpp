#include "Uniform.h"

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

namespace CoreGL
{
    Uniform::Uniform(const GLint location)
    : m_location{location}
    {

    }

    GLint Uniform::getLocation() const
    {
        return m_location;
    }

    // 2D Vectors
    template<>
    void Uniform::setVector(GLuint program, const glm::vec2& value, GLsizei count) const
    {
        glProgramUniform2fv(program, m_location, count, glm::value_ptr(value));
    }
    
    template<>
    void Uniform::setVector(GLuint program, const glm::ivec2& value, GLsizei count) const
    {
        glProgramUniform2iv(program, m_location, count, glm::value_ptr(value));
    }

    template<>
    void Uniform::setVector(GLuint program, const glm::uvec2& value, GLsizei count) const
    {
        glProgramUniform2uiv(program, m_location, count, glm::value_ptr(value));
    }

    // 3D Vectors
    template<>
    void Uniform::setVector(GLuint program, const glm::vec3& value, GLsizei count) const
    {
        glProgramUniform3fv(program, m_location, count, glm::value_ptr(value));
    }
    
    template<>
    void Uniform::setVector(GLuint program, const glm::ivec3& value, GLsizei count) const
    {
        glProgramUniform3iv(program, m_location, count, glm::value_ptr(value));
    }

    template<>
    void Uniform::setVector(GLuint program, const glm::uvec3& value, GLsizei count) const
    {
        glProgramUniform3uiv(program, m_location, count, glm::value_ptr(value));
    }

    // 4D Vectors
    template<>
    void Uniform::setVector(GLuint program, const glm::vec4& value, GLsizei count) const
    {
        glProgramUniform4fv(program, m_location, count, glm::value_ptr(value));
    }
    
    template<>
    void Uniform::setVector(GLuint program, const glm::ivec4& value, GLsizei count) const
    {
        glProgramUniform4iv(program, m_location, count, glm::value_ptr(value));
    }

    template<>
    void Uniform::setVector(GLuint program, const glm::uvec4& value, GLsizei count) const
    {
        glProgramUniform4uiv(program, m_location, count, glm::value_ptr(value));
    }

    // Square matrices
    template<>
    void Uniform::setMatrix(GLuint program, const glm::mat2& value, GLsizei count, GLboolean transpose) const
    {
        glProgramUniformMatrix2fv(program, m_location, count, transpose, glm::value_ptr(value));
    }

    template<>
    void Uniform::setMatrix(GLuint program, const glm::mat3& value, GLsizei count, GLboolean transpose) const
    {
        glProgramUniformMatrix3fv(program, m_location, count, transpose, glm::value_ptr(value));
    }

    template<>
    void Uniform::setMatrix(GLuint program, const glm::mat4& value, GLsizei count, GLboolean transpose) const
    {
        glProgramUniformMatrix4fv(program, m_location, count, transpose, glm::value_ptr(value));
    }

    // Non square matrices
    template<>
    void Uniform::setMatrix(GLuint program, const glm::mat2x3& value, GLsizei count, GLboolean transpose) const
    {
        glProgramUniformMatrix2x3fv(program, m_location, count, transpose, glm::value_ptr(value));
    }

    template<>
    void Uniform::setMatrix(GLuint program, const glm::mat2x4& value, GLsizei count, GLboolean transpose) const
    {
        glProgramUniformMatrix2x4fv(program, m_location, count, transpose, glm::value_ptr(value));
    }

    template<>
    void Uniform::setMatrix(GLuint program, const glm::mat3x2& value, GLsizei count, GLboolean transpose) const
    {
        glProgramUniformMatrix3x2fv(program, m_location, count, transpose, glm::value_ptr(value));
    }

    template<>
    void Uniform::setMatrix(GLuint program, const glm::mat3x4& value, GLsizei count, GLboolean transpose) const
    {
        glProgramUniformMatrix3x4fv(program, m_location, count, transpose, glm::value_ptr(value));
    }

    template<>
    void Uniform::setMatrix(GLuint program, const glm::mat4x2& value, GLsizei count, GLboolean transpose) const
    {
        glProgramUniformMatrix4x2fv(program, m_location, count, transpose, glm::value_ptr(value));
    }

    template<>
    void Uniform::setMatrix(GLuint program, const glm::mat4x3& value, GLsizei count, GLboolean transpose) const
    {
        glProgramUniformMatrix4x3fv(program, m_location, count, transpose, glm::value_ptr(value));
    }
    
}