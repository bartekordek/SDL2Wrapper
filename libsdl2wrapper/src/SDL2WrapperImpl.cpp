#include "SDL2WrapperImpl.hpp"
#include "RegularSDL2Window.hpp"
#include "KeySDL.hpp"
#include <SDL.h>
#include <set>
#include <boost/assert.hpp>

using namespace SDL2W;

SDL2WrapperImpl::SDL2WrapperImpl()
{
    const auto sdlInitSuccess = SDL_Init( SDL_INIT_EVERYTHING );
    BOOST_ASSERT_MSG( 0 == sdlInitSuccess, "Cannot initialize SDL subsystem" );
    createKeys();
}

void SDL2WrapperImpl::createKeys()
{
    auto kbrdState = SDL_GetKeyboardState( nullptr );
    for( int i = SDL_SCANCODE_A; i < SDL_NUM_SCANCODES; ++i )
    {
        const auto key = createKey( i, kbrdState );
        if( "" == key->getKeyName() )
        {
            delete key;
        }
        else
        {
            this->m_keys[i] = std::unique_ptr<IKey>( key );
        }
    }
}

IKey* SDL2WrapperImpl::createKey( const int keySignature, const unsigned char* sdlKey ) const
{
    IKey* result = new KeySDL();
    SDL_Scancode scanCode = static_cast<SDL_Scancode>( keySignature );
    result->setKeyName( SDL_GetScancodeName( scanCode ) );
    result->setKeyIsDown( ( 0 == sdlKey[scanCode] ) ? false : true );
    return result;
}

SDL2WrapperImpl::~SDL2WrapperImpl()
{
    this->m_keys.clear();
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
    while( this->eventLoopActive )
    {
        if( SDL_WaitEvent( &event ) > 0 )
        {
            if( ( event.type == SDL_KEYDOWN || event.type == SDL_KEYUP ) )
            {
                auto scancode = SDL_GetScancodeFromKey( event.key.keysym.sym );
                if( SDL_SCANCODE_UNKNOWN != scancode )
                {
                    const bool keyIsDown = ( SDL_KEYDOWN == event.type ) ? true : false;
                    const auto keyIndex = static_cast<unsigned int>( scancode );
                    auto& key = this->m_keys.at( keyIndex );
                    key->setKeyIsDown( keyIsDown );
                    notifyCallbacks( *key );
                }
            }
        }
    }
}

void SDL2WrapperImpl::notifyCallbacks( const IKey& key )
{
    for( auto callback: this->m_keyCallbacks )
    {
        callback( key );
    }
}

void SDL2WrapperImpl::addKeyboardEventCallback( const std::function<void( const IKey& key )>& callback )
{
    this->m_keyCallbacks.push_back( callback );
}

void SDL2WrapperImpl::stopEventLoop()
{
    this->eventLoopActive = false;
}