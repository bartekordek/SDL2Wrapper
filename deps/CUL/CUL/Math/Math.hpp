#pragma once
namespace CUL
{
	namespace Math
	{
		namespace Util
		{
			template<typename Type>
			Type abs( const Type arg )
			{
				if( arg < 0 )
				{
					return 0 - arg;
				}
				return arg;
			}
		}
	}
}