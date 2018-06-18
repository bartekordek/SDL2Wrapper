#pragma once

#include "SDL2Wrapper/IKey.hpp"
#include "CUL/STD_string.hpp"

namespace SDL2W
{
#ifdef _MSC_VER
#pragma warning( push )
#pragma warning( disable: 4820 )
#endif
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
#ifdef _MSC_VER
#pragma warning( pop )
#endif
}