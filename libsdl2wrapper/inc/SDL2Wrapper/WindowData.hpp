#pragma once

#include "SDL2Wrapper/WinSize.hpp"

#include "CUL/Graphics/Pos2D.hpp"
#include "CUL/Math/Vector3D.hpp"
#include "CUL/Graphics/Size2D.hpp"

NAMESPACE_BEGIN( SDL2W )

using Vector3Di = CUL::MATH::Vector3Di;

struct SDL2WAPI WindowData
{
public:
    CUL::Graphics::Pos2Di pos = CUL::Graphics::Pos2Di( 0, 0 );
    WinSize currentRes = { 640, 480 };
    WinSize nativeRes;
    WinSize windowRes;
    CUL::String name = "";
    CUL::String rendererName = "opengl";

    WindowData() = default;

    WindowData( const WindowData& arg ):
        pos( arg.pos ),
        currentRes( arg.currentRes ),
        name( arg.name ),
        rendererName( arg.rendererName )
    {
    }

    WindowData& operator=( const WindowData& rhv )
    {
        if( this != &rhv )
        {
            pos = rhv.pos;
            currentRes = rhv.currentRes;
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