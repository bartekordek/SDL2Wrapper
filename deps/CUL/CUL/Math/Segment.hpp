#pragma once
#include "CUL/Math/MultiPointFactory.hpp"
namespace CUL
{
	namespace Math
	{
		template <typename Type>
		class Segment
		{
		public:
			explicit Segment()
			{
			}

			virtual ~Segment()
			{
			}

			void setAxisCount( const unsigned int axesCount )
			{
				this->start.setAxisCount( axesCount );
				this->end.setAxisCount( axesCount );
			}

			void setLength( const Type newLength )
			{
				const Type oldLength = getLength();
				if( static_cast<int>( oldLength ) == 0 )
				{
					setLengthOnlyOnFirstAxis( newLength );
					return;
				}
				const Type newLengthToOldLengthProportion = newLength / oldLength;
				MultiPoint<Type>& end = this->end;
				MultiPoint<Type>& start = this->start;
				const MultiPoint<Type> relativeDistance = end.relativeDistance( start );

				for( unsigned int axisIndex = 0; axisIndex < end.getAxisCount(); ++axisIndex )
				{
					const Type oldStartAxisValue = start.getValue( axisIndex );
					const Type oldEndAxisValue = end.getValue( axisIndex );
					auto oldRelativeDistancePerAxis = relativeDistance.getValue( axisIndex );
					auto newDistance = oldRelativeDistancePerAxis * newLengthToOldLengthProportion;

					if( oldStartAxisValue < oldEndAxisValue )
					{
						end.setValue( axisIndex, start.getValue( axisIndex ) + newDistance );
					}
					else
					{
						end.setValue( axisIndex, start.getValue( axisIndex ) - newDistance );
					}
				}
			}

			const Type getLength()const
			{
				return this->start.distance( end );
			}

			void setStart( const MultiPoint<Type>& start )
			{
				this->start = start;
				if( startAndEndHasTheSameAxisCount() )
				{
					sortBeginingAndStart();
				}
			}

			void setEnd( const MultiPoint<Type>& end )
			{
				this->end = end;
				if( startAndEndHasTheSameAxisCount() )
				{
					sortBeginingAndStart();
				}
			}

		private:
			void setLengthOnlyOnFirstAxis( const Type newLength )
			{
				if( start.getAxesCount() > 0 && startAndEndHasTheSameAxisCount() )
				{
					auto startXpos = this->start.getValue( Axis::X );
					this->end.setValue( Axis::X, newLength );
				}
			}

			const bool startAndEndHasTheSameAxisCount()const
			{
				if( start.getAxisCount() == end.getAxisCount() )
				{
					return true;
				}
				return false;
			}
			void sortBeginingAndStart()
			{
				if( start.distanceToZeroZero() > end.distanceToZeroZero() )
				{
					std::swap( this->start, this->end );
				}
			}

			MultiPoint<Type> start;
			MultiPoint<Type> end;
		};
	}
}