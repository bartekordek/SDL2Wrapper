#include "WindowFactoryConcrete.hpp"
#include "RegularSDL2Window.hpp"
#include "CUL/GenericUtils/SimpleAssert.hpp"
#include "CUL/STL_IMPORTS/STD_cstring.hpp"

using namespace SDL2W;

WindowCreatorConcrete::WindowCreatorConcrete()
{
}

IWindow* WindowCreatorConcrete::createWindow( const WindowData& winData )
{
    auto window = new RegularSDL2Window( winData );
    return window;
}

WindowCreatorConcrete::~WindowCreatorConcrete()
{
}