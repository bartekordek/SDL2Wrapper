#pragma once

#include "SDL2Wrapper/IWindow.hpp"
#include "SDL2Wrapper/IRender.hpp"

#include "CUL/STL_IMPORTS/STD_memory.hpp"
#include "CUL/STL_IMPORTS/STD_set.hpp"
#include "CUL/STL_IMPORTS/STD_mutex.hpp"
#include "CUL/Video/IFPSCounter.hpp"

struct SDL_Window;
struct SDL_Renderer;
struct SDL_Surface;

NAMESPACE_BEGIN( SDL2W )

#ifdef _MSC_VER
#pragma warning( push )
#pragma warning( disable: 4820 )
#endif

class RegularSDL2Window final:
    public IWindow
{
public:
    RegularSDL2Window() = delete;
    RegularSDL2Window( const WindowData& winData );

    ~RegularSDL2Window();

protected:
private:
    SDL_Window* createWindow( const WindowData& winDatae );
    SDL_Surface* createSurface( const Path& path );
    ITexture* createTexture( SDL_Surface* surface, const Path& path );
    void destroyObjects();

    // Inherited via IWindow
    void addObject( IObject* object ) override;
    void removeObject( IObject* object ) override;

    operator SDL_Window*() override;
    operator const SDL_Window*( ) override;

    const Vector3Di& getPos()const override;
    void setPos( const Vector3Di& pos ) override;

    const WindowSize& getSize()const override;
    void setSize( const WindowSize& size ) override;

    void setBackgroundColor( const ColorE color ) override;
    void setBackgroundColor( const ColorS& color ) override;
    void clearBuffers() override;
    void renderAll() override;
    void updateScreenBuffers() override;

    const IWindow::Type getType() const override;

    ITexture* createTexture( const Path& path ) override;
    ISprite* createSprite( const Path& path ) override;
    ISprite* createSprite( ITexture* tex ) override;

    const ColorS getBackgroundColor()const override;

    const double getScreenRatio() const override;

    WindowData m_windowData;
    ColorS m_backgroundColor;
    SDL_Window* m_window = nullptr;
    SDL_Renderer* m_renderer = nullptr;
    std::set<IObject*> m_objects;
    std::mutex m_objectsMtx;
    TextureMap m_textures;

    double m_screenRatio = 1.0;

    RegularSDL2Window( const RegularSDL2Window& win ) = delete;
    RegularSDL2Window& operator=( const RegularSDL2Window& right ) = delete;

};

#ifdef _MSC_VER
#pragma warning( pop )
#endif

NAMESPACE_END( SDL2W )