#pragma once

#include "SDL2Wrapper/Import.hpp"
#include "CUL/String.hpp"

NAMESPACE_BEGIN( SDL2W )

using CsStr = CUL::CsStr;

class SDL2WAPI IKey
{
public:
    IKey();
    virtual ~IKey();
    virtual void setKeyName( CsStr& keyName ) = 0;
    virtual CsStr& getKeyName() const = 0;
    virtual bool getKeyIsDown() const = 0;
    virtual void setKeyIsDown( Cbool isDown ) = 0;
protected:
private:
};

NAMESPACE_END( SDL2W )