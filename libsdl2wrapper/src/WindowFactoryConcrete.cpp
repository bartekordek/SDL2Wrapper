#include "WindowFactoryConcrete.hpp"
#include "RegularSDL2Window.hpp"
#include "CUL/SimpleAssert.hpp"
#include "CUL/STD_cstring.hpp"

using namespace SDL2W;

WindowCreatorConcrete::WindowCreatorConcrete(
    const Vector3Di& pos,
    const Vector3Du& size,
    CnstStr& winName )
{
    this->m_mainWindow = createWindow( pos, size, winName );
}

WindowCreatorConcrete::~WindowCreatorConcrete()
{
    this->m_mainWindow = nullptr;
}

IWindow* WindowCreatorConcrete::getMainWindow()
{
    CUL::Assert::simple( this->m_mainWindow, "There is no main window." );
    return this->m_mainWindow;
}

IWindow* WindowCreatorConcrete::createWindow(
    const Vector3Di& pos,
    const Vector3Du& size,
    CnstStr& winName )
{
    auto window = new RegularSDL2Window(
        pos, size, winName );
    this->m_windows[ window ] = std::unique_ptr<IWindow>( window );
    return window;
}

IWindow* WindowCreatorConcrete::getWindow(
    const char* winName )
{
    for( auto& windows : this->m_windows )
    {
        if( std::strcmp( windows.first->getName().c_str(), winName ) == 0 )
        {
            return windows.first;
        }
    }
    return nullptr;
}

WindowCollection& SDL2W::WindowCreatorConcrete::getAllWindows()
{
    return this->m_windows;
}