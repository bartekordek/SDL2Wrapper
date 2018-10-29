#pragma once

#include "CUL/UselessMacros.hpp"
#include "SDL2Wrapper/SDL2Wrapper.hpp"

NAMESPACE_BEGIN( SDL2W )

class SDL2WAPI IMouseObserver
{
public:
    IMouseObserver( void ) = default;
    virtual ~IMouseObserver( void ) = default;

    virtual void onKeyBoardEvent( void ) = 0;

protected:
private:
};

NAMESPACE_END( SDL2W )