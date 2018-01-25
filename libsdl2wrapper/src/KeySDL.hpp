#pragma once

#include "SDL2Wrapper/IKey.hpp"
#include <string>

namespace SDL2W
{
    class KeySDL: public IKey
    {
    public:
        KeySDL();
        KeySDL( const KeySDL& key );
        virtual ~KeySDL();
        KeySDL& operator=( const KeySDL& key );

        void setKeyName( const std::string& keyName ) override;
        const std::string& getKeyName()const override;
        void setKeyIsDown( const bool keyIsDown ) override;
        const bool getKeyIsDown()const override;
    protected:
    private:
        std::string keyName;
        bool m_keyIsDown = false;
    };
}