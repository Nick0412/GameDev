#include "Program.h"
#include <iostream>
namespace CoreGL
{

#ifdef SHADER_DIR
    static const std::string g_shader_path = SHADER_DIR;
#else
    static const std::string g_shader_path = "UNDEFINED";
#endif

    static std::string readShaderFile(const std::string& file)
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
            throw std::runtime_error(e);
        }

        return file_text;
    }

    static GLuint createShader(GLenum shader_type, const std::string& shader_file)
    {
        GLuint shader_id = glCreateShader(shader_type);
        std::string full_shader_file = g_shader_path + shader_file;
        std::string shader_source = readShaderFile(full_shader_file);
        auto shader_source_cast = static_cast<const GLchar*>(shader_source.c_str());
        glShaderSource(shader_id, 1, &shader_source_cast, nullptr);

        return shader_id;
    }

    static void checkShaderCompileStatus(GLuint shader_id)
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

    static void checkProgramLinkStatus(GLuint program_id)
    {
        glLinkProgram(program_id);
        GLint result;
        glGetProgramiv(program_id, GL_LINK_STATUS, &result);
        if (result == GL_FALSE)
        {
            char info_log[1024];
            glGetProgramInfoLog(program_id, 1024, nullptr, info_log);
            auto ex = std::string("Program Link Error: ") + info_log;
            throw std::runtime_error(ex);
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

    void Program::linkProgram() const
    {   
        glLinkProgram(m_program_id);
        checkProgramLinkStatus(m_program_id);
        glValidateProgram(m_program_id);
    }

    void Program::useProgram() const
    {
        glUseProgram(m_program_id);
    }

}