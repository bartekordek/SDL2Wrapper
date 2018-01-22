#include "Sprite.hpp"
#include <SDL.h>
#include <boost/assert.hpp>
#include "TextureWrapper.hpp"

using namespace SDL2W;

Sprite::Sprite():
    m_pivot( static_cast<this> )
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

const CUL::IPivot* Sprite::getPivot()const override
{
    return this->m_pivot;
}

void Sprite::setPivotNorm( const double px, const double py, const double pz ) override
{
    this->m_pNormX = px;
    this->m_pNormY = py;
    this->m_pNormZ = pz;
}

void Sprite::setPivotNormX( const double val ) override
{
    this->m_pNormX = px;
}

void Sprite::setPivotNormY( const double val ) override
{
    this->m_pNormY = py;
}

void Sprite::setPivotNormZ( const double val ) override
{
    this->m_pNormZ = pz;
}

const double Sprite::getNormPivotX()const override
{
    return this->m_pNormX;
}

const double Sprite::getNormPivotY()const override
{
    return this->m_pNormY;
}

const double Sprite::getNormPivotZ()const override
{
    return this->m_pNormZ;
}

void Sprite::setPivotAbs( const double px, const double py, const double pz ) override
{
    
}

void Sprite::setPivotAbsX( const double val ) override
{
}

void Sprite::setPivotAbsY( const double val ) override
{
}

void Sprite::setPivotAbsZ( const double val ) override
{
}

const double Sprite::getAbsPivotX()const override
{
}

const double Sprite::getAbsPivotY()const override
{
}

const double Sprite::getAbsPivotZ()const override
{
    retun 
}

void Sprite::calculateSizes()
{
	const CUL::Math::Vector3Dd sizeAsDouble( 
		this->size.getX(),
		this->size.getY(), 0 );
	const auto realSizeD = sizeAsDouble * this->scale;
	this->realSize.setXYZ(
		static_cast<unsigned>( realSizeD.getX() ),
		static_cast<unsigned>( realSizeD.getY() ),
		0
	);
    calculateAbsolutePivot();
}

void Sprite::calculateAbsolutePivot()
{
    this->m_pAbs = this->m_pNorm * realSize;
}