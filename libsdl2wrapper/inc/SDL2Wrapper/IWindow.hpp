#pragma once

#include "SDL2Wrapper/SDL2Wrapper.hpp"
#include "SDL2Wrapper/ISprite.hpp"
#include "SDL2Wrapper/ITexture.hpp"
#include "SDL2Wrapper/IRender.hpp"
#include "SDL2Wrapper/IObjectRegister.hpp"
#include "CUL/STD_string.hpp"
#include "CUL/Color.hpp"
#include "CUL/IName.hpp"

namespace SDL2W
{
#ifdef _MSC_VER
    class SDL2WAPI CUL::IName;
#endif
    using Vector3Di = CUL::Math::Vector3Di;
    using Vector3Du = CUL::Math::Vector3Du;
    using ColorS = CUL::ColorS;
    using ColorE = CUL::ColorE;
    using IName = CUL::IName;

    class SDL2WAPI IWindow:
        public IRender,
        public IName,
        public IObjectRegister
    {
    public:
        enum class Type: char
        {
            NONE = 0,
            SDL_WIN
        };

        IWindow();
        IWindow( const IWindow& wind ) = delete;
        virtual ~IWindow();

        IWindow& operator=( const IWindow& window ) = delete;

        virtual const Vector3Di& getPos()const = 0;
        virtual void setPos( const Vector3Di& pos ) = 0;

        virtual const Vector3Du& getSize()const = 0;
        virtual void setSize( const Vector3Du& size ) = 0;

        virtual const Type getType() const = 0;

    protected:
    private:
    };
}
