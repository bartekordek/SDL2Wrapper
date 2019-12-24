#include "RegularSDL2Window.hpp"
#include "TextureSDL.hpp"
#include "Sprite.hpp"
#include "TextureSDL.hpp"

#include "SDL2Wrapper/IMPORT_SDL.hpp"
#include "SDL2Wrapper/IMPORT_SDL_video.hpp"

#include "CUL/Filesystem/FS.hpp"

#include "SimpleUtils.hpp"

#include "CUL/STL_IMPORTS/STD_iostream.hpp"

using namespace SDL2W;

using IPivot = CUL::Math::IPivot;

RegularSDL2Window::RegularSDL2Window( const WindowData& winData ):
    m_windowData( winData )
{
    m_window = createWindow( winData );

    const auto id = SDL_GetWindowID( m_window );
    setWindowID( id );

    m_renderer = SDL_CreateRenderer( m_window, -1, SDL_RENDERER_ACCELERATED );
    Assert( nullptr != m_renderer, "Cannot create renderer." );
    SDL_RendererInfo info;
    auto rendererInfoResult = SDL_GetRendererInfo( m_renderer, &info );
    CUL::String rendererInfoSummary( "Renderer INFO:\n" );
    rendererInfoSummary += "Name = " + CUL::String( info.name ) + "\n";
    rendererInfoSummary += "Max texture width = " + CUL::String( info.max_texture_width ) + "\n";
    rendererInfoSummary += "Max texture height = " + CUL::String( info.max_texture_width ) + "\n";
    logMsg( rendererInfoSummary, CUL::LOG::Severity::INFO );

    Assert( 0 == rendererInfoResult, "Cannot get renderer info." );

    setName( winData.name );
}

SDL_Window* RegularSDL2Window::createWindow( const WindowData& winData )
{
    auto& pos = winData.pos;
    auto& size = winData.size;
    auto& opengl = winData.withOpenGL;
    auto& winName = winData.name;

    logMsg( "Creating window with:", CUL::LOG::Severity::INFO );
    logMsg( "Pos.x = " + CUL::String( pos.getX()) + ", Pos.y = " + CUL::String( pos.getY() ), CUL::LOG::Severity::INFO );
    logMsg( "Width = " + CUL::String( size.getWidth() ) + ", height = " + CUL::String( size.getHeight() ), CUL::LOG::Severity::INFO );
    SDL_Window* result = nullptr;
    Uint32 windowFlags = SDL_WINDOW_SHOWN;
    if( opengl )
    {
        windowFlags |= SDL_WINDOW_OPENGL;
    }

    auto targetWidth = static_cast<int>( size.getWidth() );
    auto targetHeight = static_cast<int>( size.getHeight() );

    result = SDL_CreateWindow(
        winName.cStr(),
        static_cast< int >( pos.getX() ),
        static_cast< int >( pos.getY() ),
        targetWidth,
        targetHeight,
        windowFlags );
    if( nullptr == result )
    {
        auto sdlError = SDL_GetError();
        CUL::String s_sdlError( sdlError );
        logMsg(
            "SDL ERROR: [ " + s_sdlError + " ] ", CUL::LOG::Severity::CRITICAL );
        Assert( false, "The Window has not been initialized." );
    }

    int resultWidth = 0;
    int resultHeight = 0;
    SDL_GetWindowSize( result, &resultWidth, &resultHeight );
    Assert( targetWidth == resultWidth, "Result window width is different than target width." );
    Assert( targetHeight == resultHeight, "Result window height is different than target height." );

    m_screenRatio = ( 1.0 * targetWidth ) / ( 1.0 * targetHeight );

    return result;
}

RegularSDL2Window::operator SDL_Window*()
{
    return m_window;
}

RegularSDL2Window::operator const SDL_Window*( )
{
    return m_window;
}

RegularSDL2Window::~RegularSDL2Window()
{
    logMsg( "RegularSDL2Window::~RegularSDL2Window()" );
    destroyObjects();

    Assert( nullptr != m_renderer, "The Renderer has been destroyed somwhere else." );
    SDL_DestroyRenderer( m_renderer );
    m_renderer = nullptr;

    Assert( nullptr != m_window, "The Window has been destroyed somwhere else." );
    SDL_DestroyWindow( m_window );
    m_window = nullptr;
}

void RegularSDL2Window::destroyObjects()
{
    std::lock_guard<std::mutex> objectsMutexGuard( m_objectsMtx );
    m_textures.clear();
}

void RegularSDL2Window::updateScreenBuffers()
{
    if( m_windowData.withOpenGL )
    {
        Assert( nullptr != m_window, "The Window is not initialized." );
        SDL_GL_SwapWindow( m_window );
        // ^ https://forums.libsdl.org/viewtopic.php?p=52399
    }
    else
    {
        Assert( nullptr != m_renderer, "The Renderer is not initialized." );
        SDL_RenderPresent( m_renderer );
    }
    frameHasEnded();
}

void RegularSDL2Window::renderAll()
{
    SDL_SetRenderDrawColor(
        m_renderer,
        m_backgroundColor.getRUI(),
        m_backgroundColor.getGUI(),
        m_backgroundColor.getBUI(),
        m_backgroundColor.getAUI() );
    std::lock_guard<std::mutex> objectsMutexGuard(m_objectsMtx);
    for( auto& object : m_objects )
    {
        if ( IObject::Type::SPRITE == object->getType() )
        {
            auto sprite = static_cast<Sprite*>( object );
            auto& pos = object->getRenderPosition();
            auto& size = object->getSizeAbs();
            auto pivot = object->getPivot( IPivot::PivotType::ABSOLUTE );

            SDL_Rect renderQuad;
            renderQuad.x = static_cast<int>( pos.getX() );
            renderQuad.y = static_cast<int>( pos.getY() );
            renderQuad.w = static_cast<int>( size.getX() );
            renderQuad.h = static_cast<int>( size.getY() );

            std::unique_ptr<SDL_Rect> srcRect;

            auto tex = sprite->getTexture();
            auto texSDLW = static_cast< TextureSDL* >( tex );

            const double angle = sprite->getAngle().getValueD();

            SDL_Point center;
            center.x = static_cast<int>( pivot.getX() );
            center.y = static_cast<int>( pivot.getY() );

            auto result = SDL_RenderCopyEx(
                m_renderer,
                texSDLW->getTexture(),
                srcRect.get(),
                &renderQuad,
                angle, &center, SDL_RendererFlip::SDL_FLIP_NONE );
            CUL::Assert::simple( result == 0, "Cannot render SDL texture..." );
        }
    }
}

void RegularSDL2Window::setBackgroundColor( const ColorE color )
{
    setBackgroundColor( ColorS( color ) );
}

void RegularSDL2Window::clearBuffers()
{
    CUL::Assert::simple( nullptr != m_renderer, "The Renderer has been deleted somwhere else." );
    SDL_RenderClear( m_renderer );
}

void RegularSDL2Window::setBackgroundColor( const ColorS& color )
{
    m_backgroundColor = color;
}

const Vector3Di& RegularSDL2Window::getPos() const
{
    return m_windowData.pos;
}

void RegularSDL2Window::setPos( const Vector3Di& pos )
{
    m_windowData.pos = pos;
}

const WindowSize& RegularSDL2Window::getSize() const
{
    return m_windowData.size;
}

void RegularSDL2Window::setSize( const WindowSize& size )
{
    m_windowData.size = size;
}

const IWindow::Type RegularSDL2Window::getType() const
{
    return IWindow::Type::SDL_WIN;
}

ISprite* RegularSDL2Window::createSprite( const Path& objPath )
{
    logMsg( "ISprite* RegularSDL2Window::createSprite( const Path& objPath )" );
    ISprite* result = nullptr;
    CUL::Assert::simple( objPath.getPath() != "", "EMTPY PATH." );
    auto it = m_textures.find( objPath.getPath().string() );
    if( m_textures.end() == it )
    {
        logMsg( "ISprite* RegularSDL2Window::createSprite: sprite not found, creating..." );
        auto tex = createTexture( objPath );
        result = createSprite( tex );
        logMsg( "ISprite* RegularSDL2Window::createSprite: sprite not found, creating... Done." );
    }
    else
    {
        logMsg( "ISprite* RegularSDL2Window::createSprite: sprite found, fetching..." );
        auto tex = it->second.get();
        logMsg( "ISprite* RegularSDL2Window::createSprite: creating sprite..." );
        result = createSprite( tex );
        logMsg( "ISprite* RegularSDL2Window::createSprite: creating sprite Done." );
        logMsg( "ISprite* RegularSDL2Window::createSprite: sprite found, Done." );
    }
    logMsg( "ISprite* RegularSDL2Window::createSprite( const Path& objPath )end" );
    return result;
}

ITexture* RegularSDL2Window::createTexture( const Path& objPath )
{
    logMsg( "ITexture* RegularSDL2Window::createTexture( const Path& objPath )" );
    ITexture* result = nullptr;
    CUL::Assert::simple( objPath.getPath() != "", "EMTPY PATH." );
    auto it = m_textures.find( objPath.getPath().string() );
    if( m_textures.end() == it )
    {
        logMsg( "ITexture* RegularSDL2Window::createTexture texture not found, creating surface..." );
        auto surface = createSurface( objPath );
        logMsg( "ITexture* RegularSDL2Window::createTexture texture not found, creating surface done." );
        logMsg( "ITexture* RegularSDL2Window::createTexture creating texture..." );
        auto tex = createTexture( surface, objPath );
        logMsg( "ITexture* RegularSDL2Window::createTexture creating texture done." );
        logMsg( "ITexture* RegularSDL2Window::createTexture freeing surface..." );
        SDL_FreeSurface( surface );
        surface = nullptr;
        logMsg( "ITexture* RegularSDL2Window::createTexture freeing surface done." );
        result = tex;
    }
    else
    {
        logMsg( "ITexture* RegularSDL2Window::createTexture texture found, fetching..." );
        result = it->second.get();
        logMsg( "ITexture* RegularSDL2Window::createTexture texture found, fetching done." );
    }
    return result;
}

ISprite* RegularSDL2Window::createSprite(
    ITexture* tex )
{
    auto spritePtr = new Sprite();
    spritePtr->setTexture( tex );
    addObject( spritePtr );
    return spritePtr;
}

SDL_Surface* RegularSDL2Window::createSurface(
    const Path& path )
{
    std::cout << "Current dir: " << CUL::FS::FSApi::getCurrentDir().cStr() << "\n";
    std::cout << "Checking for path...\n";
    if( false == path.exists() )
    {
        std::cout << "Checking for path FAILED\n";
        Assert( false, "File " + path.getPath() + " does not exist." );
    }
    SDL_Surface* result = nullptr;
    if( ".bmp" == path.getExtension() )
    {
        std::cout << "Checking for sdl load bmp...\n";
        result = SDL_LoadBMP( path.getPath().cStr() );
    }

    if( ".png" == path.getExtension() )
    {
        auto value = path.getPath().cStr();
        const char* valueAsChar = value;
        std::cout << "Checking for sdl IMG_Load...\n";
        std::cout << "File: " << valueAsChar << "\n";
        result = IMG_Load( valueAsChar );//Crash on linux.
        IMG_GetError();
        std::cout << "Checking for sdl IMG_Load... Done.\n";
    }
    std::cout << "Checking for file loading completion...\n";
    Assert( nullptr != result, "Cannot load: " + path.getPath() );
    std::cout << "Checking for file loading completion... Done.\n";
    return result;
}

ITexture* RegularSDL2Window::createTexture( SDL_Surface* surface, const Path& path )
{
    logMsg( "ITexture* RegularSDL2Window::createTexture( SDL_Surface* surface, const Path& path )" );
    CUL::Assert::simple( nullptr != m_renderer, "RENDERER NOT READY!\n" );
    CUL::Assert::simple( nullptr != surface, "SURFACE IS NULL!\n" );

    auto texSDL = new TextureSDL();

    logMsg( "ITexture* RegularSDL2Window::createTexture: creating texture from surface..." );
    auto tex = SDL_CreateTextureFromSurface( m_renderer, surface );
    logMsg( "ITexture* RegularSDL2Window::createTexture: creating texture from surface done." );
    CUL::Assert::simple(
        nullptr != tex,
        "Cannot create texture from " +
        path.getPath() +
        " does not exist." );

    texSDL->setTexture( tex, path );
    m_textures[ path.getPath() ] = std::unique_ptr<ITexture>( texSDL );
    return texSDL;
}

void RegularSDL2Window::addObject( IObject* object )
{
    std::lock_guard<std::mutex> objectsMutexGuard( m_objectsMtx );
    m_objects.insert( object );
}

void RegularSDL2Window::removeObject( IObject* object )
{
    std::lock_guard<std::mutex> objectsMutexGuard( m_objectsMtx );
    m_objects.erase( object );
}

const double RegularSDL2Window::getScreenRatio() const
{
    return m_screenRatio;
}

const ColorS RegularSDL2Window::getBackgroundColor() const
{
    return m_backgroundColor;
}