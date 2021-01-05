#include "Shader.h"

#include "File.h"

#include <sstream>
#include <vector>
namespace CoreGL
{
#ifdef SHADER_DIR
    const std::string Shader::s_shader_path = SHADER_DIR;
#endif

    Shader::Shader(GLenum shader_type, const std::string& file)
    :   m_type{shader_type}, 
        m_file{file},
        m_id{glCreateShader(shader_type)}
    {
        std::string full_file = s_shader_path + file;
        try 
        {
            m_code = Utility::File::readText(full_file);
        }
        catch (const std::exception& ex)
        {
            throw;
        }
    }

    Shader::~Shader()
    {
        glDeleteShader(m_id);
    }

    GLenum Shader::getType() const
    {
        return m_type;
    }

    GLuint Shader::getId() const
    {
        return m_id;
    }

    void Shader::compile() const
    {
        auto code = m_code.c_str();
        glShaderSource(m_id, 1, &code, nullptr);
        glCompileShader(m_id);

        GLint result;
        GLint info_length;
        glGetShaderiv(m_id, GL_COMPILE_STATUS, &result);
        glGetShaderiv(m_id, GL_INFO_LOG_LENGTH, &info_length);

        std::vector<GLchar> error_message(info_length, '\0');
        glGetShaderInfoLog(m_id, info_length, nullptr, error_message.data());

        if (result != GL_TRUE)
        {
            std::stringstream stream;
            stream  << "Shader compilation failed:\n"
                    << "File: " << m_file << "\n"
                    << "Message: " << std::string(error_message.begin(), error_message.end()) << "\n";
            throw std::runtime_error(stream.str());
        }
    }
}