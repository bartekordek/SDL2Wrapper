#pragma once

#include "CUL/UselessMacros.hpp"
#include "SDL2Wrapper/SDL2Wrapper.hpp"

NAMESPACE_BEGIN( SDL2W )

class SDL2WAPI IMouseData
{
public:
    IMouseData( void ) = default;
    virtual ~IMouseData( void ) = default;

    virtual cunt getMouseButtonCount()const = 0;
    virtual const bool isButtonDown( cunt buttonIndex )const = 0;
    virtual cint getX()const = 0;
    virtual cint getY()const = 0;

protected:
private:
};

NAMESPACE_END( SDL2W )