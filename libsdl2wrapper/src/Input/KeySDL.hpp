#pragma once

#include "SDL2Wrapper/Input/IKey.hpp"
#include "CUL/STL_IMPORTS/STD_string.hpp"

NAMESPACE_BEGIN( SDL2W )


#ifdef _MSC_VER
#pragma warning( push )
#pragma warning( disable: 4820 )
#endif

class KeySDL: public IKey
{
public:
    KeySDL();
    virtual ~KeySDL();

protected:
private:
    void setKeyName( CsStr& keyName ) override;
    CsStr& getKeyName()const override;
    void setKeyIsDown( Cbool keyIsDown ) override;
    Cbool getKeyIsDown()const override;

    CUL::String m_keyName;
    bool m_keyIsDown = false;

private: // Deleted
    KeySDL( const KeySDL& key ) = delete;
    KeySDL& operator=( const KeySDL& key ) = delete;

};

#ifdef _MSC_VER
#pragma warning( pop )
#endif

NAMESPACE_END( SDL2W )