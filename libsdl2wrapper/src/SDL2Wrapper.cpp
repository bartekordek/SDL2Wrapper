#include "SDL2Wrapper/SDL2Wrapper.hpp"
#include "SDL2WrapperImpl.hpp"
#include "CUL/SimpleAssert.hpp"
namespace SDL2W
{
    ISDL2Wrapper* sdlWrapper = nullptr;

    ISDL2Wrapper* createSDL2Wrapper( const Vector3Di& pos,
                                     const Vector3Du& size,
                                     CnstStr& winName,
                                     const bool opengl )
    {
        CUL::Assert::simple( sdlWrapper == nullptr, "SDL2Wrapper already constructed." );
        sdlWrapper = new SDL2WrapperImpl( pos, size, winName, opengl );
        return sdlWrapper;
    }

    ISDL2Wrapper* getSDL2Wrapper()
    {
        CUL::Assert::simple( sdlWrapper != nullptr, "SDL2Wrapper was not constructed yet." );
        return sdlWrapper;
    }

    void destroySDL2Wrapper()
    {
        delete sdlWrapper;
    }
}