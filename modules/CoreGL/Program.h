#ifndef PROGRAM_H
#define PROGRAM_H

#include "glad/glad.h"

#include "Shader.h"
#include "Uniform.h"

#include <fstream>
#include <sstream>  
#include <string>
#include <unordered_map>

namespace CoreGL
{
    class Program final
    {
    private:
        GLuint m_program_id;
        std::unordered_map<std::string, Uniform> m_uniforms;

    private:
        void mapUniforms(const Shader& shader);

    public:
        Program();
        ~Program();

        // void attachShader(GLenum shader_type, const std::string& shader_file) const;
        void attachShader(const Shader& shader);
        void linkProgram() const;
        void useProgram() const;

        GLuint getId() const;
        Uniform& operator[](const std::string& uniform_name);
        GLuint getUniformLocation(const std::string& uniform_name) const;
    };
}

#endif