#pragma once
#include "IIterator.hpp"
#include <memory>
namespace CUL
{
	template<typename Type>
	class IList
	{
	public:
		IList() = default;
		virtual ~IList() = default;

		virtual IList& operator=( const IList& list ) = 0;

		virtual const IIterator<Type>& begin() const = 0;
		virtual const IIterator<Type>& end() const = 0;

		virtual const IIterator<Type>& firstElement()const = 0;
		virtual const IIterator<Type>& lastElement()const = 0;

		virtual IIterator<Type>* getRandomIteratorPtr() = 0;
		virtual IIterator<Type>&  getRandomIterator() = 0;

		virtual const IIterator<Type>* getRandomIteratorPtr()const = 0;
		virtual const IIterator<Type>&  getRandomIterator()const = 0;

		virtual const unsigned int size()const = 0;

		virtual void pushBack( const Type& element ) = 0;
		virtual void remove( const IIterator<Type>& it ) = 0;
		virtual void remove( const Type& elements ) = 0;

		virtual void clear() = 0;

		virtual const std::shared_ptr<IIterator<Type>> find( const Type& type ) const = 0;

	protected:
	private:
	};
}
