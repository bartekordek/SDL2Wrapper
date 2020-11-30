#pragma once

#include "SDL2Wrapper/Import.hpp"
#include "CUL/Math/Vector3D.hpp"
#include "CUL/Graphics/Size2D.hpp"

NAMESPACE_BEGIN( SDL2W )

using Vector3Di = CUL::MATH::Vector3Di;
using WindowSize = CUL::Graphics::Size2Di;
using String = CUL::String;

struct SDL2WAPI WindowData
{
public:
    Vector3Di pos = Vector3Di( 0, 0, 0 );
    WindowSize size = WindowSize( 640, 480 );
    String name = "";
    String rendererName = "opengl";

    WindowData() = default;

    WindowData( const WindowData& arg ):
        pos( arg.pos ),
        size( arg.size ),
        name( arg.name ),
        rendererName( arg.rendererName )
    {
    }

    WindowData& operator=( const WindowData& rhv )
    {
        if( this != &rhv )
        {
            pos = rhv.pos;
            size = rhv.size;
            name = rhv.name;
            rendererName = rhv.rendererName;
        }
        return *this;
    }

    ~WindowData() = default;


protected:
private:

    // Deleted:
    WindowData( WindowData&& arg ) = delete;
    WindowData& operator=( WindowData&& rhv ) = delete;
};

NAMESPACE_END( SDL2W )