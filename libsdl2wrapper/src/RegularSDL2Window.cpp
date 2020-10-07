#include "RegularSDL2Window.hpp"
#include "TextureSDL.hpp"
#include "Sprite.hpp"
#include "TextureSDL.hpp"

#include "SDL2Wrapper/IMPORT_SDL.hpp"
#include "SDL2Wrapper/IMPORT_SDL_video.hpp"

#include "CUL/Filesystem/FS.hpp"

#include "SimpleUtils.hpp"

#include "CUL/STL_IMPORTS/STD_iostream.hpp"
#include "SDL2Wrapper/ISDL2Wrapper.hpp"

using namespace SDL2W;

using IPivot = CUL::MATH::IPivot;

RegularSDL2Window::RegularSDL2Window(
    const WindowData& winData,
    ISDL2Wrapper* wrapper,
    CUL::LOG::ILogger* logger ):
    m_windowData( winData ),
    m_wrapper( wrapper ),
    m_logger( logger )
{
    m_window = createWindow( winData );

    setWindowID( SDL_GetWindowID( m_window ) );

    m_renderer = SDL_CreateRenderer( m_window, -1, SDL_RENDERER_ACCELERATED );
    Assert( nullptr != m_renderer, "Cannot create renderer." );
    SDL_RendererInfo info;
    const auto rendererInfoResult = SDL_GetRendererInfo( m_renderer, &info );
    Assert( 0 == rendererInfoResult, "Cannot get renderer info." );
    m_logger->log( "Renderer INFO:", CUL::LOG::Severity::INFO );
    m_logger->log( "Name = " + CUL::String( info.name ), CUL::LOG::Severity::INFO );
    m_logger->log( "Max texture width = " + CUL::String( info.max_texture_width ), CUL::LOG::Severity::INFO );
    m_logger->log( "Max texture height = " + CUL::String( info.max_texture_width ), CUL::LOG::Severity::INFO );
    setName( winData.name );
    m_il = CUL::Graphics::IImageLoader::createConcrete( m_wrapper->getConfig() );
}

SDL_Window* RegularSDL2Window::createWindow( const WindowData& winData )
{
    auto& pos = winData.pos;
    auto& size = winData.size;
    auto& opengl = winData.withOpenGL;
    auto& winName = winData.name;

    m_logger->log( "Creating window with:", CUL::LOG::Severity::INFO );
    m_logger->log( "Pos.x = " + CUL::String( pos.getX() ) + ", Pos.y = " + CUL::String( pos.getY() ), CUL::LOG::Severity::INFO );
    m_logger->log( "Width = " + CUL::String( size.getWidth() ) + ", height = " + CUL::String( size.getHeight() ), CUL::LOG::Severity::INFO );
    SDL_Window* result = nullptr;
    Uint32 windowFlags = SDL_WINDOW_SHOWN;
    if( opengl )
    {
        windowFlags |= SDL_WINDOW_OPENGL;
    }

    const auto targetWidth = static_cast<int>( size.getWidth() );
    const auto targetHeight = static_cast<int>( size.getHeight() );

    result = SDL_CreateWindow(
        winName.cStr(),
        static_cast<int>( pos.getX() ),
        static_cast<int>( pos.getY() ),
        targetWidth,
        targetHeight,
        windowFlags );
    if( nullptr == result )
    {
        auto sdlError = SDL_GetError();
        CUL::String s_sdlError( sdlError );
        m_logger->log(
            "SDL ERROR: [ " + s_sdlError + " ] ", CUL::LOG::Severity::CRITICAL );
        Assert( false, "The Window has not been initialized." );
    }

    return result;
}

RegularSDL2Window::operator SDL_Window*( )
{
    return m_window;
}

RegularSDL2Window::operator const SDL_Window*( )
{
    return m_window;
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
    std::lock_guard<std::mutex> objectsMutexGuard( m_objectsMtx );
    for( auto& object : m_objects )
    {
        if( IObject::Type::SPRITE == object->getType() )
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
            const auto texSDLW = static_cast<TextureSDL*>( tex );

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

IWindow::Type RegularSDL2Window::getType() const
{
    return IWindow::Type::SDL_WIN;
}

ISprite* RegularSDL2Window::createSprite( const Path& objPath )
{
    ISprite* result = nullptr;
    CUL::Assert::simple( objPath.getPath() != "", "EMTPY PATH." );
    auto it = m_textures.find( objPath.getPath().string() );
    if( m_textures.end() == it )
    {
        auto tex = createTexture( objPath );
        result = createSprite( tex );
    }
    else
    {
        auto tex = it->second.get();
        result = createSprite( tex );
    }
    return result;
}

ITexture* RegularSDL2Window::createTexture( const Path& objPath )
{
    ITexture* result = nullptr;
    CUL::Assert::simple( objPath.getPath() != "", "EMTPY PATH." );
    auto it = m_textures.find( objPath.getPath().string() );
    if( m_textures.end() == it )
    {
        auto surface = createSurface( objPath );
        auto tex = createTexture( surface.first, objPath );
        SDL_FreeSurface( surface.first );
        surface.first = nullptr;

        delete surface.second;
        surface.second = nullptr;
        result = tex;
    }
    else
    {
        result = it->second.get();
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

SurfaceImage RegularSDL2Window::createSurface(
    const Path& path )
{
    SurfaceImage surfaceImage;

    std::cout << "Current dir: " <<
        CUL::FS::FSApi::getCurrentDir().cStr() <<
        "\n";
    if( false == path.exists() )
    {
        std::cout << "Checking for path FAILED\n";
        Assert( false, "File " + path.getPath() + " does not exist." );
    }

    auto image = m_il->loadImage( path );
    Assert( nullptr != image, "Cannot load: " + path.getPath() );

    const auto& imageInfo = image->getImageInfo();

    Uint32 pixelFormat = 0;
    switch( imageInfo.pixelFormat )
    {
        case CUL::Graphics::PixelFormat::RGB:
            pixelFormat = SDL_PIXELFORMAT_RGB24;
        break;
        case CUL::Graphics::PixelFormat::ARGB:
            pixelFormat = SDL_PIXELFORMAT_ARGB32;
        break;
        case CUL::Graphics::PixelFormat::RGBA:
            pixelFormat = SDL_PIXELFORMAT_RGBA32;
        break;
        case CUL::Graphics::PixelFormat::NONE:
            Assert( false, "Pixel format of surface not set." );
        break;
        case CUL::Graphics::PixelFormat::BGR:
            pixelFormat = SDL_PIXELFORMAT_BGR24;
        break;
        case CUL::Graphics::PixelFormat::BGRA:
            pixelFormat = SDL_PIXELFORMAT_BGRA32;
        break;
        case CUL::Graphics::PixelFormat::ABGR:
            pixelFormat = SDL_PIXELFORMAT_ABGR32;
        break;
        case CUL::Graphics::PixelFormat::TEST:
            pixelFormat = SDL_PIXELFORMAT_RGB555;
        break;
    }


    surfaceImage.first = SDL_CreateRGBSurfaceWithFormatFrom( (void*) image->getData(),
        imageInfo.size.width, imageInfo.size.height,
        imageInfo.depth, imageInfo.pitch, pixelFormat );

    Assert( nullptr != surfaceImage.first, "Cannot create surf: " + path.getPath() );
    Assert( 0 != surfaceImage.first->pixels, "Cannot create surf: " + path.getPath() );

    surfaceImage.second = image;

    return surfaceImage;
}

ITexture* RegularSDL2Window::createTexture( SDL_Surface* surface, const Path& path )
{
    CUL::Assert::simple( nullptr != m_renderer, "RENDERER NOT READY!\n" );
    CUL::Assert::simple( nullptr != surface, "SURFACE IS NULL!\n" );

    auto texSDL = new TextureSDL();

    auto tex = SDL_CreateTextureFromSurface( m_renderer, surface );
    CUL::Assert::simple(
        nullptr != tex,
        "Cannot create texture from " +
        path.getPath() +
        " does not exist." );

    texSDL->setTexture( tex, path );
    m_textures[path.getPath()] = std::unique_ptr<ITexture>( texSDL );
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

ColorS RegularSDL2Window::getBackgroundColor() const
{
    return m_backgroundColor;
}


RegularSDL2Window::~RegularSDL2Window()
{
    m_logger->log( "RegularSDL2Window::~RegularSDL2Window()" );
    destroyObjects();

    Assert( nullptr != m_renderer, "The Renderer has been destroyed somwhere else." );
    SDL_DestroyRenderer( m_renderer );
    m_renderer = nullptr;

    Assert( nullptr != m_window, "The Window has been destroyed somwhere else." );
    SDL_DestroyWindow( m_window );
    m_window = nullptr;
}
