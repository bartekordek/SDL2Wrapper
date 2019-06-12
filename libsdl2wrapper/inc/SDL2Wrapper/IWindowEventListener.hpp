#pragma once

#include "SDL2Wrapper/Import.hpp"

namespace SDL2W
{
    class SDL2WAPI IWindowEventObserver
    {
    public:
        enum class WindowEventType: short
        {
            CLOSE = 1,
            MINIMIZED,
            RESTORED,
            MOVED,
            RESIZE,
            MOUSE_ENTERED,
            MOUSE_LEAVED,
            FOCUS_GAINED,
            FOCUS_LEAVED
        };

        IWindowEventObserver() = default;
        virtual ~IWindowEventObserver() = default;

        virtual void onWindowEvent( const WindowEventType e ) = 0;

    protected:
    private:
    };
}