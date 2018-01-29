#pragma once
#include "SDL2Wrapper/IKeyboardObserver.hpp"
#include "SDL2Wrapper/IKey.hpp"
#include <functional>
namespace SDL2W
{
    class SDL2WrapperAPI IKeyboardObservable
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