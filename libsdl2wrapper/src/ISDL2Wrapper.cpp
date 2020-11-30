#include "SDL2Wrapper/ISDL2Wrapper.hpp"
#include "SDL2WrapperImpl.hpp"

using namespace SDL2W;

ISDL2Wrapper::ISDL2Wrapper()
{
}

ISDL2Wrapper* ISDL2Wrapper::createSDL2Wrapper()
{
    return new SDL2WrapperImpl();
}

ISDL2Wrapper::~ISDL2Wrapper()
{
}