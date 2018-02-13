#pragma once
#include "SDL2Wrapper/IObject.hpp"
#include "CUL/Math/IPivotObserver.hpp"
#include "CUL/Math/Degree.hpp"
#include <memory>
#include <mutex>
struct SDL_Texture;

namespace SDL2W
{
    class TextureWrapper;
    using IPivotObserver = CUL::Math::IPivotObserver;
    class Sprite final: 
        public IObject, private IPivotObserver
    {
    public:
        Sprite();
        ~Sprite();

        const SDL_Texture* getTexture()const;
        void setTexture( SDL_Texture* texutre );
        const Type getType()const override;

        const CUL::Math::Vector3Dd& getPosition()const override;
        const CUL::Math::Vector3Dd& getSize()const override;
        const CUL::Math::Vector3Dd& getSizeAbs()const override;
        const CUL::Math::Vector3Dd& getRenderPosition()const override;

        void setPosition( const CUL::Math::Vector3Di& newPosition ) override;
        void move( const CUL::Math::Vector3Di& moveVect ) override;
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

        mutable std::mutex mtx;
        std::shared_ptr<TextureWrapper> texture;
        CUL::Math::Vector3Dd position;
        CUL::Math::Vector3Dd positionWithOffset;
        CUL::Math::Vector3Dd size;
        CUL::Math::Vector3Dd realSize;
        CUL::Math::Vector3Dd scale = CUL::Math::Vector3Dd( 1.0, 1.0, 0.0 );

        std::unique_ptr<IPivot> m_pivot;
        CUL::Math::Degree yaw = 0.0;
    };
}