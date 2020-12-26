#ifndef SHADER_FILE_H
#define SHADER_FILE_H

#include <fstream>
#include <sstream>
#include <string>

namespace File
{
    class ShaderFile
    {
    private:
    public:
        std::string readFile(const std::string& file) const;
    };
}

#endif