#pragma once
#include "SDL2Wrapper/SDL2Wrapper.hpp"
#include "CUL/Path.hpp"
#include "CUL/CUL.hpp"
#include "CUL/Color.hpp"
#include "SDL2Wrapper/IObject.hpp"
#include <string>
#include <memory>
namespace SDL2W
{
    using ColorS = CUL::ColorS;
    using ColorE = CUL::ColorE;
    using Vector3Di = CUL::Math::Vector3Di;
    using Vector3Du = CUL::Math::Vector3Du;
    using Path = CUL::FS::Path;
    class SDL2WrapperAPI IWindow
    {
    public:
        IWindow(
            const CUL::Math::Vector3Di& pos,
            const CUL::Math::Vector3Du& size,
            const std::string& name );
        IWindow( const IWindow& wind );
        IWindow() = delete;

        virtual IObject* createObject(
            const Path& path,
            const IObject::Type type = IObject::Type::SPRITE )const = 0;

        virtual void renderNext() = 0;
        virtual void clear() = 0;

        IWindow& operator=( const IWindow& window );

        const Vector3Di& getPos()const;
        void setPos( const Vector3Di& pos );

        const Vector3Du& getSize()const;
        void setSize( const Vector3Du& size );

        const std::string& getName()const;
        void setName( const std::string& name );

        virtual void refreshScreen() = 0;
        virtual void renderAllObjects() = 0;

        virtual void setBackgroundColor( const ColorS& color ) = 0;
        virtual void setBackgroundColor( const ColorE color ) = 0;

        virtual ~IWindow();
    protected:
    private:
        Vector3Di position;
        Vector3Du m_size;
        std::string name;
    };
}