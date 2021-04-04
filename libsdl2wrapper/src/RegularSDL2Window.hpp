#pragma once

#include "SDL2Wrapper/IWindow.hpp"
#include "SDL2Wrapper/IRender.hpp"
#include "SDL2Wrapper/WindowData.hpp"

#include "SDL2Wrapper/IMPORT_SDL.hpp"
#include "SDL2Wrapper/IMPORT_SDL_video.hpp"


#include "CUL/STL_IMPORTS/STD_memory.hpp"
#include "CUL/STL_IMPORTS/STD_set.hpp"
#include "CUL/STL_IMPORTS/STD_mutex.hpp"
#include "CUL/STL_IMPORTS/STD_utility.hpp"

#include "CUL/Video/IFPSCounter.hpp"
#include "CUL/Graphics/IImageLoader.hpp"
#include "CUL/CULInterface.hpp"
#include "CUL/STL_IMPORTS/STD_atomic.hpp"
#include "CUL/STL_IMPORTS/STD_thread.hpp"

struct SDL_Window;
struct SDL_Renderer;
struct SDL_Surface;

NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( FS )
class Path;
NAMESPACE_END( FS )
NAMESPACE_END( CUL )

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
    RegularSDL2Window(
        const WindowData& winData,
        ISDL2Wrapper* wrapper,
        CUL::CULInterface* culInterface );

    void fetchSreenData();

    ~RegularSDL2Window();
protected:
private:
    SDL_Window* createWindow( const WindowData& winDatae );
    SurfaceImage createSurface( const CUL::FS::Path& path );
    CUL::Graphics::ITexture* createTexture( SDL_Surface* surface, const CUL::FS::Path& path );
    void destroyObjects();
    WindowSize getCurrentScreenNativeResolution() const override;

    void toggleFpsCounter( bool on, short unsigned everyNsecond = 2 ) override;
    void closeInfoLoop();
    void infoLoop();
    std::unique_ptr<CUL::Video::IFPSCounter> m_fpsCounter;
    std::atomic<bool> m_runInfoLoop = false;
    std::atomic<unsigned int> m_sleepTimeInfoLoop = 2u;
    std::thread m_infoPrintLoop;

    // Inherited via IWindow
    void addObject( IObject* object ) override;
    void removeObject( IObject* object ) override;

    operator SDL_Window*( ) override;
    operator const SDL_Window*( ) override;

    const CUL::Graphics::Pos2Di& getPos() const override;
    void setPos( const CUL::Graphics::Pos2Di& pos ) override;

    const WindowSize& getSize() const override;
    void setSize( const WindowSize& size ) override;

    void setBackgroundColor( const ColorE color ) override;
    void setBackgroundColor( const ColorS& color ) override;
    void clearBuffers() override;
    void renderAll() override;
    void updateScreenBuffers() override;

    IWindow::Type getType() const override;

    CUL::Graphics::ITexture* createTexture( const CUL::FS::Path& path ) override;
    ISprite* createSprite( const CUL::FS::Path& path ) override;
    ISprite* createSprite( CUL::Graphics::ITexture* tex ) override;

    ColorS getBackgroundColor() const override;

    CUL::Video::IFPSCounter*  getFpsCounter() override;
    void setFullscreen( bool fullscreen ) override;

    WindowData m_windowData;
    bool m_openGL = false;
    ColorS m_backgroundColor;
    SDL_Window* m_window = nullptr;
    SDL_Renderer* m_renderer = nullptr;
    std::set<IObject*> m_objects;
    std::mutex m_objectsMtx;
    TextureMap m_textures;
    CUL::Graphics::IImageLoader* m_il = nullptr;
    ISDL2Wrapper* m_wrapper = nullptr;
    CUL::CULInterface* m_culInterface = nullptr;
    CUL::FS::FSApi* m_fsApi = nullptr;
    CUL::LOG::ILogger* m_logger = nullptr;
    SDL_DisplayMode m_nativeDisplayMode;

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
