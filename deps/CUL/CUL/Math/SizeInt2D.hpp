#pragma once
#include "ISize.hpp"
namespace CUL
{
    namespace Math
    {
        class SizeInt2D: public ISize<int>
        {
        public:
            SizeInt2D() = default;
            SizeInt2D( const SizeInt2D &right ) = default;
            SizeInt2D( const int width, const int height ): width( width ), height( height )
            {
            }
            virtual ~SizeInt2D() = default;
            SizeInt2D& operator=( const SizeInt2D& right ) = default;
            const int getWidth()const override
            {
                return this->width;
            }
            const int getHeight()const override
            {
                return this->height;
            }
            const int getDepth()const override
            {
                return 0;
            }
            void setWidth( const int width )override
            {
                this->width = width;
            }
            void setHeight( const int height )override
            {
                this->height = height;
            }
            void setDepth( const int depth )override
            {
            }
        protected:
        private:
            int width = 0;
            int height = 0;
        };
    }
}