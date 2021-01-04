#include "File.h"

#include <fstream>
#include <sstream>

namespace Utility
{
    bool File::exists(const std::string& path)
    {
        std::ifstream file(path);
        return file.good();
    }

    std::string File::readText(const std::string& path)
    {
        std::ifstream file_stream;
        file_stream.exceptions(std::ifstream::failbit);
        std::string text;

        try
        {
            file_stream.open(path);
            std::stringstream string_stream;
            string_stream << file_stream.rdbuf();
            text = string_stream.str();
        }
        catch (const std::exception& ex) 
        {   
            std::string error(ex.what());
            std::string location = std::string(" ") + path;
            throw std::runtime_error(error + location);
        }

        return text;
    }
}