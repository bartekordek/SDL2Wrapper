#include "WindowFactoryConcrete.hpp"
#include "RegularSDL2Window.hpp"
#include "CUL/GenericUtils/SimpleAssert.hpp"
#include "CUL/STL_IMPORTS/STD_cstring.hpp"

using namespace SDL2W;

WindowCreatorConcrete::WindowCreatorConcrete()
{
}

IWindow* WindowCreatorConcrete::createWindow( const WindowData& winData, ISDL2Wrapper* wrapper )
{
    auto window = new RegularSDL2Window( winData, wrapper );
    return window;
}

WindowCreatorConcrete::~WindowCreatorConcrete()
{
}