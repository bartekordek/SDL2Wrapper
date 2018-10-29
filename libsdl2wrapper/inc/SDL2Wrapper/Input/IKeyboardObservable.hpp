#pragma once

#include "SDL2Wrapper/Input/IKeyboardObserver.hpp"
#include "SDL2Wrapper/Input/IKey.hpp"
#include "CUL/STD_functional.hpp"
#include "CUL/MyString.hpp"

NAMESPACE_BEGIN( SDL2W )

class SDL2WAPI IKeyboardObservable
{
public:
    IKeyboardObservable() = default;
    virtual ~IKeyboardObservable() = default;

    virtual void addKeyboardEventCallback( const std::function<void( const IKey& key )>& callback ) = 0;

    virtual void registerKeyboardEventListener( IKeyboardObserver* observer ) = 0;
    virtual void unregisterKeyboardEventListener( IKeyboardObserver* observer ) = 0;

    virtual const bool isKeyUp( CUL::CnstMyStr& keyName )const = 0;

protected:
private:
};

NAMESPACE_END( SDL2W )