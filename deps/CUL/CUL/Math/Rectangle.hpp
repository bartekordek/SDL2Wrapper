#pragma once

#include "Segment.hpp"

namespace CUL
{
	namespace Math
	{
		template <typename Type>
		class Rectangle
		{
		public:
			explicit Rectangle( const unsigned int axesCount, const Segment<Type>& downEdge = Segment<Type>(), const Segment<Type>& leftEdge = Segment<Type>() )
			{
				this->leftEdge.setAxesCount( axesCount );
				this->downEdge.setAxesCount( axesCount );
			}

			virtual ~Rectangle()
			{
			}

			const Type calculateField()const
			{
				return getWidth() * getHeight();
			}

			void setWidth( const Type width )
			{
				downEdge.setLength( width );
			}

			void setHeight( const Type height )
			{
				leftEdge.setLength( height );
			}

			const Type getWidth()const
			{
				return downEdge.getLength();
			}

			const Type getHeight()const
			{
				return leftEdge.getLength();
			}

			void setLeftDownCornerPosition( const MultiPoint<Type>& position )
			{
				leftEdge.setStart( position );
				downEdge.setStart( position );
			}


		protected:
		private:
			Segment<Type> leftEdge;
			Segment<Type> downEdge;
		};
	}
}