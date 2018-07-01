#pragma once

#include "SDL2Wrapper/IObject.hpp"

namespace SDL2W
{
    class SDL2WAPI IObjectRegister
    {
    public:
        IObjectRegister() = default;
        IObjectRegister( const IObjectRegister& val ) = delete;
        virtual ~IObjectRegister() = default;

        IObjectRegister& operator=( const IObjectRegister& rhv ) = delete;

        virtual void addObject( IObject* object ) = 0;
        virtual void removeObject( IObject* object ) = 0;

    protected:
    private:
    };
}