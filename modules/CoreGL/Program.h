#ifndef PROGRAM_H
#define PROGRAM_H

#include "glad/glad.h"

#include <fstream>
#include <sstream>  
#include <string>

namespace CoreGL
{
    class Program final
    {
    private:
        GLuint m_program_id;
    public:
        Program();
        void attachShader(GLenum shader_type, const std::string& shader_file) const;
        void linkProgram() const;
        void useProgram() const;
    };
}

#endif