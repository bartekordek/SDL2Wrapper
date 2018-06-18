#pragma once

#include "SDL2Wrapper/IKey.hpp"
#include "SDL2Wrapper/SDL2Wrapper.hpp"

namespace SDL2W
{
    class SDL2WAPI IKeyboardObserver
    {
    public:
        IKeyboardObserver() = default;
        virtual ~IKeyboardObserver() = default;

        virtual void onKeyBoardEvent( const IKey& key ) = 0;

    protected:
    private:
    };
}