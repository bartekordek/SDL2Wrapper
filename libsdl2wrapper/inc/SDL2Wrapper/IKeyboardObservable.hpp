#pragma once
#include "SDL2Wrapper/IKeyboardObserver.hpp"
#include "SDL2Wrapper/IKey.hpp"
#include "CUL/STD_functional.hpp"
namespace SDL2W
{
    class SDL2WAPI IKeyboardObservable
    {
    public:
        IKeyboardObservable() = default;
        virtual ~IKeyboardObservable() = default;

        virtual void addKeyboardEventCallback( const std::function<void( const IKey& key )>& callback ) = 0;

        virtual void registerKeyboardEventListener( IKeyboardObserver* observer ) = 0;
        virtual void unregisterKeyboardEventListener( IKeyboardObserver* observer ) = 0;

        virtual const bool isKeyUp( const std::string& keyName )const = 0;

    protected:
    private:
    };
}