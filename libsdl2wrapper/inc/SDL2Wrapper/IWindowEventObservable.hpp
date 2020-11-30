#pragma once

#include "SDL2Wrapper/Import.hpp"

#include "CUL/STL_IMPORTS/STD_functional.hpp"

NAMESPACE_BEGIN( WindowEvent )

enum class Type: short;

NAMESPACE_END( WindowEvent )

NAMESPACE_BEGIN( SDL2W )

using WindowCallback = std::function<void( const WindowEvent::Type wEt )>;

class SDL2WAPI IWindowEventObservable
{
public:
    IWindowEventObservable() = default;

    virtual void registerWindowEventCallback( const WindowCallback& callback ) = 0;

    virtual ~IWindowEventObservable() = default;

protected:
private:
private: // Deleted:
    IWindowEventObservable( const IWindowEventObservable& arg ) = delete;
    IWindowEventObservable( IWindowEventObservable&& arg ) = delete;
    IWindowEventObservable& operator=( const IWindowEventObservable& rhv ) = delete;
    IWindowEventObservable& operator=( IWindowEventObservable&& rhv ) = delete;
};

NAMESPACE_END( SDL2W )