#pragma once

#include "ITexture.hpp"
#include "IObject.hpp"

namespace SDL2W
{
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
}