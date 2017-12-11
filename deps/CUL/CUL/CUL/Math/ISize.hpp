#pragma once

namespace CUL
{
	namespace Math
	{
		template <typename Type>
		class ISize
		{
		public:
			ISize()
			{
			}

			virtual ~ISize()
			{
			}

			virtual void setWidth(const Type width) = 0;
			virtual void setHeight(const Type height) = 0;
			virtual void setDepth(const Type depth) = 0;
			void setSize(const ISize& size)
			{
				setWidth(size.getWidth());
				setHeight(size.getHeight());
				setDepth(size.getDepth());
			}
			void setSize(const Type width, const Type height, const Type depth)
			{
				setWidth(width);
				setHeight(height);
				setDepth(depth);
			}

			virtual const Type getWidth()const = 0;
			virtual const Type getHeight()const = 0;
			virtual const Type getDepth()const = 0;

		protected:
		private:
		};
	}
}