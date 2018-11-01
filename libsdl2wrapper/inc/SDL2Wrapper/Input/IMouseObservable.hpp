#pragma once

#include "SDL2Wrapper/Input/IMouseObserver.hpp"
#include "SDL2Wrapper/Input/IMouseData.hpp"
#include "CUL/STD_functional.hpp"

NAMESPACE_BEGIN( SDL2W )

class SDL2WAPI IMouseObservable
{
public:
    IMouseObservable( void ) = default;
    virtual ~IMouseObservable( void ) = default;

    virtual void addMouseEventCallback( const std::function<void( const IMouseData& md )>& callback ) = 0;

    virtual void registerMouseEventListener( IMouseObserver* observer ) = 0;
    virtual void unregisterMouseEventListener( IMouseObserver* observer ) = 0;

    virtual IMouseData& getMouseData( void ) = 0;

protected:
private:
};

NAMESPACE_END( SDL2W )