#pragma once

#include "SDL2Wrapper/ISprite.hpp"
#include "CUL/Graphics/ITexture.hpp"
#include "CUL/Math/IPivotObserver.hpp"
#include "CUL/Math/Angle.hpp"
#include "CUL/STL_IMPORTS/STD_memory.hpp"
#include "CUL/STL_IMPORTS/STD_mutex.hpp"

NAMESPACE_BEGIN( SDL2W )

using PivotType = CUL::Math::IPivot::PivotType;
using Vector3Dd = CUL::Math::Vector3Dd;

using RT = CUL::Math::RotationType;
using CRT = const RT;

using CDbl = CUL::Graphics::CDbl;

using Position3DDMutexed = CUL::Graphics::Position3DDMutexed;

class Sprite final:
    public ISprite
{
public:
    Sprite();
    ~Sprite();

    ITexture* getTexture() override;
    void setTexture( ITexture* texutre ) override;
    const Type getType()const override;

    const Position3DDMutexed& getPosition()const override;
    const Position3DDMutexed& getRenderPosition()const override;
    const Position3DDMutexed& getSizeReal()const override;
    const Position3DDMutexed& getSizeAbs()const override;

    void setPosition( const Position3DDMutexed& newPosition ) override;
    void setX( CDbl val ) override;
    void setY( CDbl val ) override;
    void setZ( CDbl val ) override;
    void move( const Position3DDMutexed& moveVect ) override;

    const Position3DDMutexed& getScale()const override;
    void setScale( const Vector3Dd& scale ) override;

    void rotate(
        const CUL::Math::Angle& angle,
        CRT = RT::YAW ) override;
    const CUL::Math::Angle& getAngle(
        CRT = RT::YAW )const override;

    void setPivot( const double px, const double py, const double pz, const PivotType type = PivotType::NORMALIZED ) override;
    void setPivotX( CDbl val, const PivotType type = PivotType::NORMALIZED ) override;
    void setPivotY( CDbl val, const PivotType type = PivotType::NORMALIZED ) override;
    void setPivotZ( CDbl val, const PivotType type = PivotType::NORMALIZED ) override;

    const Position3DDMutexed& getPivot( const PivotType type = PivotType::NORMALIZED )const override;

protected:
private:
    void calculatePositionOffset();
    void calculatePivotAbsolute();
    void calculatePivotNormalised();
    void calculateSpriteAbsoluteSize();

    ITexture* m_texture = nullptr;
    Position3DDMutexed position;
    Position3DDMutexed positionWithOffset;
    Position3DDMutexed m_textureRealSize;
    Position3DDMutexed m_absoluteSize;
    Position3DDMutexed scale = Position3DDMutexed( 1.0, 1.0, 0.0 );
    Position3DDMutexed m_pivotNormalised = Position3DDMutexed( 0.5, 0.5, 0.5 );
    Position3DDMutexed m_pivotAbsolute = Position3DDMutexed( 0.5, 0.5, 0.5 );
    CUL::Math::Angle yaw = 0.0;

};

NAMESPACE_END( SDL2W )