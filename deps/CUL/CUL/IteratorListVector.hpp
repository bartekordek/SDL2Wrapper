#pragma once
#include "IIterator.hpp"
#include <vector>
namespace CUL
{
	template<typename Type>
	class IteratorListVector: public IIterator<Type>
	{
	public:
		explicit IteratorListVector<Type>( std::vector<Type>& elements ): 
			elements( elements )
		{
		}

		explicit IteratorListVector<Type>( const IteratorListVector<Type>& arg ) :
			elements( arg.elements )
		{
		}

		virtual ~IteratorListVector()
		{
		}

		Type& getVal()override
		{
			return *this->it;
		}

		const Type& getVal()const override
		{
			return *this->it;
		}

		const bool hasNext()const override
		{
			if( this->it == this->elements.end() )
			{
				return false;
			}

			if( this->elements.size() == 1 && this->it == this->elements.begin() )
			{
				return true;
			}

			if( this->it == this->elements.end() )
			{
				return false;
			}
			return true;
		}

		Type& next() override
		{
			return *( this->it++ );
		}

		const bool hasPrevious()const override
		{
			return this->elements.begin() != this->it;
		}

		Type& previous() override
		{
			--this->it;
			return *this->it;
		}

		const bool isEmpty()const override
		{
			return this->elements.empty();
		}

		Type& first() override
		{
			return *this->it;
		}

		Type& last() override
		{
			return *this->it;
		}
		
		const Type& first()const override
		{
			return *this->it;
		}

		const Type& last()const override
		{
			return *this->it;
		}

		IIterator<Type>& operator=( const typename std::vector<Type>::iterator& inIt )
		{
			if( this->it != inIt )
			{
				this->it = inIt;
			}
			return *this;
		}

		IteratorListVector<Type>& operator=( const IteratorListVector<Type>& right )
		{
			if( this != &right )
			{
				this->elements = right.elements;
				this->it = right.it;
			}
			return *this;
		}

		void setIterator( const typename std::vector<Type>::iterator& inIt )
		{
			this->it = inIt;
		}

		Type& operator++() override
		{
			++this->it;
			return *this->it;
		}

		Type operator++( int ) override
		{
			Type temp = *this->it;
			++this->it;
			return temp;
		}

		Type& operator--() override
		{
			--this->it;
			return *this->it;
		}

		Type operator--( int ) override
		{
			Type temp = *this->it;
			--this->it;
			return temp;
		}

		IIterator<Type>& operator=( const IIterator<Type>& right ) override
		{
			auto ptr = static_cast<const IteratorListVector<Type>*>( &right );
			if( this != ptr )
			{
				this->elements = ptr->elements;
				this->it = ptr->it;
			}
			return *this;
		}

		const bool operator==( const IIterator<Type>& right )const override
		{
			const IteratorListVector<Type>* rightPtr = static_cast<const IteratorListVector<Type>*>( &right );
			if( this != rightPtr )
			{
				if( this->elements != rightPtr->elements || this->it != rightPtr->it )
				{
					return false;
				}
			}
			return true;
		}

	protected:
	private:
		std::vector<Type>& elements;
		typename std::vector<Type>::iterator it;
	};
}
