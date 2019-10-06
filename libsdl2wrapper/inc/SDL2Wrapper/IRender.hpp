#pragma once

#include "SDL2Wrapper/Import.hpp"

#include "CUL/Video/IFPSObservable.hpp"
#include "CUL/Graphics/Color.hpp"

NAMESPACE_BEGIN( SDL2W )

using ColorS = CUL::Graphics::ColorS;
using ColorE = CUL::Graphics::ColorE;
class SDL2WAPI IRender:
    public CUL::Video::IFPSObservable
{
public:
    IRender();
    IRender( const IRender& rhv ) = delete;
    virtual ~IRender();
    IRender& operator=( const IRender& rhv ) = delete;

    virtual void setBackgroundColor( const ColorS& color ) = 0;
    virtual void setBackgroundColor( const ColorE color ) = 0;
    virtual const ColorS getBackgroundColor()const = 0;
    virtual void clearBuffers() = 0;
    virtual void renderAll() = 0;
    virtual void updateScreenBuffers() = 0;

protected:
private:
};

NAMESPACE_END( SDL2W )