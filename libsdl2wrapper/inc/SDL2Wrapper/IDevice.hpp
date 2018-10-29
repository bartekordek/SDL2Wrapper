#pragma once

#include "CUL/UselessMacros.hpp"
#include "SDL2Wrapper/SDL2Wrapper.hpp"

NAMESPACE_BEGIN( SDL2W )

class SDL2WAPI IDevice
{
public:
    IDevice( void ) = default;
    virtual ~IDevice( void ) = default;

protected:
private:
};

NAMESPACE_END( SDL2W )