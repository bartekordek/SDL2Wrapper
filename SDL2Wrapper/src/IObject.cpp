#include "SDL2Wrapper/IObject.hpp"

using namespace SDL2W;

const bool IObject::operator==( const IObject& right )const
{
	return this == &right;
}