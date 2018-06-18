#pragma once
#include "SDL2Wrapper/SDL2Wrapper.hpp"
namespace SDL2W
{
    class SDL2WAPI IWindowEventObserver
    {
    public:
        enum class WindowEventType: short
        {
            CLOSE = 1,
            RESIZE
        };

        IWindowEventObserver() = default;
        virtual ~IWindowEventObserver() = default;

        virtual void onWindowEvent( const WindowEventType e ) = 0;

    protected:
    private:
    };
}