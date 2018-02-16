#pragma once

#include "ITexture.hpp"
#include "IObject.hpp"

namespace SDL2W
{
    class SDL2WrapperAPI ISprite:
        public IObject
    {    
    public:
        ISprite();
        ISprite( const ISprite& orig );
        
        virtual ITexture* getTexture() = 0;
        virtual void setTexture( ITexture* texture ) = 0;
        
        virtual ~ISprite();
    private:

    };
}