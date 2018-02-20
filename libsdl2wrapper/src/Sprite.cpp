#include "Sprite.hpp"
#include <SDL.h>
#include <boost/assert.hpp>
#include "TextureSDL.hpp"

using namespace SDL2W;

Sprite::Sprite():
    m_pivot( new IPivot( this ) )
{
}

Sprite::~Sprite()
{
}

ITexture* Sprite::getTexture()
{
    return this->m_texture;
}

void Sprite::setTexture( ITexture* inputTexture )
{
    this->m_texture = const_cast< ITexture* >( inputTexture );
    this->size = inputTexture->getSize();
    calculateSizes();
}

const IObject::Type Sprite::getType()const
{
    return IObject::Type::SPRITE;
}

    const CUL::Math::Vector3Dd& Sprite::getPosition()const
{
    return this->position;
}

const CUL::Math::Vector3Dd& Sprite::getRenderPosition()const
{
    return this->positionWithOffset;
}

const CUL::Math::Vector3Dd& Sprite::getSizeReal()const
{
    return this->size;
}

const CUL::Math::Vector3Dd& Sprite::getSizeAbs()const
{
    return this->realSize;
}

void Sprite::setPosition( const CUL::Math::Vector3Di& newPosition )
{
    this->position = newPosition;
    calculatePositionOffset();
}

void Sprite::setX( const double val )
{
    this->position.setX( val );
    calculatePositionOffset();
}

void Sprite::setY( const double val )
{
    this->position.setY( val );
    calculatePositionOffset();
}

void Sprite::setZ( const double val )
{
    this->position.setZ( val );
    calculatePositionOffset();
}

void Sprite::move( const CUL::Math::Vector3Di& moveVect )
{
    this->position += moveVect;
    calculatePositionOffset();
}

const CUL::Math::Vector3Dd& Sprite::getScale()const
{
    return this->scale;
}

void Sprite::setScale( const CUL::Math::Vector3Dd& scnewScale )
{
    this->scale = scnewScale;
    calculateSizes();
}

const IPivot* Sprite::getPivot()const
{
    return this->m_pivot.get();
}

void Sprite::calculateSizes()
{
    this->realSize = this->scale * this->size;
    this->m_pivot->setSizeReal( this->realSize );
}

void Sprite::pivotHasBeenChanged()
{
    calculatePositionOffset();
}

void Sprite::calculatePositionOffset()
{
    this->positionWithOffset = this->position - this->m_pivot->getPivot( IPivot::PivotType::ABSOLUTE );
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