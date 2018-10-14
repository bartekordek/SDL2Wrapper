#include "Sprite.hpp"
#include "SDL2Wrapper/IMPORT_SDL.hpp"
#include "CUL/IMPORT_boost_asset.hpp"
#include "TextureSDL.hpp"

using namespace SDL2W;

Sprite::Sprite()
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
    this->m_textureRealSize = inputTexture->getSize();
    this->m_textureRealSize.setZ( 1.0 );
    calculateSpriteAbsoluteSize();
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
    return this->m_textureRealSize;
}

const CUL::Math::Vector3Dd& Sprite::getSizeAbs()const
{
    return this->m_absoluteSize;
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
    calculateSpriteAbsoluteSize();
}

void Sprite::calculatePositionOffset()
{
    this->positionWithOffset = this->position - this->m_pivotAbsolute;
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

void Sprite::setPivot( 
    const double px, 
    const double py, 
    const double pz,
    const PivotType type )
{
    if( PivotType::ABSOLUTE == type )
    {
        this->m_pivotAbsolute.setXYZ( px, py, pz );
        this->m_pivotNormalised = this->m_pivotAbsolute / this->m_textureRealSize;
    }
    else
    {
        this->m_pivotNormalised.setXYZ( px, py, pz );
        this->m_pivotAbsolute = this->m_textureRealSize * this->m_pivotNormalised;
    }
}

void Sprite::setPivotX( const double val, const PivotType type )
{
    if( PivotType::ABSOLUTE == type )
    {
        this->m_pivotAbsolute.setX( val );
        this->calculatePivotNormalised();
    }
    else
    {
        this->m_pivotNormalised.setX( val );
        this->calculatePivotAbsolute();
    }
}

void Sprite::setPivotY( const double val, const PivotType type )
{
    if( PivotType::ABSOLUTE == type )
    {
        this->m_pivotAbsolute.setY( val );
        this->calculatePivotNormalised();
    }
    else
    {
        this->m_pivotNormalised.setY( val );
        this->calculatePivotAbsolute();
    }
}

void Sprite::setPivotZ( const double val, const PivotType type )
{
    if( PivotType::ABSOLUTE == type )
    {
        this->m_pivotAbsolute.setZ( val );
        this->calculatePivotNormalised();
    }
    else
    {
        this->m_pivotNormalised.setZ( val );
        this->calculatePivotAbsolute();
    }
}

const Vector3Dd& Sprite::getPivot( const PivotType type )const
{
    if( PivotType::ABSOLUTE == type )
    {
        return this->m_pivotAbsolute;
    }
    return this->m_pivotNormalised;
}

void Sprite::calculateSpriteAbsoluteSize()
{
    this->m_absoluteSize = this->m_textureRealSize * this->scale;
    calculatePivotAbsolute();
}

void Sprite::calculatePivotAbsolute()
{
    this->m_pivotAbsolute = m_pivotNormalised * m_absoluteSize;
}

void Sprite::calculatePivotNormalised()
{
    this->m_pivotNormalised = this->m_pivotAbsolute / this->m_absoluteSize;
}

