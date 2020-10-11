#pragma once

#include "SDL2Wrapper/Import.hpp"
#include "CUL/String.hpp"

NAMESPACE_BEGIN( SDL2W )

using String = CUL::String;

class SDL2WAPI IKey
{
public:
    IKey();
    virtual ~IKey();
    virtual void setKeyName( const String& keyName ) = 0;
    virtual const String& getKeyName() const = 0;
    virtual bool getKeyIsDown() const = 0;
    virtual void setKeyIsDown( Cbool isDown ) = 0;
protected:
private:
};

NAMESPACE_END( SDL2W )