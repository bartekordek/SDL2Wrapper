#include "KeySDL.hpp"

using namespace SDL2W;

KeySDL::KeySDL()
{
}

void KeySDL::setKeyName( CsStr& name )
{
    m_keyName = name;
}

CsStr& KeySDL::getKeyName() const
{
    return m_keyName;
}

void KeySDL::setKeyIsDown( Cbool keyIsDow )
{
    m_keyIsDown = keyIsDow;
}

bool KeySDL::getKeyIsDown() const
{
    return m_keyIsDown;
}

KeySDL::~KeySDL()
{
}