#include "SDL2WrapperImpl.hpp"
#include "RegularSDL2Window.hpp"
#include <SDL.h>
#include <set>

#include <boost/assert.hpp>

using namespace SDL2W;

SDL2WrapperImpl::SDL2WrapperImpl()
{
    const auto sdlInitSuccess = SDL_Init( SDL_INIT_EVERYTHING );
    BOOST_ASSERT_MSG( 0 == sdlInitSuccess, "Cannot initialize SDL subsystem" );
}

SDL2WrapperImpl::~SDL2WrapperImpl()
{
    SDL_Quit();
}

std::shared_ptr<IWindow> SDL2WrapperImpl::createWindow(
    const CUL::Position2D<int>& pos,
    const CUL::Size<unsigned>& size,
    const std::string& winName )
{
    std::shared_ptr<IWindow> result;
    result.reset(
        new RegularSDL2Window( 
            pos, size, winName ) );
    this->windows[winName] = result;
    return result;
}

void SDL2WrapperImpl::renderFrame( 
    const bool clearContext,
    const bool refreshWindow )
{
    if( true == clearContext )
    {
        clearWindows();
    }

    for( auto& window : this->windows )
    {
        window.second->renderAllObjects();
    }

    if( true == refreshWindow )
    {
        refreshScreen();
    }
}

void SDL2WrapperImpl::clearWindows()
{
    for( auto& window : this->windows )
    {
        window.second->clear();
    }
}

void SDL2WrapperImpl::refreshScreen()
{
    for( auto& window : this->windows )
    {
        window.second->refreshScreen();
    }
}

void SDL2WrapperImpl::runEventLoop()
{
    SDL_Event event;
}

void SDL2WrapperImpl::stopEventLoop()
{
    SDL_Event event;
}