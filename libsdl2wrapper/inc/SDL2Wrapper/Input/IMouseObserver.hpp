#pragma once

#include "SDL2Wrapper/Input/IMouseData.hpp"
#include "CUL/UselessMacros.hpp"
#include "SDL2Wrapper/SDL2Wrapper.hpp"

NAMESPACE_BEGIN( SDL2W )

class SDL2WAPI IMouseObserver
{
public:
    IMouseObserver( void ) = default;
    virtual ~IMouseObserver( void ) = default;

    virtual void onMouseEvent( const IMouseData& md ) = 0;

protected:
private:
};

NAMESPACE_END( SDL2W )