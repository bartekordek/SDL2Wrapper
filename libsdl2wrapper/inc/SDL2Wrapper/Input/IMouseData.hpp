#pragma once

#include "SDL2Wrapper/Import.hpp"

NAMESPACE_BEGIN( SDL2W )

using MouseButtonIndex = unsigned short;

enum class WheelDirection: short
{
    NONE = 0,
    UP,
    DOWN
};

class SDL2WAPI IMouseData
{
public:
    IMouseData( void ) = default;
    virtual ~IMouseData( void ) = default;

    virtual Cunt getMouseButtonCount() const = 0;
    virtual const bool isButtonDown( const MouseButtonIndex buttonIndex ) const = 0;
    virtual Cint getX() const = 0;
    virtual Cint getY() const = 0;
    virtual Cint getWheelX() const = 0;
    virtual Cint getWheelY() const = 0;
    virtual const WheelDirection getWheelDirection() const = 0;

protected:
private:
};

NAMESPACE_END( SDL2W )