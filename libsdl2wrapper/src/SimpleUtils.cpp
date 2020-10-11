#include "SimpleUtils.hpp"

using namespace SDL2W;

void SDL2W::Assert( const bool result, const CUL::String& msg )
{
    CUL::Assert::simple( result, msg );
}