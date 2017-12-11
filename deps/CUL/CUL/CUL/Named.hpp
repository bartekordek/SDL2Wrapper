#pragma once
#include <CUL/CUL.hpp>
#include "CUL/MyString.hpp"
namespace CUL
{
	class CULLib_API Name
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