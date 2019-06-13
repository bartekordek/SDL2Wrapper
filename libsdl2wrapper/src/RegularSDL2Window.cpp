#include "RegularSDL2Window.hpp"
#include "TextureSDL.hpp"
#include "Sprite.hpp"
#include "TextureSDL.hpp"

#include "SDL2Wrapper/IMPORT_SDL.hpp"
#include "SDL2Wrapper/IMPORT_SDL_video.hpp"
#include "IMPORT_SDL_image.hpp"

#include "CUL/Filesystem/FS.hpp"

#include "SimpleUtils.hpp"

using namespace SDL2W;

using IPivot = CUL::Math::IPivot;

RegularSDL2Window::RegularSDL2Window(
    const Vector3Di& pos,
    const Vector3Du& size,
    CUL::CnstMyStr& name,
    const bool withOpenGL ):
        m_withOpenGL( withOpenGL ),
        m_position( pos ),
        m_size( size )
{
    m_window = createWindow( pos, size, name, m_withOpenGL );
    Assert( m_window, "The Window has not been initialized." );

    const auto id = SDL_GetWindowID( m_window );
    setWindowID( id );

    m_renderer = SDL_CreateRenderer( m_window, -1, SDL_RENDERER_ACCELERATED );
    setName( name );
}

SDL_Window* RegularSDL2Window::createWindow(
    const Vector3Di& pos,
    const Vector3Du& size,
    CUL::CnstMyStr& nameconst,
    bool opengl )
{
    SDL_Window* result = nullptr;
    Uint32 windowFlags = SDL_WINDOW_SHOWN;
    if( opengl )
    {
        windowFlags |= SDL_WINDOW_OPENGL;
    }
    result = SDL_CreateWindow(
        nameconst.cStr(),
        static_cast< int >( pos.getX() ),
        static_cast< int >( pos.getY() ),
        static_cast< int >( size.getX() ),
        static_cast< int >( size.getY() ),
        windowFlags );
    if( nullptr == result )
    {
        auto sdlError = SDL_GetError();
        CUL::MyString s_sdlError( sdlError );
        logMsg(
            "ERROR" + s_sdlError, CUL::LOG::Severity::CRITICAL );
        Assert( result, "The Window has not been initialized." );
    }

    return result;
}

RegularSDL2Window::~RegularSDL2Window()
{
    logMsg( "RegularSDL2Window::~RegularSDL2Window()" );
    destroyObjects();

    Assert( m_renderer, "The Renderer has been destroyed somwhere else." );
    SDL_DestroyRenderer( m_renderer );
    this->m_renderer = nullptr;

    Assert( m_window, "The Window has been destroyed somwhere else." );
    SDL_DestroyWindow( this->m_window );
    this->m_window = nullptr;
}

void RegularSDL2Window::destroyObjects()
{
    std::lock_guard<std::mutex> objectsMutexGuard( m_objectsMtx );
    m_textures.clear();
}

void RegularSDL2Window::updateScreenBuffers()
{
    if( m_withOpenGL )
    {
        Assert( this->m_window, "The Window is not initialized." );
        SDL_GL_SwapWindow( this->m_window );
        // ^ https://forums.libsdl.org/viewtopic.php?p=52399
    }
    else
    {
        Assert( this->m_renderer, "The Renderer is not initialized." );
        SDL_RenderPresent( this->m_renderer );
    }
    frameHasEnded();
}

void RegularSDL2Window::renderAll()
{
    SDL_SetRenderDrawColor(
        this->m_renderer,
        this->m_backgroundColor.getRUI(),
        this->m_backgroundColor.getGUI(),
        this->m_backgroundColor.getBUI(),
        this->m_backgroundColor.getAUI() );
    std::lock_guard<std::mutex> objectsMutexGuard(this->m_objectsMtx);
    for( auto& object : this->m_objects )
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
                this->m_renderer,
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
    CUL::Assert::simple( this->m_renderer, "The Renderer has been deleted somwhere else." );
    SDL_RenderClear( this->m_renderer );
}

void RegularSDL2Window::setBackgroundColor( const ColorS& color )
{
    this->m_backgroundColor = color;
}

const Vector3Di& RegularSDL2Window::getPos()const
{
    return this->m_position;
}

void RegularSDL2Window::setPos( const Vector3Di& pos )
{
    this->m_position = pos;
}

const Vector3Du& RegularSDL2Window::getSize()const
{
    return this->m_size;
}

void RegularSDL2Window::setSize( const Vector3Du& size )
{
    this->m_size = size;
}

const IWindow::Type RegularSDL2Window::getType() const
{
    return IWindow::Type::SDL_WIN;
}

ISprite* RegularSDL2Window::createSprite( const Path& objPath )
{
    ISprite* result = nullptr;
    CUL::Assert::simple( objPath.getPath() != "", "EMTPY PATH." );
    auto it = this->m_textures.find( objPath.getPath().string() );
    if( this->m_textures.end() == it )
    {
        auto tex = createTexture( objPath );
        result = createSprite( tex );
    }
    else
    {
        logMsg( "ISprite* RegularSDL2Window::createSprite( const Path& objPath )22" );
        auto tex = it->second.get();
        result = createSprite( tex );
    }
    logMsg( "ISprite* RegularSDL2Window::createSprite( const Path& objPath )end" );
    return result;
}

ITexture* RegularSDL2Window::createTexture( const Path& objPath )
{
    logMsg( "ITexture* RegularSDL2Window::createTexture( const Path& objPath )" );
    ITexture* result = nullptr;
    CUL::Assert::simple( objPath.getPath() != "", "EMTPY PATH." );
    auto it = this->m_textures.find( objPath.getPath().string() );
    logMsg( "ITexture* RegularSDL2Window::createTexture( const Path& objPath )1" );
    if( this->m_textures.end() == it )
    {
        logMsg( "ITexture* RegularSDL2Window::createTexture( const Path& objPath )11" );
        auto surface = createSurface( objPath );
        logMsg( "ITexture* RegularSDL2Window::createTexture( const Path& objPath )111" );
        auto tex = createTexture( surface, objPath );
        SDL_FreeSurface( surface );
        surface = nullptr;
        result = tex;
    }
    else
    {
        logMsg( "ITexture* RegularSDL2Window::createTexture( const Path& objPath )12" );
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

SDL_Surface* RegularSDL2Window::createSurface(
    const Path& path )
{
    if( false == path.exists() )
    {
        Assert( false, "File " + path.getPath() + " does not exist." );
    }
    SDL_Surface* result = nullptr;
    if( ".bmp" == path.getExtension() )
    {
        result = SDL_LoadBMP( path.getPath().cStr() );
    }

    if( ".png" == path.getExtension() )
    {
        auto value = path.getPath().cStr();
        const char* chuj = value;
        result = IMG_Load( chuj );
    }
    Assert( result, "Cannot load: " + path.getPath() );
    return result;
}

ITexture* RegularSDL2Window::createTexture(
    SDL_Surface* surface,
    const Path& path )
{
    logMsg( "RegularSDL2Window::createTexture" );
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
    this->m_textures[ path.getPath() ] = std::unique_ptr<ITexture>( texSDL );
    return texSDL;
}

void RegularSDL2Window::addObject( IObject* object )
{
    std::lock_guard<std::mutex> objectsMutexGuard( this->m_objectsMtx );
    this->m_objects.insert( object );
}

void RegularSDL2Window::removeObject( IObject* object )
{
    std::lock_guard<std::mutex> objectsMutexGuard( this->m_objectsMtx );
    this->m_objects.erase( object );
}

SDL_Window* RegularSDL2Window::getSDLWindow() const
{
    return this->m_window;
}

const ColorS RegularSDL2Window::getBackgroundColor()const
{
    return this->m_backgroundColor;
}