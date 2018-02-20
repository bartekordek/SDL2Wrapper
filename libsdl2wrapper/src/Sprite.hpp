#pragma once
#include "SDL2Wrapper/ISprite.hpp"
#include "SDL2Wrapper/ITexture.hpp"
#include "CUL/Math/IPivotObserver.hpp"
#include "CUL/Math/Degree.hpp"
#include <memory>
#include <mutex>

namespace SDL2W
{
    using IPivotObserver = CUL::Math::IPivotObserver;
    class Sprite final: 
        public ISprite,
        private IPivotObserver
    {
    public:
        Sprite();
        ~Sprite();

        ITexture* getTexture() override;
        void setTexture( ITexture* texutre ) override;
        const Type getType()const override;

        const CUL::Math::Vector3Dd& getPosition()const override;
        const CUL::Math::Vector3Dd& getSizeReal()const override;
        const CUL::Math::Vector3Dd& getSizeAbs()const override;
        const CUL::Math::Vector3Dd& getRenderPosition()const override;

        void setPosition( const CUL::Math::Vector3Di& newPosition ) override;
        void setX( const double val ) override;
        void setY( const double val ) override;
        void setZ( const double val ) override;
        void move( const CUL::Math::Vector3Di& moveVect ) override;

        const CUL::Math::Vector3Dd& getScale()const override;
        void setScale( const CUL::Math::Vector3Dd& scale ) override;

  
        const IPivot* getPivot()const override;
        void pivotHasBeenChanged() override;

        void rotate( const CUL::Math::IAngle& angle, const RotationType = RotationType::YAW );
        const CUL::Math::IAngle& getAngle(
            const RotationType = RotationType::YAW )const;

    protected:
    private:
        void calculateSizes();
        void calculatePositionOffset();

        ITexture* m_texture = nullptr;
        CUL::Math::Vector3Dd position;
        CUL::Math::Vector3Dd positionWithOffset;
        CUL::Math::Vector3Dd size;
        CUL::Math::Vector3Dd realSize;
        CUL::Math::Vector3Dd scale = CUL::Math::Vector3Dd( 1.0, 1.0, 0.0 );

        std::unique_ptr<IPivot> m_pivot;
        CUL::Math::Degree yaw = 0.0;
    };
}