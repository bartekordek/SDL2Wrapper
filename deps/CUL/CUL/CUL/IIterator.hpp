#pragma once
namespace CUL
{
	template<typename Type>
	class IIterator
	{
	public:
		IIterator() = default;
		virtual ~IIterator() = default;
		virtual Type& getVal() = 0;
		virtual const Type& getVal() const = 0;

		virtual const bool hasNext()const = 0;
		virtual Type& next() = 0;

		virtual const bool hasPrevious()const = 0;
		virtual Type& previous() = 0;

		virtual const bool isEmpty()const = 0;

		virtual Type& first() = 0;
		virtual const Type& first()const = 0;
		virtual Type& last() = 0;
		virtual const Type& last()const = 0;

		virtual Type& operator++() = 0;
		virtual Type operator++( int ) = 0;

		virtual Type& operator--() = 0;
		virtual Type operator--( int ) = 0;

		virtual IIterator<Type>& operator=( const IIterator<Type>& right ) = 0;
		virtual const bool operator==( const IIterator<Type>& right )const = 0;

	protected:
	private:
		
	};
}