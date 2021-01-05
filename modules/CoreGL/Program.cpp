#include "Program.h"

namespace CoreGL
{
    Program::Program()
    : m_program_id{glCreateProgram()}
    {

    }

    Program::~Program()
    {
        glDeleteProgram(m_program_id);
    }

    void Program::attachShader(const Shader& shader)
    {
        glAttachShader(m_program_id, shader.getId());
        m_attached_shaders.push_back(shader);
    }

    GLuint Program::getId() const
    {
        return m_program_id;
    }

    void Program::loadProgram() 
    {
        linkProgram();
        for (const auto& shader : m_attached_shaders)
        {
            mapUniforms(shader);
        }
    }

    void Program::linkProgram() const
    {   
        glLinkProgram(m_program_id);

        GLint result;
        GLint info_length;
        glGetProgramiv(m_program_id, GL_LINK_STATUS, &result);
        glGetProgramiv(m_program_id, GL_INFO_LOG_LENGTH, &info_length);

        std::vector<GLchar> error_message(info_length, '\0');
        glGetProgramInfoLog(m_program_id, info_length, nullptr, error_message.data());

        if (result != GL_TRUE)
        {
            std::stringstream stream;
            stream  << "Program linking failed:\n"
                    << "Message: " << std::string(error_message.begin(), error_message.end()) << "\n";
            throw std::runtime_error(stream.str());
        }

        glValidateProgram(m_program_id);
    }

    void Program::useProgram() const
    {
        glUseProgram(m_program_id);
    }

    Uniform& Program::operator[](const std::string& uniform_name)
    {
        try
        {
            return m_uniforms.at(uniform_name); 
        }
        catch (const std::out_of_range& ex)
        {
            throw;
        }
    }

    void Program::mapUniforms(const Shader& shader)
    {
        std::stringstream string_stream(shader.m_code);
        std::string uniform_name;
        std::string current_text;

        while (!string_stream.eof() && string_stream.good())
        {
            string_stream >> current_text;
            if (current_text == "uniform")
            {
                string_stream >> current_text;
                string_stream >> uniform_name;

                // Remove semicolon from uniform name
                if (uniform_name.back() == ';')
                {
                    uniform_name.pop_back();
                }

                // Remove brackets for arrays
                auto bracket_pos = uniform_name.find_first_of("[");
                uniform_name = uniform_name.substr(0, bracket_pos);
                

                // m_uniforms[uniform_name] = Uniform(glGetUniformLocation(m_program_id, uniform_name.c_str()), m_program_id);
                m_uniforms[uniform_name] = Uniform(m_program_id, uniform_name);
            }
        }
    }

    GLuint Program::getUniformLocation(const std::string& uniform_name) const
    {
        try
        {
            return m_uniforms.at(uniform_name).getLocation();
        }
        catch (const std::out_of_range& ex)
        {
            throw;
        }
    }

}