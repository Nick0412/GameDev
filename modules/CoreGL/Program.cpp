#include "Program.h"
#include <iostream>
namespace CoreGL
{

#ifdef SHADER_DIR
    const std::string g_shader_path = SHADER_DIR;
#else
    const std::string g_shader_path = "UNDEFINED";
#endif

    std::string readShaderFile(const std::string& file)
    {
        std::string file_text;
        std::ifstream file_stream;
        file_stream.exceptions(std::ifstream::failbit);

        try
        {
            file_stream.open(file);
            std::stringstream string_stream;
            string_stream << file_stream.rdbuf();
            file_text = string_stream.str();
        }
        catch (const std::exception& ex)
        {
            auto e = std::string(ex.what()) + " " + file;
            throw std::runtime_error(e.c_str());
        }

        return file_text;
    }

    GLuint createShader(GLenum shader_type, const std::string& shader_file)
    {
        GLuint shader_id = glCreateShader(shader_type);
        std::string full_shader_file = g_shader_path + shader_file;
        std::string shader_source = readShaderFile(full_shader_file);
        auto shader_source_cast = static_cast<const GLchar*>(shader_source.c_str());
        glShaderSource(shader_id, 1, &shader_source_cast, nullptr);

        return shader_id;
    }

    void checkShaderCompileStatus(GLuint shader_id)
    {
        GLint result;
        glGetShaderiv(shader_id, GL_COMPILE_STATUS, &result);
        if (result == GL_FALSE)
        {
            char info_log[1024];
            glGetShaderInfoLog(shader_id, 1024, nullptr, info_log);
            auto ex = std::string("Shader Compile Error: ") + info_log;
            throw std::runtime_error(ex.c_str());
        }
    }

    Program::Program()
    : m_program_id(glCreateProgram())
    {

    }

    void Program::attachShader(GLenum shader_type, const std::string& shader_file) const
    {
        GLuint shader_id = createShader(shader_type, shader_file);
        glCompileShader(shader_id);
        checkShaderCompileStatus(shader_id);
        glAttachShader(m_program_id, shader_id);
    }

    void Program::linkProgram()
    {   
        glLinkProgram(m_program_id);
        std::cout << " TESTING 1: " + m_program_id << "\n";
        std::cout << "ERROR " << glGetError() << "\n";
        checkProgramLinkStatus();
        std::cout << " Testing 2: " + m_program_id << "\n";
        glValidateProgram(m_program_id);
    }

    void Program::useProgram() const
    {
        glUseProgram(m_program_id);
    }

    void Program::checkProgramLinkStatus()
    {
        glLinkProgram(m_program_id);
        GLint result;
        glGetProgramiv(m_program_id, GL_LINK_STATUS, &result);
        std::cout << "ERROR 1" << glGetError() << "\n";
        if (result == GL_FALSE)
        {
            std::cout << "ERROR 2" << glGetError() << "\n";
            char info_log[1024];
            glGetProgramInfoLog(m_program_id, 1024, nullptr, info_log);
            auto ex = std::string("Program Link Error: ") + info_log;
            throw std::runtime_error(ex.c_str());
        }
    }
}