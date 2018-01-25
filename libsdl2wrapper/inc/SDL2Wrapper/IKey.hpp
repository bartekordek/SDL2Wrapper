#pragma once

#include "SDL2Wrapper/SDL2Wrapper.hpp"
#include <string>

namespace SDL2W
{
    class SDL2WrapperAPI IKey
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