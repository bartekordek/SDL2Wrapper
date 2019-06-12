#pragma once

#include "SDL2Wrapper/Input/IKey.hpp"
#include "CUL/UselessMacros.hpp"

NAMESPACE_BEGIN( SDL2W )

class SDL2WAPI IKeyboardObserver
{
public:
    IKeyboardObserver() = default;
    virtual ~IKeyboardObserver() = default;

    virtual void onKeyBoardEvent( const IKey& key ) = 0;

protected:
private:
};

NAMESPACE_END( SDL2W )