#pragma once

#include "SDL2Wrapper/ISprite.hpp"
#include "SDL2Wrapper/IRender.hpp"
#include "CUL/Graphics/IObjectRegister.hpp"
#include "CUL/Graphics/ITexture.hpp"
#include "CUL/Filesystem/Path.hpp"
#include "CUL/STL_IMPORTS/STD_map.hpp"
#include "CUL/Color.hpp"
#include "CUL/IName.hpp"
#include "CUL/STL_IMPORTS/STD_memory.hpp"

struct SDL_Window;

NAMESPACE_BEGIN( SDL2W )

using CDbl = const double;
using CShrt = const unsigned short;
using SmallCount = CShrt;

#ifdef _MSC_VER
class SDL2WAPI CUL::IName;
#endif
using Vector3Di = CUL::Math::Vector3Di;
using Vector3Du = CUL::Math::Vector3Du;
using ColorS = CUL::ColorS;
using ColorE = CUL::ColorE;
using IName = CUL::IName;
using Path = CUL::FS::Path;

using TextureMap = std::map<CUL::MyString, std::unique_ptr<ITexture>>;

#ifdef _MSC_VER
#pragma warning( push )
#pragma warning( disable: 4820 )
#endif

class SDL2WAPI IWindow:
    public IRender,
    public IName,
    public CUL::Graphics::IObjectRegister
{
public:
    enum class Type: char
    {
        NONE = 0,
        SDL_WIN,
        SDL_OPENGL
    };

    IWindow();
    IWindow( const Vector3Di& pos,
        const Vector3Du& size,
        CUL::CnstMyStr& name,
        const bool withOpenGL = true ) = delete;

    virtual ~IWindow();

    virtual const Vector3Di& getPos()const = 0;
    virtual void setPos( const Vector3Di& pos ) = 0;

    virtual const Vector3Du& getSize()const = 0;
    virtual void setSize( const Vector3Du& size ) = 0;

    virtual const Type getType() const = 0;

    virtual ITexture* createTexture( const Path& path ) = 0;
    virtual ISprite* createSprite( const Path& path ) = 0;
    virtual ISprite* createSprite( ITexture* tex ) = 0;

    virtual SDL_Window* getSDLWindow() const = 0;

    void setWindowID( cunt id );
    const unsigned int getWindowID() const;

protected:

private:

    unsigned int m_winId = 0;

    IWindow( const IWindow& wind ) = delete;
    IWindow& operator=( const IWindow& window ) = delete;

};

#ifdef _MSC_VER
#pragma warning( pop )
#endif

NAMESPACE_END( CUL )