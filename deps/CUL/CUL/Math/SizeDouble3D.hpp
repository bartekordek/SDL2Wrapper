#pragma once
#include "CUL/Math/ISize.hpp"
namespace CUL
{
	namespace Math
	{
		class SizeDouble3D: public ISize<double>
		{
		public:
			SizeDouble3D() = default;
			virtual ~SizeDouble3D() = default;

			void setWidth( const double width ) override;
			void setHeight( const double height ) override;
			void setDepth( const double depth ) override;

			const double getWidth()const override;
			const double getHeight()const override;
			const double getDepth()const override;

		protected:
		private:
			double width = 0.0;
			double height = 0.0;
			double depth = 0.0;
		};
	}
}