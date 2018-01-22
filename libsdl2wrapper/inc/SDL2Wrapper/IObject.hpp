#pragma once
#include "CUL/Math/Vector3D.hpp"
#include "CUL/IPivot.hpp"
namespace SDL2W
{
	class IObject
	{
	public:
		enum class Type
		{
			SPRITE = 0
		};

		virtual void setPosition( const CUL::Math::Vector3Di& newPosition ) = 0;
		virtual void move( const CUL::Math::Vector3Di& moveVect ) = 0;

		virtual void setScale( const CUL::Math::Vector3Dd& scale ) = 0;

		virtual const CUL::Math::Vector3Di& getPosition()const = 0;
		virtual const CUL::Math::Vector3Du& getSize()const = 0;
		virtual const CUL::Math::Vector3Du& getSizeAbs()const = 0;

		virtual const Type getType()const = 0;
		virtual const bool operator==( const IObject& right )const;
        
        virtual const CUL::IPivot* getPivot()const = 0;
        
	protected:
	private:
	};
}