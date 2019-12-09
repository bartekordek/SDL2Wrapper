#pragma once

#include "CUL/UselessMacros.hpp"
#include "SDL2Wrapper/Import.hpp"

NAMESPACE_BEGIN( SDL2W )

class SDL2WAPI IEventLoop
{
public:
    IEventLoop() = default;
    virtual ~IEventLoop() = default;

    /* Should be run in main process. */
    virtual void runEventLoop() = 0;
    virtual void stopEventLoop() = 0;

    virtual void pollEvents() = 0;

protected:
private:
};

NAMESPACE_END( SDL2W )