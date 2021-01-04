#ifndef FILE_H
#define FILE_H

#include <string>

namespace Utility
{
    class File
    {
    public:
        static bool exists(const std::string& path);
        static std::string readText(const std::string& path);
    };
}

#endif