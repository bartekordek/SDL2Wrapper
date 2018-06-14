#pragma once
#include "SDL2Wrapper.hpp"
#include "CUL/Math/Vector3D.hpp"
#include "CUL/Math/IPivot.hpp"
#include "CUL/Math/IAngle.hpp"
namespace SDL2W
{
    using IPivot = CUL::Math::IPivot;
    using IAngle = CUL::Math::IAngle;
    class SDL2WrapperAPI IObject:
        public IPivot
    {
    public:
        enum class Type
        {
            SPRITE = 0
        };

        enum class RotationType
        {
            YAW,
            PITCH,
            ROLL
        };

        virtual void setPosition( const CUL::Math::Vector3Di& newPosition ) = 0;
        virtual void setX( const double val ) = 0;
        virtual void setY( const double val ) = 0;
        virtual void setZ( const double val ) = 0;
        virtual void move( const CUL::Math::Vector3Di& moveVect ) = 0;

        virtual const CUL::Math::Vector3Dd& getScale()const = 0;
        virtual void setScale( const CUL::Math::Vector3Dd& scale ) = 0;

        virtual const CUL::Math::Vector3Dd& getPosition()const = 0;
        virtual const CUL::Math::Vector3Dd& getRenderPosition()const = 0;
        virtual const CUL::Math::Vector3Dd& getSizeReal()const = 0;
        virtual const CUL::Math::Vector3Dd& getSizeAbs()const = 0;

        virtual const Type getType()const = 0;
        virtual const bool operator==( const IObject& right )const;

        virtual void rotate(
            const IAngle& angle,
            const RotationType = RotationType::YAW ) = 0;
        virtual const CUL::Math::IAngle& getAngle( 
            const RotationType = RotationType::YAW )const = 0;

    protected:
    private:
    };
}