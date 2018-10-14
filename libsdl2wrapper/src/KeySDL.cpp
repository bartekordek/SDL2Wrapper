#include "KeySDL.hpp"

namespace SDL2W
{
    KeySDL::KeySDL()
    {
    }

    KeySDL::KeySDL( const KeySDL& key ): keyName( key.keyName ), m_keyIsDown( key.m_keyIsDown )
    {
        
    }

    KeySDL::~KeySDL()
    {
    }

    KeySDL& KeySDL::operator=( const KeySDL& key )
    {
        if( this != &key )
        {
            this->keyName = key.keyName;
            this->m_keyIsDown = key.m_keyIsDown;
        }
        return *this;
    }

    void KeySDL::setKeyName( const std::string& name )
    {
        this->keyName = name;
    }

    const std::string& KeySDL::getKeyName() const
    {
        return this->keyName;
    }

    void KeySDL::setKeyIsDown( const bool keyIsDow )
    {
        this->m_keyIsDown = keyIsDow;
    }

    const bool KeySDL::getKeyIsDown() const
    {
        return this->m_keyIsDown;
    }

}