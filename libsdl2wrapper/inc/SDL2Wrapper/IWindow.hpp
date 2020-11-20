#pragma once

#include "SDL2Wrapper/ISprite.hpp"
#include "SDL2Wrapper/IRender.hpp"
#include "CUL/Graphics/IObjectRegister.hpp"
#include "CUL/Graphics/ITexture.hpp"
#include "CUL/Filesystem/Path.hpp"
#include "CUL/STL_IMPORTS/STD_map.hpp"
#include "CUL/Graphics/Color.hpp"
#include "CUL/IName.hpp"
#include "CUL/STL_IMPORTS/STD_memory.hpp"
#include "CUL/Graphics/Size2D.hpp"

struct SDL_Window;

NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( Video )
class IFPSCounter;
NAMESPACE_END( Video )
NAMESPACE_END( CUL )


NAMESPACE_BEGIN( SDL2W )

using CDbl = const double;
using CShrt = const unsigned short;
using SmallCount = CShrt;
using Size2Du = CUL::Graphics::Size2Du;
using Size2Di = CUL::Graphics::Size2Di;
using WindowSize = Size2Di;

#ifdef _MSC_VER
class SDL2WAPI CUL::IName;
#endif
class ISDL2Wrapper;

using Vector3Di = CUL::MATH::Vector3Di;
using Vector3Du = CUL::MATH::Vector3Du;
using ColorS = CUL::Graphics::ColorS;
using ColorE = CUL::Graphics::ColorE;
using IName = CUL::IName;
using Path = CUL::FS::Path;
using String = CUL::String;

using TextureMap = std::map<CUL::String, std::unique_ptr<ITexture>>;

#ifdef _MSC_VER
#pragma warning( push )
#pragma warning( disable: 4820 )
#endif

struct SDL2WAPI WindowData
{
    Vector3Di pos = Vector3Di( 0, 0, 0 );
    WindowSize size = WindowSize( 640, 480 );
    String name = "";
    String rendererName = "opengl";

    WindowData() = default;

    WindowData( const WindowData& arg ):
        pos( arg.pos ),
        size( arg.size ),
        name( arg.name ),
        rendererName( arg.rendererName )
    {
    }

    WindowData& operator=( const WindowData& rhv )
    {
        if( this != &rhv )
        {
            pos = rhv.pos;
            size = rhv.size;
            name = rhv.name;
            rendererName = rhv.rendererName;
        }
        return *this;
    }

    ~WindowData() = default;
};

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
    IWindow( const WindowData& data ) = delete;

    virtual ~IWindow();

    virtual const Vector3Di& getPos() const = 0;
    virtual void setPos( const Vector3Di& pos ) = 0;

    virtual const WindowSize& getSize() const = 0;
    virtual void setSize( const WindowSize& size ) = 0;

    virtual Type getType() const = 0;

    virtual ITexture* createTexture( const Path& path ) = 0;
    virtual ISprite* createSprite( const Path& path ) = 0;
    virtual ISprite* createSprite( ITexture* tex ) = 0;

    void setWindowID( Cunt id );
    unsigned int getWindowID() const;

    virtual void toggleFpsCounter( const bool on, const short unsigned everyNsecond = 2 ) = 0;

    virtual CUL::Video::IFPSCounter* const getFpsCounter() = 0;

    virtual operator ::SDL_Window*( ) = 0;
    virtual operator const ::SDL_Window*( ) = 0;

protected:

private:

    unsigned int m_winId = 0;

    IWindow( const IWindow& wind ) = delete;
    IWindow( IWindow&& wind ) = delete;
    IWindow& operator=( const IWindow& window ) = delete;
    IWindow& operator=( IWindow&& window ) = delete;
};

#ifdef _MSC_VER
#pragma warning( pop )
#endif

NAMESPACE_END( CUL )