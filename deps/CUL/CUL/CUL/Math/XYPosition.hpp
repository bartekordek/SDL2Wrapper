#pragma once
namespace CUL
{
	template <typename Type>
	struct XYPosition
	{
		XYPosition( const Type x = static_cast<Type>( 0 ), const Type y = static_cast<Type>( 0 ) ):
			x( x ),
			y( y )
		{

		}

		Type x = static_cast<Type>( 0 );
		Type y = static_cast<Type>( 0 );
	};
}