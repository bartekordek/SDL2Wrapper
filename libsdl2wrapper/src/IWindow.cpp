#include "SDL2Wrapper/IWindow.hpp"

#include "SDL2Wrapper/IMPORT_SDL.hpp"
#include "SDL2Wrapper/IMPORT_SDL_video.hpp"

using namespace SDL2W;

IWindow::IWindow()
{
}

IWindow::~IWindow()
{
}

void IWindow::setWindowID( cunt id )
{
    this->m_winId = id;
}

const unsigned int IWindow::getWindowID() const
{
    return this->m_winId;
}

SDL_Window* IWindow::createWindow(
    const Vector3Di& pos,
    const Vector3Du& size,
    CUL::CnstMyStr& nameconst,
    bool opengl )
{
    Uint32 windowFlags = SDL_WINDOW_SHOWN;
    if( opengl )
    {
        windowFlags |= SDL_WINDOW_OPENGL;
    }
    return SDL_CreateWindow(
        nameconst.cStr(),
        static_cast< int >( pos.getX() ),
        static_cast< int >( pos.getY() ),
        static_cast< int >( size.getX() ),
        static_cast< int >( size.getY() ),
        windowFlags );
}