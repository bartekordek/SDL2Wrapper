#pragma once
#include "CUL/Math/Epsilon.hpp"

namespace CUL
{
	namespace Math
	{
		template <typename Type>
		class Vector3D: public Epsilon<Type>
		{
		public:
			Vector3D() = default;
			Vector3D( const Type xVal, const Type yVal, const Type zVal ):
				x(xVal), 
				y(yVal),
				z(zVal)
			{
			}

			Vector3D( const Vector3D<Type>& vector ) = default;

			virtual ~Vector3D() = default;

			const Type getX()const
			{
				return this->x;
			}

			const Type getY()const
			{
				return this->y;
			}

			const Type getZ()const
			{
				return this->z;
			}

			void setX( const Type xValue )
			{
				this->x = xValue;
			}

			void setY( const Type yValue )
			{
				this->y = yValue;
			}

			void setZ( const Type zValue )
			{
				this->z = zValue;
			}

			void setXYZ( const Type xVal, const Type yVal, const Type zVal )
			{
				this->x = xVal;
				this->y = yVal;
				this->z = zVal;
			}

			void setXYZ( const Vector3D& object )
			{
				this->x = object.x;
				this->y = object.y;
				this->z = object.z;
			}

			const bool operator==( const Vector3D& ivector )const
			{
				if( 
					Epsilon<Type>::equals( this->x, ivector.x ) &&
					Epsilon<Type>::equals( this->y, ivector.y ) &&
					Epsilon<Type>::equals( this->z, ivector.z ) )
				{
					return true;
				}
				return false;
			}

			Vector3D<Type> operator*( const Vector3D<Type>& t )const
			{
				Vector3D<Type> result;
				result.x = this->x * t.x;
				result.y = this->y * t.y;
				result.z = this->z * t.z;
				return result;
			}

			Vector3D<Type>& operator*=( const Vector3D<Type>& t )
			{
				this->x = this->x * t.x;
				this->y = this->y * t.y;
				this->z = this->z * t.z;
				return *this;
			}

			Vector3D<Type> operator*( const Type& t )const
			{
				Vector3D<Type> result;
				result.x = this->x * t;
				result.y = this->y * t;
				result.z = this->z * t;
				return result;
			}

			Vector3D<Type>& operator*=( const Type& t )
			{
				this->x = this->x * t;
				this->y = this->y * t;
				this->z = this->z * t;
				return *this;
			}

			Vector3D<Type>& operator+=( const Vector3D<Type>& right )
			{
				this->x += right.x;
				this->y += right.y;
				this->z += right.z;
				return *this;
			}

			Vector3D<Type>& operator=( const Vector3D<Type>& right )
			{
				if( this != &right )
				{
					this->x = right.x;
					this->y = right.y;
					this->z = right.z;
				}
				return *this;
			}

			const Type dotProdcut( const Vector3D<Type>& right )const
			{
				const Type xx = this->x * right.x;
				const Type yy = this->y * right.y;
				const Type zz = this->z * right.z;
				return xx * yy * zz;
			}

			const Vector3D<Type> crossProducti( const Vector3D<Type>& right )const
			{
				const auto& v1 = *this;
				const auto& v2 = right;

				const Type cx = v1.y * v2.z - v1.z * v2.y;
				const Type cy = v1.z * v2.x - v1.x * v2.z;
				const Type cz = v1.x * v2.y - v1.y * v2.x;
				return Vector3D<Type>( cx, cy, cz );
			}

		protected:
			Type x = static_cast<Type>( 0 );
			Type y = static_cast<Type>( 0 );
			Type z = static_cast<Type>( 0 );
		};

		using Vector3Dd = Vector3D<double>;
		using Vector3Di = Vector3D<int>;
		using Vector3Du = Vector3D<unsigned>;
	}
}
