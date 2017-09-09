#pragma once
#include "SDL2Wrapper/IObject.hpp"
#include <memory>
#include <mutex>
struct SDL_Texture;
namespace SDL2W
{
	class Sprite : public IObject
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
		void setScale( const CUL::Math::Vector3Du& scale ) override;

	protected:
	private:
		void calculateSizes();

		std::mutex mtx;
		static void deleteTexture( SDL_Texture* texture );
		std::shared_ptr<SDL_Texture> texture;
		CUL::Math::Vector3Di position;
		CUL::Math::Vector3Du size;
		CUL::Math::Vector3Du realSize;
		CUL::Math::Vector3Du scale = CUL::Math::Vector3Du( 1, 1, 0 );
	};
}