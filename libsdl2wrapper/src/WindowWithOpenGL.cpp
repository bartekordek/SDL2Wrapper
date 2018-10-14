#include "WindowWithOpenGL.hpp"
#include "TextureSDL.hpp"
#include "Sprite.hpp"
#include "TextureSDL.hpp"

#include "SDL2Wrapper/IMPORT_SDL.hpp"
#include "SDL2Wrapper/IMPORT_SDL_video.hpp"
#include "IMPORT_SDL_image.hpp"

#include "CUL/FS.hpp"
#include "CUL/SimpleAssert.hpp"

#include "IMPORT_SDL_opengl.hpp"

using namespace SDL2W;

WindowWithOpenGL::WindowWithOpenGL(
    const Vector3Di& pos,
    const Vector3Du& size,
    CnstStr& name,
    const int major, const int minor ):
    m_position( pos ),
    m_size( size )
{
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, major );
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, minor );
    Uint32 windowFlags = SDL_WINDOW_OPENGL;
    this->m_window = SDL_CreateWindow(
        this->getName().c_str(),
        static_cast<int>( this->getPos().getX() ),
        static_cast<int>( this->getPos().getY() ),
        static_cast<int>( this->getSize().getX() ),
        static_cast<int>( this->getSize().getY() ),
        windowFlags );
    this->m_renderer = SDL_CreateRenderer( this->m_window, -1, SDL_RENDERER_ACCELERATED );
    this->m_oglContext = SDL_GL_CreateContext( this->m_window );
    setName( name );
    this->m_fpsCounter.reset( CUL::Video::FPSCounterFactory::getConcreteFPSCounter() );
    this->m_fpsCounter->start();

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    glClearColor( 0.f, 0.f, 0.f, 1.f );
}

WindowWithOpenGL::~WindowWithOpenGL()
{
    std::lock_guard<std::mutex> objectsMutexGuard( this->m_objectsMtx );
    this->m_textures.clear();
    CUL::Assert::simple(
        this->m_window,
        "The Window has been destroyed somwhere else." );
    CUL::Assert::simple(
        this->m_renderer,
        "The Renderer has been destroyed somwhere else." );
    SDL_DestroyRenderer( this->m_renderer );
    this->m_renderer = nullptr;
    SDL_DestroyWindow( this->m_window );
    this->m_window = nullptr;
}

void WindowWithOpenGL::updateScreenBuffers()
{
    CUL::Assert::simple( this->m_renderer, "The Renderer has not been initialized." );
    CUL::Assert::simple( this->m_window, "The Window has not been initialized." );
    SDL_RenderPresent( this->m_renderer );
    SDL_GL_SwapWindow( this->m_window );
}

void WindowWithOpenGL::renderAll()
{
    SDL_SetRenderDrawColor(
        this->m_renderer,
        this->m_backgroundColor.getRUI(),
        this->m_backgroundColor.getGUI(),
        this->m_backgroundColor.getBUI(),
        this->m_backgroundColor.getAUI() );
    std::lock_guard<std::mutex> objectsMutexGuard( this->m_objectsMtx );
    for( auto& object : this->m_objects )
    {
        if( IObject::Type::SPRITE == object->getType() )
        {
            auto sprite = static_cast<Sprite*>( object );
            auto& pos = object->getRenderPosition();
            auto& size = object->getSizeAbs();
            auto pivot = object->getPivot( PivotType::ABSOLUTE );

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
                this->m_renderer,
                texSDLW->getTexture(),
                srcRect.get(),
                &renderQuad,
                angle, &center, SDL_RendererFlip::SDL_FLIP_NONE );
            CUL::Assert::simple( result == 0, "Cannot render SDL texture..." );
        }
    }
    SDL_GL_SwapWindow( this->m_window );

    this->m_fpsCounter->increase();
}

void WindowWithOpenGL::setBackgroundColor( const ColorE color )
{
    setBackgroundColor( color );
}

void WindowWithOpenGL::clearBuffers()
{
    CUL::Assert::simple( this->m_renderer, "The Renderer has been deleted somwhere else." );
    SDL_RenderClear( this->m_renderer );
}

void WindowWithOpenGL::setBackgroundColor( const ColorS& color )
{
    this->m_backgroundColor = color;
}

const Vector3Di& WindowWithOpenGL::getPos()const
{
    return this->m_position;
}

void WindowWithOpenGL::setPos( const Vector3Di& pos )
{
    this->m_position = pos;
}

const Vector3Du& WindowWithOpenGL::getSize()const
{
    return this->m_size;
}

void WindowWithOpenGL::setSize( const Vector3Du& size )
{
    this->m_size = size;
}

const IWindow::Type WindowWithOpenGL::getType() const
{
    return IWindow::Type::SDL_WIN;
}

ISprite* WindowWithOpenGL::createSprite( const Path& objPath )
{
    ISprite* result = nullptr;
    CUL::Assert::simple( objPath.getPath() != "", "EMTPY PATH." );
    auto it = this->m_textures.find( objPath.getPath() );
    if( this->m_textures.end() == it )
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

ITexture* WindowWithOpenGL::createTexture( const Path& objPath )
{
    ITexture* result = nullptr;
    CUL::Assert::simple( objPath.getPath() != "", "EMTPY PATH." );
    auto it = this->m_textures.find( objPath.getPath() );
    if( this->m_textures.end() == it )
    {
        auto surface = createSurface( objPath );
        auto tex = createTexture( surface, objPath );
        SDL_FreeSurface( surface );
        surface = nullptr;
        result = tex;
    }
    else
    {
        result = it->second.get();
    }
    return result;
}

ISprite* WindowWithOpenGL::createSprite(
    ITexture* tex )
{
    auto spritePtr = new Sprite();
    spritePtr->setTexture( tex );
    addObject( spritePtr );
    return spritePtr;
}

SDL_Surface* WindowWithOpenGL::createSurface(
    const Path& path )
{
    if( false == path.exists() )
    {
        const std::string msg =
            "File " +
            path.getPath() +
            " does not exist.";
        CUL::Assert::simple( false, msg.c_str() );
    }

    SDL_Surface* result = nullptr;
    if( ".bmp" == path.getExtension() )
    {
        result = SDL_LoadBMP( path.getPath().c_str() );
    }

    if( ".png" == path.getExtension() )
    {
        result = IMG_Load( path.getPath().c_str() );
    }
    CUL::Assert::simple(
        nullptr != result,
        "Result is nullptr." );
    return result;
}

ITexture* WindowWithOpenGL::createTexture(
    SDL_Surface* surface,
    const Path& path )
{
    CUL::Assert::simple( this->m_renderer, "RENDERER NOT READY!\n" );
    auto texSDL = new TextureSDL();

    auto tex = SDL_CreateTextureFromSurface(
        this->m_renderer,
        surface );
    CUL::Assert::simple(
        tex,
        "Cannot create texture from " +
        path.getPath() +
        " does not exist." );

    texSDL->setTexture( tex, path );
    this->m_textures[path.getPath()] = std::unique_ptr<ITexture>( texSDL );
    return texSDL;
}

void WindowWithOpenGL::addObject( IObject* object )
{
    std::lock_guard<std::mutex> objectsMutexGuard( this->m_objectsMtx );
    this->m_objects.insert( object );
}

void WindowWithOpenGL::removeObject( IObject* object )
{
    std::lock_guard<std::mutex> objectsMutexGuard( this->m_objectsMtx );
    this->m_objects.erase( object );
}

CDbl WindowWithOpenGL::getFpsAverage()
{
    return this->m_fpsCounter->getAverageFps();
}

void WindowWithOpenGL::setAverageFpsSampleSize( SmallCount sampleSize )
{
    this->m_fpsCounter->setSampleSize( sampleSize );
}

CDbl WindowWithOpenGL::getFpsLast()
{
    return this->m_fpsCounter->getCurrentFps();
}

const ColorS WindowWithOpenGL::getBackgroundColor()const
{
    return this->m_backgroundColor;
}