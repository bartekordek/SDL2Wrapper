#pragma once

#include "SDL2Wrapper/SDL2Wrapper.hpp"
#include "CUL/MyString.hpp"

namespace SDL2W
{
    class SDL2WAPI IKey
    {
    public:
        IKey();
        virtual ~IKey();
        virtual void setKeyName( const std::string& keyName ) = 0;
        virtual CUL::CnstMyStr& getKeyName()const = 0;
        virtual const bool getKeyIsDown()const = 0;
        virtual void setKeyIsDown( const bool isDown ) = 0;
    protected:
    private:


    };
}