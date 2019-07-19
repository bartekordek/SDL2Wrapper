#include "WindowFactoryConcrete.hpp"
#include "RegularSDL2Window.hpp"
#include "CUL/SimpleAssert.hpp"
#include "CUL/STL_IMPORTS/STD_cstring.hpp"

using namespace SDL2W;

WindowCreatorConcrete::WindowCreatorConcrete()
{
}

WindowCreatorConcrete::~WindowCreatorConcrete()
{
}

IWindow* WindowCreatorConcrete::createWindow(
    const Vector3Di& pos,
    const Vector3Du& size,
    CUL::CnstMyStr& winName,
    const bool withOpenGL )
{
    auto window = new RegularSDL2Window(
        pos, size, winName, withOpenGL );
    return window;
}