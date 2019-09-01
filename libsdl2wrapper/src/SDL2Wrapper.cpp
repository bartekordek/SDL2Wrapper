#include "SDL2Wrapper/Import.hpp"
#include "SDL2WrapperImpl.hpp"

#include "CUL/GenericUtils/SimpleAssert.hpp"

using namespace SDL2W;

ISDL2Wrapper* SDL2W::createSDL2Wrapper(
    const Vector3Di& pos,
    const Vector3Du& size,
    CUL::CnstMyStr& winName,
    const bool opengl )
{
    return new SDL2WrapperImpl( pos, size, winName, opengl );
}