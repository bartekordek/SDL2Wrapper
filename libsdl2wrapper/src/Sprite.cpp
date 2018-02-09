#include "Sprite.hpp"
#include <SDL.h>
#include <boost/assert.hpp>
#include "TextureWrapper.hpp"

using namespace SDL2W;

Sprite::Sprite():
    m_pivot( new IPivot( this ) )
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

const CUL::Math::Vector3Di& Sprite::getRenderPosition()const
{
    std::lock_guard<std::mutex> lock( this->mtx );
    return this->positionWithOffset;
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
    calculatePositionOffset();
}

void Sprite::move( const CUL::Math::Vector3Di& moveVect )
{
    std::lock_guard<std::mutex> lock( this->mtx );
    this->position += moveVect;
    calculatePositionOffset();
}

void Sprite::setScale( const CUL::Math::Vector3Dd& scnewScale )
{
    std::lock_guard<std::mutex> lock( this->mtx );
    this->scale = scnewScale;
    calculateSizes();
}

const IPivot* Sprite::getPivot()const
{
    return this->m_pivot.get();
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
    this->m_pivot->setRealSize( this->realSize );
}

void Sprite::pivotHasBeenChanged()
{
    calculatePositionOffset();
}

void Sprite::calculatePositionOffset()
{
    auto pivotAsInteger = static_cast<CUL::Math::Vector3Di>(
        this->m_pivot->getPivot( IPivot::PivotType::ABSOLUTE ));
    this->positionWithOffset = this->position - pivotAsInteger;
}

void Sprite::rotate(
    const CUL::Math::IAngle& angle,
    const RotationType )
{
    this->yaw = angle;
}

const CUL::Math::IAngle& Sprite::getAngle(
    const RotationType rotationType )const
{
    if( RotationType::YAW == rotationType )
    {
        return this->yaw;
    }
    return this->yaw; // TODO?
}