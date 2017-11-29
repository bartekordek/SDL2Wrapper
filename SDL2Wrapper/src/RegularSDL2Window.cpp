#include "RegularSDL2Window.hpp"
#include "Sprite.hpp"

#include "CUL/ListFactory.hpp"

#include <SDL.h>
#include <SDL_video.h>

#include <boost/assert.hpp>

using namespace SDL2W;
using namespace CUL;

RegularSDL2Window::RegularSDL2Window( 
	const CUL::XYPosition<int>& pos,
	const CUL::Size<unsigned>& size,
	const std::string& name ): IWindow( pos, size, name )
{
	this->window.reset(
		SDL_CreateWindow(
			this->getName().c_str(),
			static_cast<int>( this->getPos().x ),
			static_cast<int>( this->getPos().y ),
			static_cast<int>( this->getSize().GetWidth() ),
			static_cast<int>( this->getSize().GetWidth() ),
			SDL_WINDOW_SHOWN ), RegularSDL2Window::windowDeleter );

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
	std::shared_ptr<IObject> result;
	if(IObject::Type::SPRITE == type)
	{
		SDL_Surface* surface = createSurface( objPath );
		auto tex = SDL_CreateTextureFromSurface( this->renderer.get(), surface );
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
#endif

void RegularSDL2Window::renderNext()
{
	objects->getRandomIteratorPtr()->hasNext();
	auto obj = objects->getRandomIteratorPtr()->next();
	if( IObject::Type::SPRITE == obj->getType() )
	{
		auto tex = static_cast<Sprite*>( obj.get() );

		/*SDL_RenderCopy( 
			this->renderer.get(), 
			const_cast<SDL_Texture*>( tex->getTexture() ), 
			srcRect.get(), &renderQuad );*/
	}

	/*auto sdlTexture = static_cast<const TextureSDL*>(&texture);
	SDL_Rect renderQuad;
	renderQuad.x = static_cast<int>(position.getX());
	renderQuad.y = static_cast<int>(position.getY());
	renderQuad.w = static_cast<int>(targetSize.getX());
	renderQuad.h = static_cast<int>(targetSize.getY());
	std::unique_ptr<SDL_Rect> srcRect;
	*/
}

void RegularSDL2Window::refreshScreen()
{
	SDL_RenderPresent( this->renderer.get() );
}

void RegularSDL2Window::renderAllObjects()
{
	auto& iterator = this->objects->getRandomIterator();
	while( iterator.hasNext() )
	{
		auto& object = iterator.next();
		if( IObject::Type::SPRITE == object->getType() )
		{
			auto* sprite = static_cast<Sprite*>( object.get() );
			auto& pos = object->getPosition();
			auto& size = object->getSizeAbs();

			SDL_Rect renderQuad;
			renderQuad.x = static_cast<int>( pos.getX() );
			renderQuad.y = static_cast<int>( pos.getY() );
			renderQuad.w = static_cast<int>( size.getX() );
			renderQuad.h = static_cast<int>( size.getY() );
			std::unique_ptr<SDL_Rect> srcRect;
			auto tex = const_cast<SDL_Texture*>( sprite->getTexture() );
			SDL_RenderCopy( 
				this->renderer.get(), 
				tex, 
				srcRect.get(), 
				&renderQuad );
		}
	}
}

void RegularSDL2Window::clear()
{
	SDL_RenderClear( this->renderer.get() );
}

#ifdef _MSC_VER
__pragma( warning( pop ) )
#endif