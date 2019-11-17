#include "SDL2Wrapper/Import.hpp"
#include "SDL2WrapperImpl.hpp"

#include "CUL/GenericUtils/SimpleAssert.hpp"

using namespace SDL2W;

ISDL2Wrapper* SDL2W::createSDL2Wrapper( const WindowData& winData )
{
    return new SDL2WrapperImpl( winData );
}