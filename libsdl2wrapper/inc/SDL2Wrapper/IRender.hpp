#pragma once

#include "SDL2Wrapper/SDL2Wrapper.hpp"
#include "CUL/Color.hpp"

namespace SDL2W
{
    using ColorS = CUL::ColorS;
    using ColorE = CUL::ColorE;
    class SDL2WAPI IRender
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
}