#pragma once

namespace CUL
{
	template <typename Type>
	class Size
	{
	public:
		Size()
		{
		}

		Size( const Type width, const Type height ) : mWidth( width ), mHeight( height )
		{
		}

		Size( const Size& size )
		{
			*this = size;
		}

		~Size()
		{
		}

		Size& operator=( const Size& size )
		{
			if( this != &size )
			{
				mWidth = size.mWidth;
				mHeight = size.mHeight;
			}
			return *this;
		}

		const Type GetWidth()const
		{
			return mWidth;
		}

		const Type GetHeight()const
		{
			return mHeight;
		}

		void SetWidth( const Type width )
		{
			mWidth = width;
		}

		void SetHeight( const Type height )
		{
			mHeight = height;
		}

		void SetWH( const unsigned int width, const unsigned int height )
		{
			mWidth = width;
			mHeight = height;
		}

		void SetWH( const Size& size )
		{
			if( this != &size )
			{
				*this = size;
			}
		}

	protected:
	private:
		Type mWidth = static_cast<Type>(0);
		Type mHeight = static_cast<Type>( 0 );
	};
}