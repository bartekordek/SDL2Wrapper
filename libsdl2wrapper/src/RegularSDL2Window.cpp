#include "RegularSDL2Window.hpp"
#include "Sprite.hpp"

#include "CUL/ListFactory.hpp"
#include "CUL/FS.hpp"

#include <SDL.h>
#include <SDL_video.h>

#define BOOST_CONFIG_SUPPRESS_OUTDATED_MESSAGE
#include <boost/assert.hpp>

using namespace SDL2W;
using namespace CUL;

RegularSDL2Window::RegularSDL2Window( 
    const CUL::Math::Vector3Di& pos,
    const CUL::Math::Vector3Du& size,
    const std::string& name ): IWindow( pos, size, name )
{

    auto windowFlags = SDL_WINDOW_SHOWN;
    this->window.reset(
        SDL_CreateWindow(
            this->getName().c_str(),
            static_cast<int>( this->getPos().getX() ),
            static_cast<int>( this->getPos().getY() ),
            static_cast<int>( this->getSize().getX() ),
            static_cast<int>( this->getSize().getY() ),
            windowFlags ), RegularSDL2Window::windowDeleter );

    this->renderer.reset(
        SDL_CreateRenderer( this->window.get(), -1, SDL_RENDERER_ACCELERATED ), RegularSDL2Window::rendererDeleter );

    this->objects.reset( ListFactory::createVectorListPtr<std::shared_ptr<IObject>>() );
}

RegularSDL2Window::RegularSDL2Window( const RegularSDL2Window& win ):
    IWindow( win.getPos(), win.getSize(), win.getName() ),
    window( win.window ),
    renderer( win.renderer ),
    objects( win.objects )
{
}

RegularSDL2Window::~RegularSDL2Window()
{
}

RegularSDL2Window& RegularSDL2Window::operator=( const RegularSDL2Window& right )
{
    if( this != & right)
    {
        this->setPos( right.getPos() );
        this->setSize( right.getSize() );
        this->setName( right.getName() );
        this->window = right.window;
        this->renderer = right.renderer;
    }
    return *this;
}

void RegularSDL2Window::windowDeleter( SDL_Window* win )
{
    SDL_DestroyWindow( win );
}

void RegularSDL2Window::rendererDeleter( SDL_Renderer* rend )
{
    SDL_DestroyRenderer( rend );
}

std::shared_ptr<IObject> RegularSDL2Window::createObject(
    const CUL::FS::Path& objPath,
    const IObject::Type type ) const
{
    auto cwd = CUL::FS::FSApi::getCurrentDir();
    bool pathExist = objPath.exists();
    if( false == pathExist )
    {
        const std::string msg = "File " + objPath.getPath() + " does not exist.";
        BOOST_ASSERT_MSG( false, msg.c_str() );
    }
    
    std::shared_ptr<IObject> result;
    auto rendererPtr = this->renderer.get();
    if( rendererPtr && IObject::Type::SPRITE == type )
    {
        SDL_Surface* surface = createSurface( objPath );
        auto tex = SDL_CreateTextureFromSurface( rendererPtr, surface );
        auto sprite = new Sprite();
        sprite->setTexture( tex );
        result.reset( sprite );

    }
    this->objects->pushBack( result );
    return result;
}

SDL_Surface* RegularSDL2Window::createSurface( const CUL::FS::Path& path )
{
    SDL_Surface* result = nullptr;
    if( ".bmp" == path.getExtension() )
    {
        result = SDL_LoadBMP( path.getPath().c_str() );
    }

    if( ".png" == path.getExtension() )
    {
        //TODO result = SDL_Load
    }
    BOOST_ASSERT( result != nullptr );
    return result;
}
#ifdef _MSC_VER
__pragma( warning( push ) ) \
__pragma( warning( disable:4189 ) )
__pragma( warning( disable:4100 ) )
#endif

void RegularSDL2Window::renderNext()
{
    objects->getRandomIteratorPtr()->hasNext();
    auto obj = objects->getRandomIteratorPtr()->next();
    if( IObject::Type::SPRITE == obj->getType() )
    {
        auto tex = static_cast<Sprite*>( obj.get() );
    }
}

void RegularSDL2Window::refreshScreen()
{
    SDL_RenderPresent( this->renderer.get() );
}

void RegularSDL2Window::renderAllObjects()
{
    SDL_SetRenderDrawColor( 
        this->renderer.get(), 
        this->m_backgroundColor.r,
        this->m_backgroundColor.g,
        this->m_backgroundColor.b,
        this->m_backgroundColor.alpha );

    auto& iterator = this->objects->getRandomIterator();
    while( iterator.hasNext() )
    {
        auto& object = iterator.next();
        if( IObject::Type::SPRITE == object->getType() )
        {
            auto* sprite = static_cast<Sprite*>( object.get() );
            auto& pos = object->getRenderPosition();
            auto& size = object->getSizeAbs();
            auto pivot = object->getPivot()->getPivot( IPivot::PivotType::ABSOLUTE );

            SDL_Rect renderQuad;
            renderQuad.x = static_cast<int>( pos.getX() );
            renderQuad.y = static_cast<int>( pos.getY() );
            renderQuad.w = static_cast<int>( size.getX() );
            renderQuad.h = static_cast<int>( size.getY() );

            std::unique_ptr<SDL_Rect> srcRect;

            auto tex = const_cast<SDL_Texture*>( sprite->getTexture() );

            const double angle = sprite->getAngle().getValueD();

            SDL_Point center;
            center.x = static_cast<int>( pivot.getX() );
            center.y = static_cast<int>( pivot.getY() );

            auto result = SDL_RenderCopyEx(
                this->renderer.get(), 
                tex, 
                srcRect.get(), 
                &renderQuad,
                angle, &center, SDL_RendererFlip::SDL_FLIP_NONE );
            BOOST_ASSERT_MSG( result == 0, "Cannot render SDL texture..." );
        }
    }
}

void RegularSDL2Window::clear()
{
    SDL_RenderClear( this->renderer.get() );
}

void RegularSDL2Window::setBackgroundColor( const ColorE color )
{
    setBackgroundColor( color );
}

void RegularSDL2Window::setBackgroundColor( const ColorS& color )
{
    this->m_backgroundColor = color;
}

#ifdef _MSC_VER
__pragma( warning( pop ) )
#endif