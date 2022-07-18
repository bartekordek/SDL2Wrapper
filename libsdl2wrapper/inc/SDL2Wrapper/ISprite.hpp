#pragma once

#include "SDL2Wrapper/Import.hpp"

#include "CUL/Graphics/IObject.hpp"

NAMESPACE_BEGIN( CUL::Graphics )
class ITexture;
NAMESPACE_END( CUL::Graphics )

NAMESPACE_BEGIN( SDL2W )

using ITexture = CUL::Graphics::ITexture;
using IObject = CUL::Graphics::IObject;

class SDL2WAPI ISprite:
    public IObject
{
public:
    ISprite();

    virtual ITexture* getTexture() = 0;
    virtual void setTexture( ITexture* texture ) = 0;

    virtual ~ISprite();
private:
};

NAMESPACE_END( SDL2W )