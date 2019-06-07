#include "SDL2Wrapper/IWindow.hpp"

#include "SDL2Wrapper/IMPORT_SDL.hpp"
#include "SDL2Wrapper/IMPORT_SDL_video.hpp"

#include "CUL/Log/ILogContainer.hpp"

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
    SDL_Window* result = nullptr;
    Uint32 windowFlags = SDL_WINDOW_SHOWN;
    if( opengl )
    {
        windowFlags |= SDL_WINDOW_OPENGL;
    }
    result = SDL_CreateWindow(
        nameconst.cStr(),
        static_cast< int >( pos.getX() ),
        static_cast< int >( pos.getY() ),
        static_cast< int >( size.getX() ),
        static_cast< int >( size.getY() ),
        windowFlags );
    if( nullptr == result )
    {
        auto sdlError = SDL_GetError();
        CUL::MyString s_sdlError( sdlError );
        CUL::LOG::LOG_CONTAINER::getLogger()->log(
        "ERROR" + s_sdlError, CUL::LOG::Severity::CRITICAL );
        CUL::Assert::simple( result, "The Window has not been initialized." );
    }
    
    return result;
}