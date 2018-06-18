#pragma once

#include "SDL2Wrapper/ISprite.hpp"
#include "SDL2Wrapper/ITexture.hpp"
#include "CUL/Math/IPivotObserver.hpp"
#include "CUL/Math/Degree.hpp"
#include "CUL/STD_memory.hpp"
#include "CUL/STD_mutex.hpp"

namespace SDL2W
{
    using PivotType = CUL::Math::IPivot::PivotType;
    using Vector3Dd = CUL::Math::Vector3Dd;
    class Sprite final: 
        public ISprite
    {
    public:
        Sprite();
        ~Sprite();

        ITexture* getTexture() override;
        void setTexture( ITexture* texutre ) override;
        const Type getType()const override;

        const Vector3Dd& getPosition()const override;
        const Vector3Dd& getSizeReal()const override;
        const Vector3Dd& getSizeAbs()const override;
        const Vector3Dd& getRenderPosition()const override;

        void setPosition( const CUL::Math::Vector3Di& newPosition ) override;
        void setX( const double val ) override;
        void setY( const double val ) override;
        void setZ( const double val ) override;
        void move( const CUL::Math::Vector3Di& moveVect ) override;

        const Vector3Dd& getScale()const override;
        void setScale( const Vector3Dd& scale ) override;

        void rotate( const CUL::Math::IAngle& angle, const RotationType = RotationType::YAW );
        const CUL::Math::IAngle& getAngle(
            const RotationType = RotationType::YAW )const;

        void setPivot( const double px, const double py, const double pz, const PivotType type = PivotType::NORMALIZED ) override;
        void setPivotX( const double val, const PivotType type = PivotType::NORMALIZED ) override;
        void setPivotY( const double val, const PivotType type = PivotType::NORMALIZED ) override;
        void setPivotZ( const double val, const PivotType type = PivotType::NORMALIZED ) override;

        const Vector3Dd& getPivot( const PivotType type = PivotType::NORMALIZED )const override;

    protected:
    private:
        void calculatePositionOffset();
        void calculatePivotAbsolute();
        void calculatePivotNormalised();
        void calculateSpriteAbsoluteSize();

        ITexture* m_texture = nullptr;
        Vector3Dd position;
        Vector3Dd positionWithOffset;
        Vector3Dd m_textureRealSize;
        Vector3Dd m_absoluteSize;
        Vector3Dd scale = Vector3Dd( 1.0, 1.0, 0.0 );
        Vector3Dd m_pivotNormalised = Vector3Dd( 0.5, 0.5, 0.5 );
        Vector3Dd m_pivotAbsolute = Vector3Dd( 0.5, 0.5, 0.5 );
        CUL::Math::Degree yaw = 0.0;
    };
}