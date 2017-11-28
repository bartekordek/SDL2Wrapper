#pragma once
#include "IList.hpp"
#include "ListLinked.hpp"
#include "ListVector.hpp"

namespace CUL
{
	
	class ListFactory
	{
	public:
		template<typename Type>
		static IList<Type>* createVectorListPtr()
		{
			return new ListVector<Type>();
		}
		
		template<typename Type>
		static IList<Type>* createLinkedListPtr()
		{
			return new ListLinked<Type>();
		}
		
	private:

	};
}