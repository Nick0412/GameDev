#include "Program.h"

namespace CoreGL
{
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
            throw;
        }

        return file_text;
    }
}