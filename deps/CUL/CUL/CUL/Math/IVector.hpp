#pragma once

#include <MogeLib.hpp>

namespace CUL
{
    namespace Math
    {
	template <typename Type>
	class MogeLib_API IVector
	{
	public:
		IVector()
		{
		}

		virtual ~IVector()
		{
		}

		virtual const Type getXType()const = 0;
		virtual const Type getYType()const = 0;
		virtual const Type getZType()const = 0;

		virtual void setXyz( const Type x, const Type y, const Type z ) = 0;

		virtual void setX( const Type x ) = 0;
		virtual void setY( const Type y ) = 0;
		virtual void setZ( const Type z ) = 0;

		virtual void setX( const unsigned int x ) = 0;
		virtual void setY( const unsigned int y ) = 0;
		virtual void setZ( const unsigned int z ) = 0;

		virtual void setX( const int x ) = 0;
		virtual void setY( const int y ) = 0;
		virtual void setZ( const int z ) = 0;

	protected:
	private:
	};
    }
}