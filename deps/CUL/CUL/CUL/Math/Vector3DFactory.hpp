#pragma once
#include "CUL/Math/Vector3D.hpp"
namespace CUL
{
	namespace Math
	{
		class MogeLib_API Vector3DFactory
		{
		public:
			static Vector3D<double>* createVectorSimpleDouble( const double x = 0.0, const double y = 0.0, const double z = 0.0 );
			static Vector3D<int>* createVectorSimpleInt( const int x = 0, const int y = 0, const int z = 0 );
			static Vector3D<unsigned int>* createVectorSimpleUInt( const unsigned int x = 0, const unsigned int y = 0, const unsigned int z = 0 );
		};
	}
}