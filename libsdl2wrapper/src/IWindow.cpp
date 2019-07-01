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