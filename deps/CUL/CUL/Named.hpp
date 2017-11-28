#pragma once
#include "CUL/MyString.hpp"
namespace CUL
{
	class Name
	{
	public:
		explicit Name( const CUL::MyString& name = CUL::MyString("") );
		explicit Name( const Name& name );
		virtual ~Name();

		void setName( const CUL::MyString& name );
		const CUL::MyString& GetName()const;

		Name& operator=( const Name& name );

	protected:
	private:
		MyString mName;

	};
}