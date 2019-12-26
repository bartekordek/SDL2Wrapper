#pragma once

#include "SDL2Wrapper/Import.hpp"

NAMESPACE_BEGIN( SDL2W )

NAMESPACE_BEGIN( WindowEvent )

enum class Type: short
{
    NONE = 0,
    CLOSE,
    MINIMIZED,
    RESTORED,
    MOVED,
    RESIZE,
    MOUSE_ENTERED,
    MOUSE_LEAVED,
    FOCUS_GAINED,
    FOCUS_LEAVED
};

NAMESPACE_END( WindowEvent )

class SDL2WAPI IWindowEventObserver
{
public:
    IWindowEventObserver() = default;
    virtual ~IWindowEventObserver() = default;

    virtual void onWindowEvent( const WindowEvent::Type e ) = 0;

protected:
private:
private: // Deleted:
    IWindowEventObserver( const IWindowEventObserver& arg ) = delete;
    IWindowEventObserver( IWindowEventObserver&& arg ) = delete;
    IWindowEventObserver& operator=( const IWindowEventObserver& rhv ) = delete;
    IWindowEventObserver& operator=( IWindowEventObserver&& rhv ) = delete;
};

NAMESPACE_END( SDL2W )