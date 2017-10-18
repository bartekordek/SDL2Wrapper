#include "Sprite.hpp"
#include <SDL.h>
#include <boost/assert.hpp>
#include "TextureWrapper.hpp"

using namespace SDL2W;

Sprite::Sprite()
{
}

Sprite::~Sprite()
{
}

const SDL_Texture* Sprite::getTexture()const
{
	return this->texture->getTexture();
}

void Sprite::setTexture( SDL_Texture* inputTexture )
{
	std::lock_guard<std::mutex> lock( this->mtx );
	this->texture.reset( new TextureWrapper() );
	this->texture->setTexture( inputTexture );
	int w, h;
	const auto sdlQuerySuccess = SDL_QueryTexture( 
		inputTexture, 
		nullptr, 
		nullptr, 
		&w, 
		&h );
	BOOST_ASSERT_MSG( 
		0 == sdlQuerySuccess, 
		"Cannot initialize SDL subsystem" );
	
	this->size.setXYZ( w, h, 0 );
	calculateSizes();
}

const IObject::Type Sprite::getType()const
{
	return IObject::Type::SPRITE;
}

const CUL::Math::Vector3Di& Sprite::getPosition()const
{
	std::lock_guard<std::mutex> lock( this->mtx );
	return this->position;
}

const CUL::Math::Vector3Du& Sprite::getSize()const
{
	std::lock_guard<std::mutex> lock( this->mtx );
	return this->size;
}

const CUL::Math::Vector3Du& Sprite::getSizeAbs()const
{
	std::lock_guard<std::mutex> lock( this->mtx );
	return this->realSize;
}

void Sprite::setPosition( const CUL::Math::Vector3Di& newPosition )
{
	std::lock_guard<std::mutex> lock( this->mtx );
	this->position = newPosition;
}

void Sprite::move( const CUL::Math::Vector3Di& moveVect )
{
	std::lock_guard<std::mutex> lock( this->mtx );
	this->position += moveVect;
}

void Sprite::setScale( const CUL::Math::Vector3Dd& scnewScale )
{
	std::lock_guard<std::mutex> lock( this->mtx );
	this->scale = scnewScale;
	calculateSizes();
}

void Sprite::calculateSizes()
{
	this->realSize = this->size * this->scale;
}