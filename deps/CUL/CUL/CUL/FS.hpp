#pragma once
#include <CUL/CUL.hpp>
#include <string>
namespace CUL
{
    namespace FS
    {
        class CULLib_API FSApi
        {
        public:
            FSApi();
            virtual ~FSApi();
            static std::string getCurrentDir();
        };
    }
}