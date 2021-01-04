#ifndef SHADER_H
#define SHADER_H

#include "glad/glad.h"

#include <string>

namespace CoreGL
{
    class Shader
    {
    private:
        static const std::string s_shader_path;

    private:
        GLenum m_type;
        std::string m_code;
        GLuint m_id;
        std::string m_file;
        std::string m_code;

    public:
        Shader() = delete;
        Shader(GLenum shader_type, const std::string& file);
        ~Shader();

        GLenum getType() const;
        GLuint getId() const;

        void compile();

    public:
        friend class Progam;
    };
}

#endif