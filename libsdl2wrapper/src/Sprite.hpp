#pragma once
#include "SDL2Wrapper/IObject.hpp"
#include "CUL/IPivotObserver.hpp"
#include <memory>
#include <mutex>
struct SDL_Texture;

namespace SDL2W
{
    class TextureWrapper;
    class Sprite : public IObject, private CUL::IPivotObserver
    {
    public:
        Sprite();
        virtual ~Sprite();

        const SDL_Texture* getTexture()const;
        void setTexture( SDL_Texture* texutre );
        const Type getType()const override;

        const CUL::Math::Vector3Di& getPosition()const override;
        const CUL::Math::Vector3Du& getSize()const override;
        const CUL::Math::Vector3Du& getSizeAbs()const override;

        void setPosition( const CUL::Math::Vector3Di& newPosition ) override;
        void move( const CUL::Math::Vector3Di& moveVect ) override;
        void setScale( const CUL::Math::Vector3Dd& scale ) override;

        // TODO: Not yet implemented.
        const CUL::IPivot* getPivot()const override;

        void pivotHasBeenChanged() override;

    protected:
    private:
        void calculateSizes();

        mutable std::mutex mtx;
        std::shared_ptr<TextureWrapper> texture;
        CUL::Math::Vector3Di position;
        CUL::Math::Vector3Di positionWithOffset;
        CUL::Math::Vector3Du size;
        CUL::Math::Vector3Du realSize;
        CUL::Math::Vector3Dd scale = CUL::Math::Vector3Dd( 1.0, 1.0, 0.0 );

        std::unique_ptr<CUL::IPivot> m_pivot;

    };
}