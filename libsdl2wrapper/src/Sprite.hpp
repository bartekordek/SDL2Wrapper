#pragma once
#include "SDL2Wrapper/IObject.hpp"
#include <memory>
#include <mutex>
struct SDL_Texture;

namespace SDL2W
{
	class TextureWrapper;
	class Sprite : public IObject, private CUL::IPivot
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
        
        void setPivotNorm( const double px, const double py, const double pz ) override;
        void setPivotNormX( const double val ) override;
        void setPivotNormY( const double val ) override;
        void setPivotNormZ( const double val ) override;

        const double getNormPivotX()const override;
        const double getNormPivotY()const override;
        const double getNormPivotZ()const override;

        void setPivotAbs( const double px, const double py, const double pz ) override;
        void setPivotAbsX( const double val ) override;
        void setPivotAbsY( const double val ) override;
        void setPivotAbsZ( const double val ) override;

        const double getAbsPivotX()const override;
        const double getAbsPivotY()const override;
        const double getAbsPivotZ()const override;

	protected:
	private:
		void calculateSizes();
        void calculateAbsolutePivot();

		mutable std::mutex mtx;
		std::shared_ptr<TextureWrapper> texture;
		CUL::Math::Vector3Di position;
		CUL::Math::Vector3Du size;
		CUL::Math::Vector3Du realSize;
		CUL::Math::Vector3Dd scale = CUL::Math::Vector3Dd( 1.0, 1.0, 0.0 );
        
        IPivot* m_pivot = nullptr;
        
        CUL::Math::Vector3Du m_pNorm = CUL::Math::Vector3Dd( 0.5, 0.5, 0.5 );
        CUL::Math::Vector3Du m_pAbs = CUL::Math::Vector3Dd( 0.5, 0.5, 0.5 );
	};
}