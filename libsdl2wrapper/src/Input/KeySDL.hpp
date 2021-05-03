#pragma once

#include "SDL2Wrapper/Input/IKey.hpp"
#include "CUL/STL_IMPORTS/STD_string.hpp"

NAMESPACE_BEGIN( SDL2W )

#ifdef _MSC_VER
#pragma warning( push )
#pragma warning( disable: 4820 )
#endif

class KeySDL final: public IKey
{
public:
    KeySDL();
    ~KeySDL();
protected:
private:
    void setKeyName( const String& keyName ) override;
    const String& getKeyName() const override;
    void setKeyIsDown( bool keyIsDown ) override;
    bool getKeyIsDown() const override;

    CUL::String m_keyName;
    bool m_keyIsDown = false;

private: // Deleted
    KeySDL( const KeySDL& key ) = delete;
    KeySDL( KeySDL&& key ) = delete;
    KeySDL& operator=( const KeySDL& key ) = delete;
    KeySDL& operator=( KeySDL&& key ) = delete;
};

#ifdef _MSC_VER
#pragma warning( pop )
#endif

NAMESPACE_END( SDL2W )