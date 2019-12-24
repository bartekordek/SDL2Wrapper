#pragma once

#include "SDL2Wrapper/Input/IKeyboardObserver.hpp"
#include "SDL2Wrapper/Input/IKey.hpp"
#include "CUL/STL_IMPORTS/STD_functional.hpp"
#include "CUL/String.hpp"

NAMESPACE_BEGIN( SDL2W )

class SDL2WAPI IKeyboardObservable
{
public:
    IKeyboardObservable() = default;
    virtual ~IKeyboardObservable() = default;

    virtual void registerKeyboardEventCallback( const std::function<void( const IKey& key )>& callback ) = 0;

    virtual void registerKeyboardEventListener( IKeyboardObserver* observer ) = 0;
    virtual void unregisterKeyboardEventListener( IKeyboardObserver* observer ) = 0;

    virtual Cbool isKeyUp( CsStr& keyName ) const = 0;

protected:
private:
};

NAMESPACE_END( SDL2W )