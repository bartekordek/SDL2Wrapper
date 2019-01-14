#include "WindowFactoryConcrete.hpp"
#include "RegularSDL2Window.hpp"
#include "WindowWithOpenGL.hpp"
#include "CUL/SimpleAssert.hpp"
#include "CUL/STD_cstring.hpp"

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
    CUL::CnstMyStr& winName )
{
    auto window = new RegularSDL2Window(
        pos, size, winName );
    return window;
}

IWindow* WindowCreatorConcrete::createWindowOGL(
    const Vector3Di& pos,
    const Vector3Du & size,
    CUL::CnstMyStr& winName )
{
    auto window = new WindowWithOpenGL( 
        pos, size,
        winName );
    return window;
}