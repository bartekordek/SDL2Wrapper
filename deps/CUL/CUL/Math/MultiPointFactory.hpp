#pragma once

#include "MultiPoint.hpp"

namespace CUL
{
	namespace Math
	{
		class MultiPointFactory
		{
		public:
			template <typename Type>
			static MultiPoint<Type> create2d( const Type x, const Type y )
			{
				MultiPoint<Type> result( 2 );
				result.setValue( Axis::X, x );
				result.setValue( Axis::Y, y );
				return result;
			}

			template <typename Type>
			static MultiPoint<Type> create3d( const Type x, const Type y, const Type z )
			{
				MultiPoint<Type> result( 3 );
				result.setValue( Axis::X, x );
				result.setValue( Axis::Y, y );
				result.setValue( Axis::Z, z );
				return result;
			}

		protected:
			void translationUnitIsNotEmpty();
		private:
			MultiPointFactory() 
			{
				translationUnitIsNotEmpty();
			}
			virtual ~MultiPointFactory() {}
		};
	}
}