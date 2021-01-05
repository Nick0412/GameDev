#include "Uniform.h"
#include <iostream>

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

namespace CoreGL
{
    Uniform::Uniform(GLuint program_id, const std::string& uniform_name)
    : m_program_id{program_id}, m_uniform_name{uniform_name}
    {
        m_location = glGetUniformLocation(m_program_id, m_uniform_name.c_str());
    }

    GLint Uniform::getLocation() const
    {
        return m_location;
    }

    // 2D Vectors
    template<>
    void Uniform::setVector(const glm::vec2& value, GLsizei count) const
    {
        glProgramUniform2fv(m_program_id, m_location, count, glm::value_ptr(value));
    }
    
    template<>
    void Uniform::setVector(const glm::ivec2& value, GLsizei count) const
    {
        glProgramUniform2iv(m_program_id, m_location, count, glm::value_ptr(value));
    }

    template<>
    void Uniform::setVector(const glm::uvec2& value, GLsizei count) const
    {
        glProgramUniform2uiv(m_program_id, m_location, count, glm::value_ptr(value));
    }

    // 3D Vectors
    template<>
    void Uniform::setVector(const glm::vec3& value, GLsizei count) const
    {
        glProgramUniform3fv(m_program_id, m_location, count, glm::value_ptr(value));
    }
    
    template<>
    void Uniform::setVector(const glm::ivec3& value, GLsizei count) const
    {
        glProgramUniform3iv(m_program_id, m_location, count, glm::value_ptr(value));
    }

    template<>
    void Uniform::setVector(const glm::uvec3& value, GLsizei count) const
    {
        glProgramUniform3uiv(m_program_id, m_location, count, glm::value_ptr(value));
    }

    // 4D Vectors
    template<>
    void Uniform::setVector(const glm::vec4& value, GLsizei count) const
    {
        glProgramUniform4fv(m_program_id, m_location, count, glm::value_ptr(value));
    }
    
    template<>
    void Uniform::setVector(const glm::ivec4& value, GLsizei count) const
    {
        glProgramUniform4iv(m_program_id, m_location, count, glm::value_ptr(value));
    }

    template<>
    void Uniform::setVector(const glm::uvec4& value, GLsizei count) const
    {
        glProgramUniform4uiv(m_program_id, m_location, count, glm::value_ptr(value));
    }

    // Square matrices
    template<>
    void Uniform::setMatrix(const glm::mat2& value, GLsizei count, GLboolean transpose) const
    {
        glProgramUniformMatrix2fv(m_program_id, m_location, count, transpose, glm::value_ptr(value));
    }

    template<>
    void Uniform::setMatrix(const glm::mat3& value, GLsizei count, GLboolean transpose) const
    {
        glProgramUniformMatrix3fv(m_program_id, m_location, count, transpose, glm::value_ptr(value));
    }

    template<>
    void Uniform::setMatrix(const glm::mat4& value, GLsizei count, GLboolean transpose) const
    {
        glProgramUniformMatrix4fv(m_program_id, m_location, count, transpose, glm::value_ptr(value));
    }

    // Non square matrices
    template<>
    void Uniform::setMatrix(const glm::mat2x3& value, GLsizei count, GLboolean transpose) const
    {
        glProgramUniformMatrix2x3fv(m_program_id, m_location, count, transpose, glm::value_ptr(value));
    }

    template<>
    void Uniform::setMatrix(const glm::mat2x4& value, GLsizei count, GLboolean transpose) const
    {
        glProgramUniformMatrix2x4fv(m_program_id, m_location, count, transpose, glm::value_ptr(value));
    }

    template<>
    void Uniform::setMatrix(const glm::mat3x2& value, GLsizei count, GLboolean transpose) const
    {
        glProgramUniformMatrix3x2fv(m_program_id, m_location, count, transpose, glm::value_ptr(value));
    }

    template<>
    void Uniform::setMatrix(const glm::mat3x4& value, GLsizei count, GLboolean transpose) const
    {
        glProgramUniformMatrix3x4fv(m_program_id, m_location, count, transpose, glm::value_ptr(value));
    }

    template<>
    void Uniform::setMatrix(const glm::mat4x2& value, GLsizei count, GLboolean transpose) const
    {
        glProgramUniformMatrix4x2fv(m_program_id, m_location, count, transpose, glm::value_ptr(value));
    }

    template<>
    void Uniform::setMatrix(const glm::mat4x3& value, GLsizei count, GLboolean transpose) const
    {
        glProgramUniformMatrix4x3fv(m_program_id, m_location, count, transpose, glm::value_ptr(value));
    }
    
}