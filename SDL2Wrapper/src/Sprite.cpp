#include "Sprite.hpp"
#include <SDL.h>
#include <SDL_render.h>

using namespace SDL2W;

Sprite::Sprite()
{

}

Sprite::~Sprite()
{
}

const SDL_Texture* Sprite::getTexture()const
{
	return this->texture.get();
}

void Sprite::setTexture( SDL_Texture* inputTexture )
{
	std::lock_guard<std::mutex> lock( this->mtx );
	this->texture.reset( inputTexture, Sprite::deleteTexture);
	int w, h;
	SDL_QueryTexture( inputTexture, nullptr, nullptr, &w, &h );
	this->size.setXYZ( w, h, 0 );
	calculateSizes();
}

void Sprite::deleteTexture( SDL_Texture* texture )
{
	SDL_DestroyTexture( texture );
}

const IObject::Type Sprite::getType()const
{
	return IObject::Type::SPRITE;
}

const CUL::Math::Vector3Di& Sprite::getPosition()const
{
	return this->position;
}

const CUL::Math::Vector3Du& Sprite::getSize()const
{
	return this->size;
}

const CUL::Math::Vector3Du& Sprite::getSizeAbs()const
{
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

void Sprite::setScale( const CUL::Math::Vector3Du& scnewScale )
{
	std::lock_guard<std::mutex> lock( this->mtx );
	this->scale = scnewScale;
	calculateSizes();
}

void Sprite::calculateSizes()
{
	this->realSize = this->size * this->scale;
}