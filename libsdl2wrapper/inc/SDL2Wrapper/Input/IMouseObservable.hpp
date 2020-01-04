#pragma once

#include "SDL2Wrapper/Input/IMouseObserver.hpp"
#include "SDL2Wrapper/Input/IMouseData.hpp"
#include "CUL/STL_IMPORTS/STD_functional.hpp"

NAMESPACE_BEGIN( SDL2W )

class SDL2WAPI IMouseObservable
{
public:
    using MouseCallback = std::function<void( const IMouseData& md )>;

    IMouseObservable() = default;
    virtual ~IMouseObservable() = default;

    virtual void addMouseEventCallback( const MouseCallback& callback ) = 0;

    virtual void registerMouseEventListener( IMouseObserver* observer ) = 0;
    virtual void unregisterMouseEventListener( IMouseObserver* observer ) = 0;

    virtual IMouseData& getMouseData() = 0;

protected:
private:
};

NAMESPACE_END( SDL2W )