#pragma once
#include "IList.hpp"
#include "IteratorListLinked.hpp"
#include <memory>
#include <algorithm>
namespace CUL
{
	template<typename Type>
	class ListLinked: public IList<Type>
	{
	public:
		ListLinked<Type>()
		{
			this->iterator.reset( new IteratorListLinked<Type>( this->values ) );
			this->first.reset( new IteratorListLinked<Type>( this->values ) );
			this->last.reset( new IteratorListLinked<Type>( this->values ) );
		}

		IList<Type>& operator=(const IList<Type>& list) override
		{
			if (this != &list)
			{
				IIterator<Type>* item = const_cast<IIterator<Type>*>(list.getRandomIteratorPtr());

				while (item->hasNext())
				{
					auto& value = item->next();
					this->pushBack(value);
				}
			}
			return *this;
		}

		const IIterator<Type>& begin() const override
		{
			return *this->first.get();
		}

		const IIterator<Type>& end() const override
		{
			return *this->last.get();
		}

		const IIterator<Type>& firstElement()const override
		{
			return *this->first.get();
		}

		const IIterator<Type>& lastElement()const override
		{
			return *this->lastEl.get();
		}

		IIterator<Type>* getRandomIteratorPtr()override
		{
			*this->iterator.get() = *this->first.get();
			return this->iterator.get();
		}

		IIterator<Type>& getRandomIterator()override
		{
			*this->iterator.get() = *this->first.get();
			return *this->iterator.get();
		}

		const IIterator<Type>* getRandomIteratorPtr()const override
		{
			*this->iterator.get() = *this->first.get();
			return this->iterator.get();
		}

		const IIterator<Type>& getRandomIterator()const override
		{
			*this->iterator.get() = *this->first.get();
			return *this->iterator.get();
		}

		const unsigned int size()const override
		{
			return static_cast<unsigned int>( this->values.size() );
		}

		void pushBack( const Type& element ) override
		{
			this->values.push_back( element );
			this->first->setIterator( this->values.begin() );
			this->last->setIterator( this->values.end() );
			//this->lastEl->setIterator( this->values.rend() );
		}

		void remove( const IIterator<Type>& it ) override
		{
			const Type& val = it.getVal();
			remove( val );
		}
		
		void remove( const Type& element ) override
		{
			auto newIt = std::find( this->values.begin(), this->values.end(), element );
			if( newIt != this->values.end() )
			{
				this->values.erase( newIt );
				this->first->setIterator( this->values.begin() );
				this->last->setIterator( this->values.end() );
			}
		}

		const std::shared_ptr<IIterator<Type>> find( const Type& type ) const override
		{
			std::shared_ptr<IIterator<Type>> result( new IteratorListLinked<Type>( *this->first ) );
			while( result->hasNext() )
			{
				if( result.get()->getVal() == type )
				{
					return result;
				}
				++*result;
			}
			return result;
		}

		void clear()override
		{
			values.clear();
		}

	protected:
	private:
		std::list<Type> values;
		std::unique_ptr<IteratorListLinked<Type>> iterator;
		std::unique_ptr<IteratorListLinked<Type>> first;
		std::unique_ptr<IteratorListLinked<Type>> last;
		std::unique_ptr<IteratorListLinked<Type>> lastEl;
	};
}
