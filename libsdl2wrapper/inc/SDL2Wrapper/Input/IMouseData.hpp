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
    IMouseData() = default;
    virtual ~IMouseData() = default;

    virtual unsigned int getMouseButtonCount() const = 0;
    virtual bool isButtonDown( const MouseButtonIndex buttonIndex ) const = 0;
    virtual int getX() const = 0;
    virtual int getY() const = 0;
    virtual int getWheelX() const = 0;
    virtual int getWheelY() const = 0;
    virtual WheelDirection getWheelDirection() const = 0;

protected:
private:
};

NAMESPACE_END( SDL2W )