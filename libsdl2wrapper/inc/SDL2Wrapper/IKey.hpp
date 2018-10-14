#pragma once

#include "SDL2Wrapper/SDL2Wrapper.hpp"
#include "CUL/STD_string.hpp"

namespace SDL2W
{
    class SDL2WAPI IKey
    {
    public:
        IKey();
        virtual ~IKey();
        virtual void setKeyName( const std::string& keyName ) = 0;
        virtual const std::string& getKeyName()const = 0;
        virtual const bool getKeyIsDown()const = 0;
        virtual void setKeyIsDown( const bool isDown ) = 0;
    protected:
    private:
    };
}