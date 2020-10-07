#pragma once

#include "SDL2Wrapper/IWindow.hpp"
#include "SDL2Wrapper/IRender.hpp"

#include "CUL/STL_IMPORTS/STD_memory.hpp"
#include "CUL/STL_IMPORTS/STD_set.hpp"
#include "CUL/STL_IMPORTS/STD_mutex.hpp"
#include "CUL/STL_IMPORTS/STD_utility.hpp"

#include "CUL/Video/IFPSCounter.hpp"
#include "CUL/Graphics/IImageLoader.hpp"
#include "CUL/Log/ILogger.hpp"

struct SDL_Window;
struct SDL_Renderer;
struct SDL_Surface;

NAMESPACE_BEGIN( SDL2W )

using SurfaceImage = std::pair<SDL_Surface*, CUL::Graphics::IImage*>;

#ifdef _MSC_VER
#pragma warning( push )
#pragma warning( disable: 4820 )
#endif

class RegularSDL2Window final:
    public IWindow
{
public:
    RegularSDL2Window( const WindowData& winData, ISDL2Wrapper* wrapper, CUL::LOG::ILogger* logger );

    ~RegularSDL2Window();

protected:
private:
    SDL_Window* createWindow( const WindowData& winDatae );
    SurfaceImage createSurface( const Path& path );
    ITexture* createTexture( SDL_Surface* surface, const Path& path );
    void destroyObjects();

    // Inherited via IWindow
    void addObject( IObject* object ) override;
    void removeObject( IObject* object ) override;

    operator SDL_Window*( ) override;
    operator const SDL_Window*( ) override;

    const Vector3Di& getPos() const override;
    void setPos( const Vector3Di& pos ) override;

    const WindowSize& getSize() const override;
    void setSize( const WindowSize& size ) override;

    void setBackgroundColor( const ColorE color ) override;
    void setBackgroundColor( const ColorS& color ) override;
    void clearBuffers() override;
    void renderAll() override;
    void updateScreenBuffers() override;

    IWindow::Type getType() const override;

    ITexture* createTexture( const Path& path ) override;
    ISprite* createSprite( const Path& path ) override;
    ISprite* createSprite( ITexture* tex ) override;

    ColorS getBackgroundColor() const override;

    WindowData m_windowData;
    ColorS m_backgroundColor;
    SDL_Window* m_window = nullptr;
    SDL_Renderer* m_renderer = nullptr;
    std::set<IObject*> m_objects;
    std::mutex m_objectsMtx;
    TextureMap m_textures;
    CUL::Graphics::IImageLoader* m_il = nullptr;
    ISDL2Wrapper* m_wrapper = nullptr;
    CUL::LOG::ILogger* m_logger = nullptr;

// Deleted:
    RegularSDL2Window( const RegularSDL2Window& win ) = delete;
    RegularSDL2Window( RegularSDL2Window&& win ) = delete;
    RegularSDL2Window& operator=( const RegularSDL2Window& right ) = delete;
    RegularSDL2Window& operator=( RegularSDL2Window&& right ) = delete;
    RegularSDL2Window() = delete;
};

#ifdef _MSC_VER
#pragma warning( pop )
#endif

NAMESPACE_END( SDL2W )