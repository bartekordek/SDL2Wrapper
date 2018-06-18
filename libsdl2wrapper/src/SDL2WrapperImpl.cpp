#include "SDL2WrapperImpl.hpp"
#include "RegularSDL2Window.hpp"
#include "KeySDL.hpp"
#include "Sprite.hpp"
#include "TextureSDL.hpp"

#include "SDL2Wrapper/IMPORT_SDL.hpp"
#include "WindowFactoryConcrete.hpp"
#include "CUL/SimpleAssert.hpp"
#include "CUL/ITimer.hpp"

using namespace SDL2W;

SDL2WrapperImpl::SDL2WrapperImpl(
    const Vector3Di& pos,
    const Vector3Du& size,
    CnstStr& winName )
{
    const auto sdlInitSuccess = SDL_Init( SDL_INIT_EVERYTHING );
    CUL::Assert::simple( 0 == sdlInitSuccess, "Cannot initialize SDL subsystem" );
    this->m_windowFactory = new WindowCreatorConcrete( pos, size, winName );
    createKeys();
}

SDL2WrapperImpl::~SDL2WrapperImpl()
{
    delete this->m_windowFactory;
    this->m_keys.clear();
    SDL_Quit();
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
            this->m_keys[key->getKeyName()] = std::unique_ptr<IKey>( key );
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


void SDL2WrapperImpl::renderFrame( 
    const bool clearContext,
    const bool refreshWindow )
{
    for( size_t i = 0; i < length; i++ )
    {

    }
    //if( true == clearContext )
    //{
    //    clearWindows();
    //}

    //for( auto& window : this->windows )
    //{
    //    window.second->renderAllObjects();
    //}

    //if( true == refreshWindow )
    //{
    //    refreshScreen();
    //}
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
#include "CUL/STD_iostream.hpp"
void SDL2WrapperImpl::runEventLoop()
{
    SDL_Event event;
    while( this->eventLoopActive )
    {
        if( SDL_PollEvent( &event ) > 0 )
        {
            if( ( event.type == SDL_KEYDOWN || event.type == SDL_KEYUP ) )
            {
                auto scancode = event.key.keysym.scancode;
                if( SDL_SCANCODE_UNKNOWN != event.key.keysym.scancode )
                {
                    const bool keyIsDown = ( SDL_KEYDOWN == event.type ) ? true : false;
                    auto& key = this->m_keys.at( SDL_GetScancodeName( scancode ) );
                    key->setKeyIsDown( keyIsDown );
                    notifyKeyboardCallbacks( *key );
                    notifyKeyboardListeners( *key );
                }
            }
            else if( event.type == SDL_MOUSEMOTION )
            {

            }
            else if( event.type == SDL_QUIT )
            {
                notifyWindowEventListeners( WindowEventType::CLOSE );
            }
            else
            {
                std::cout << "WTF\n";
            }
        }
        CUL::ITimer::sleepMicroSeconds( this->m_eventLatencyUs );
    }
}

void SDL2WrapperImpl::notifyKeyboardCallbacks( const IKey& key )
{
    for( auto callback: this->m_keyCallbacks )
    {
        callback( key );
    }
}

void SDL2WrapperImpl::addKeyboardEventCallback(
    const std::function<void( const IKey& key )>& callback )
{
    this->m_keyCallbacks.push_back( callback );
}

void SDL2WrapperImpl::stopEventLoop()
{
    this->eventLoopActive = false;
}

void SDL2WrapperImpl::registerKeyboardEventListener(
    IKeyboardObserver* observer )
{
    this->m_keyboardObservers.insert( observer );
}

void SDL2WrapperImpl::unregisterKeyboardEventListener(
    IKeyboardObserver* observer )
{
    this->m_keyboardObservers.erase( observer );
}

void SDL2WrapperImpl::notifyKeyboardListeners( const IKey& key )
{
    for( auto listener : this->m_keyboardObservers )
    {
        listener->onKeyBoardEvent( key );
    }
}

void SDL2WrapperImpl::registerWindowEventListener(
    IWindowEventObserver* observer )
{
    this->m_windowEventObservers.insert( observer );
}

void SDL2WrapperImpl::unregisterWindowEventListener(
    IWindowEventObserver* observer )
{
    this->m_windowEventObservers.erase( observer );
}

void SDL2WrapperImpl::notifyWindowEventListeners( const WindowEventType e )
{
    for( auto listener : this->m_windowEventObservers )
    {
        listener->onWindowEvent( e );
    }
}

void SDL2WrapperImpl::setInputLatency( const unsigned int latencyInUs )
{
    this->m_eventLatencyUs = latencyInUs;
}

const bool SDL2WrapperImpl::isKeyUp( const std::string& keyName )const
{
    return this->m_keys.at( keyName )->getKeyIsDown();
}

Keys& SDL2WrapperImpl::getKeyStates()
{
    return this->m_keys;
}

IWindowFactory* SDL2W::SDL2WrapperImpl::getWindowFactory()
{
    CUL::Assert::simple( this->m_windowFactory, "Windows Factory not yet constructed." );
    return this->m_windowFactory;
}

ISprite* SDL2WrapperImpl::createSprite( const Path& objPath,
                                        IWindow* targetWindow )
{
    if( IWindow::Type::SDL_WIN == targetWindow->getType() )
    {
        auto sdlWin = static_cast<RegularSDL2Window*>( targetWindow );
        return sdlWin->createSprite( objPath );
    }
    return nullptr;
}

ITexture* SDL2WrapperImpl::createTexture( const Path& objPath,
                                          IWindow* targetWindow )
{
    if( IWindow::Type::SDL_WIN == targetWindow->getType() )
    {
        auto sdlWin = static_cast<RegularSDL2Window*>( targetWindow );
        return sdlWin->createTexture( objPath );
    }
    return nullptr;
}

ISprite* SDL2WrapperImpl::createSprite( ITexture* tex,
                                        IWindow* targetWindow )
{
    if( IWindow::Type::SDL_WIN == targetWindow->getType() )
    {
        auto sdlWin = static_cast<RegularSDL2Window*>( targetWindow );
        return sdlWin->createSprite( tex );
    }
    return nullptr;
}