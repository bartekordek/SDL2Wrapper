#include "SDL2Wrapper/SDL2Wrapper.hpp"
#include "SDL2WrapperImpl.hpp"
#include "CUL/SimpleAssert.hpp"

using ISDL2Wrapper = SDL2W::ISDL2Wrapper;
using Vector3Di = SDL2W::Vector3Di;
using Vector3Du = SDL2W::Vector3Du;
using SDL2WrapperImpl = SDL2W::SDL2WrapperImpl;

ISDL2Wrapper* sdlWrapper = nullptr;

ISDL2Wrapper* SDL2W::createSDL2Wrapper(
    const Vector3Di& pos,
    const Vector3Du& size,
    CUL::CnstMyStr& winName,
    const bool opengl )
{
    CUL::Assert::simple( sdlWrapper == nullptr, "SDL2Wrapper already constructed." );
    sdlWrapper = new SDL2WrapperImpl( pos, size, winName, opengl );
    return sdlWrapper;
}

ISDL2Wrapper* SDL2W::getSDL2Wrapper()
{
    CUL::Assert::simple( sdlWrapper != nullptr, "SDL2Wrapper was not constructed yet." );
    return sdlWrapper;
}

void SDL2W::destroySDL2Wrapper()
{
    delete sdlWrapper;
}