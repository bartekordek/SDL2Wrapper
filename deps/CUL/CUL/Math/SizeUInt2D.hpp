#pragma once
#include "ISize.hpp"
namespace CUL
{
    namespace Math
    {
        class SizeUint2D: public ISize<unsigned int>
        {
        public:
			SizeUint2D() = default;
			SizeUint2D( const SizeUint2D &right ) = default;
			SizeUint2D( const unsigned int width, const unsigned int height ): width( width ), height( height )
            {
            }
            virtual ~SizeUint2D() = default;
			SizeUint2D& operator=( const SizeUint2D& right ) = default;
            const unsigned int getWidth()const override
            {
                return this->width;
            }
            const unsigned int getHeight()const override
            {
                return this->height;
            }
            const unsigned int getDepth()const override
            {
                return 0;
            }
            void setWidth( const unsigned int width )override
            {
                this->width = width;
            }
            void setHeight( const unsigned int height )override
            {
                this->height = height;
            }
            void setDepth( const unsigned int depth )override
            {
            }
        protected:
        private:
            unsigned int width = 0;
            unsigned int height = 0;
        };
    }
}