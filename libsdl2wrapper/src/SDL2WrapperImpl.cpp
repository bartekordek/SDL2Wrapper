#include "SimpleUtils.hpp"
#include "SDL2WrapperImpl.hpp"
#include "RegularSDL2Window.hpp"
#include "Input/KeySDL.hpp"
#include "Input/MouseDataSDL.hpp"
#include "Sprite.hpp"
#include "TextureSDL.hpp"

#include "SDL2Wrapper/IMPORT_SDL.hpp"
#include "CUL/ITimer.hpp"

using namespace SDL2W;

SDL2WrapperImpl::SDL2WrapperImpl()
{
}

void SDL2WrapperImpl::init( const WindowData& wd )
{
    const auto sdlInitSuccess = SDL_Init(
        SDL_INIT_TIMER &
        SDL_INIT_AUDIO &
        SDL_INIT_VIDEO &
        SDL_INIT_EVENTS
    );
    if( 0 != sdlInitSuccess )
    {
        Assert( 0, SDL_GetError() );
    }

    int flags = IMG_INIT_JPG | IMG_INIT_PNG;
    int initalizedFlags = IMG_Init( flags );

    if( ( initalizedFlags & flags ) != flags )
    {
        Assert( 0, "Cannot initialize all sdl image flags." );
    }

    m_windowFactory = new WindowCreatorConcrete();
    m_mainWindow = m_windowFactory->createWindow( wd );
    m_windows[m_mainWindow->getWindowID()] = std::unique_ptr<IWindow>( m_mainWindow );

    createKeys();

    m_mouseData.reset( new MouseDataSDL() );

    if( m_onInitCallback )
    {
        m_onInitCallback();
    }
}

SDL2WrapperImpl::~SDL2WrapperImpl()
{
    m_keys.clear();
    SDL_Quit();
}

#ifdef _MSC_VER
// Yes, I know that is a Spectre mitigation.
// But for now, I let this as TODO, since i don't know
// How to fix this.
// TODO
#pragma warning( push )
#pragma warning( disable: 5045 )
#endif
void SDL2WrapperImpl::createKeys()
{
    logMsg( "SDL2WrapperImpl::createKeys()::Begin" );
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
            const auto keyName = key->getKeyName();
            m_keys[keyName] = std::unique_ptr<IKey>( key );
        }
    }
    logMsg( "SDL2WrapperImpl::createKeys() - found keys:" );
    for( const auto& key : m_keys )
    {
        logMsg( key.first );
    }
    logMsg( "SDL2WrapperImpl::createKeys()::End" );
}
#ifdef _MSC_VER
#pragma warning( pop )
#endif

IKey* SDL2WrapperImpl::createKey( const int keySignature, const unsigned char* sdlKey ) const
{
    IKey* result = new KeySDL();
    SDL_Scancode scanCode = static_cast<SDL_Scancode>( keySignature );
    result->setKeyName( SDL_GetScancodeName( scanCode ) );
    result->setKeyIsDown( ( 0 == sdlKey[scanCode] ) ? false : true );
    return result;
}

void SDL2WrapperImpl::renderFrame( Cbool clearContext, Cbool refreshWindow )
{
    if( true == clearContext )
    {
        clearWindows();
    }

    for( auto& window : m_windows )
    {
        window.second->renderAll();
    }

    if( true == refreshWindow )
    {
        refreshScreen();
    }
}

void SDL2WrapperImpl::clearWindows()
{
    for( auto& window : m_windows )
    {
        window.second->clearBuffers();
    }
}

void SDL2WrapperImpl::refreshScreen()
{
    for( auto& window : m_windows )
    {
        window.second->updateScreenBuffers();
    }
}

#include "CUL/STL_IMPORTS/STD_iostream.hpp"
void SDL2WrapperImpl::runEventLoop()
{
    CUL::ThreadUtils::setCurrentThreadName( "SDL2WrapperImpl::runEventLoop()/main" );
    logMsg( "SDL2WrapperImpl::runEventLoop()::Begin" );

    while( eventLoopActive )
    {
        pollEvents();
        CUL::ITimer::sleepMicroSeconds( m_eventLatencyUs );
    }
    logMsg( "SDL2WrapperImpl::runEventLoop()::End" );
}

void SDL2WrapperImpl::pollEvents()
{
    static SDL_Event event;
    if( SDL_PollEvent( &event ) > 0 )
    {
        logMsg( "SDL2WrapperImpl::runEventLoop()::Handling Event..." );
        handleEveent( event );
        {
            std::lock_guard<std::mutex> lock( m_sdlEventObserversMtx );
            for( auto eventObserver : m_sdlEventObservers )
            {
                eventObserver->handleEvent( event );
            }
        }
    }
}

void SDL2WrapperImpl::handleEveent( const SDL_Event& event )
{
    logMsg( "SDL2WrapperImpl::handleEveent( " +
        CUL::String( event.type ) + " );" );
    if( ( event.type == SDL_KEYDOWN || event.type == SDL_KEYUP ) )
    {
        if( SDL_SCANCODE_UNKNOWN != event.key.keysym.scancode )
        {
            handleKeyboardEvent( event );
        }
    }

    if( isMouseEvent( event ) )
    {
        handleMouseEvent( event );
        notifyMouseListerners( *m_mouseData );
    }

    if( isWindowEvent( event ) )
    {
        handleWindowEvent( event );
    }
}

const bool SDL2WrapperImpl::isMouseEvent( const SDL_Event& event )
{
    switch( event.type )
    {
    case SDL_MOUSEMOTION:
    case SDL_MOUSEBUTTONDOWN:
    case SDL_MOUSEBUTTONUP:
    case SDL_MOUSEWHEEL:
        return true;
    default:
        return false;
        break;
    }
}

const bool SDL2WrapperImpl::isWindowEvent( const SDL_Event& event )
{
    switch( event.type )
    {
    case SDL_QUIT:
    case SDL_APP_TERMINATING:
    case SDL_WINDOWEVENT:
    case SDL_WINDOWEVENT_MOVED:
    case SDL_WINDOWEVENT_ENTER:
    case SDL_WINDOWEVENT_LEAVE:
        return true;
    default:
        return false;
        break;
    }
}

void SDL2WrapperImpl::handleKeyboardEvent( const SDL_Event& sdlEvent )
{
    logMsg( "SDL2WrapperImpl::handleKeyboardEvent" );
    const bool keyIsDown = ( SDL_KEYDOWN == sdlEvent.type ) ? true : false;
    auto& key = m_keys.at( SDL_GetScancodeName( sdlEvent.key.keysym.scancode ) );
    key->setKeyIsDown( keyIsDown );

    logMsg( "EVENT: Key press/release, key: " + key->getKeyName().string() );
    logMsg( "EVENT: Key press/release, keyID: " + std::to_string( sdlEvent.key.keysym.scancode ) );

    notifyKeyboardCallbacks( *key );
    notifyKeyboardListeners( *key );
}

void SDL2WrapperImpl::handleMouseEvent( const SDL_Event& event )
{
    if( event.type == SDL_MOUSEBUTTONDOWN ||
        event.type == SDL_MOUSEBUTTONUP )
    {
        const bool isUp = event.type == SDL_MOUSEBUTTONUP ? true : false;

        const auto mb = event.button;
        const auto mbIndex = static_cast<unsigned short>( mb.button );
        m_mouseData->setState( mbIndex, isUp );
    }
    else if( event.type == SDL_MOUSEMOTION )
    {
        m_mouseData->setPos( event.button.x, event.button.y );
    }
    else if( event.type == SDL_MOUSEWHEEL )
    {
        const auto we = event.wheel;
        m_mouseData->setWheel(
            we.x,
            we.y,
            we.direction == SDL_MOUSEWHEEL_NORMAL ? SDL2W::WheelDirection::UP : SDL2W::WheelDirection::DOWN );
    }
}

void SDL2WrapperImpl::handleWindowEvent( const SDL_Event& sdlEvent )
{
    logMsg( "Window Event: " + std::to_string( sdlEvent.type ) );

    auto eventType = WindowEventType::NONE;
    switch( sdlEvent.type )
    {
    case SDL_QUIT:
        eventType = WindowEventType::CLOSE; break;

    case SDL_WINDOWEVENT_MOVED:
        eventType = WindowEventType::MOVED; break;

    case SDL_WINDOWEVENT_ENTER:
        eventType = WindowEventType::MOUSE_ENTERED; break;

    case SDL_WINDOWEVENT_LEAVE:
        eventType = WindowEventType::MOUSE_LEAVED; break;

    default:
        return;
    }

    notifyWindowEventListeners( eventType );
    notifyWindowEventCallbacks( eventType );
}

void SDL2WrapperImpl::notifyKeyboardCallbacks( const IKey& key )
{
    for( auto callback : m_keyCallbacks )
    {
        callback( key );
    }
}

void SDL2WrapperImpl::registerKeyboardEventCallback( const std::function<void( const IKey& key )>& callback )
{
    m_keyCallbacks.push_back( callback );
}

void SDL2WrapperImpl::registerWindowEventCallback( const WindowCallback& callback )
{
    m_winEventCallbacks.push_back( callback );
}

void SDL2WrapperImpl::stopEventLoop()
{
    eventLoopActive = false;
}

void SDL2WrapperImpl::registerKeyboardEventListener(
    IKeyboardObserver* observer )
{
    std::lock_guard<std::mutex> lock( m_keyboardObserversMtx );
    m_keyboardObservers.insert( observer );
}

void SDL2WrapperImpl::unregisterKeyboardEventListener( IKeyboardObserver* observer )
{
    std::lock_guard<std::mutex> lock( m_keyboardObserversMtx );
    m_keyboardObservers.erase( observer );
}

void SDL2WrapperImpl::notifyKeyboardListeners( const IKey& key )
{
    std::lock_guard<std::mutex> lock( m_keyboardObserversMtx );
    for( auto listener : m_keyboardObservers )
    {
        listener->onKeyBoardEvent( key );
    }
}

void SDL2WrapperImpl::notifyMouseListerners( const IMouseData& md )
{
    std::lock_guard<std::mutex> lock( m_mouseObserversMtx );
    for( const auto& listener : m_mouseObservers )
    {
        listener->onMouseEvent( md );
    }
}

void SDL2WrapperImpl::registerMouseEventListener( IMouseObserver* observer )
{
    std::lock_guard<std::mutex> lock( m_mouseObserversMtx );
    m_mouseObservers.insert( observer );
}

void SDL2WrapperImpl::unregisterMouseEventListener( IMouseObserver* observer )
{
    std::lock_guard<std::mutex> lock( m_mouseObserversMtx );
    m_mouseObservers.erase( observer );
}

void SDL2WrapperImpl::registerOnInitCallback( const InitCallback& callback )
{
    m_onInitCallback = callback;
}

void SDL2WrapperImpl::registerWindowEventListener(
    IWindowEventObserver* observer )
{
    m_windowEventObservers.insert( observer );
}

void SDL2WrapperImpl::unregisterWindowEventListener(
    IWindowEventObserver* observer )
{
    m_windowEventObservers.erase( observer );
}

void SDL2WrapperImpl::addMouseEventCallback( const MouseCallback& callback )
{
    m_mouseCallbacks.push_back( callback );
}

IMouseData& SDL2WrapperImpl::getMouseData()
{
    return *m_mouseData;
}

void SDL2WrapperImpl::notifyWindowEventListeners( const WindowEventType e )
{
    for( auto listener : m_windowEventObservers )
    {
        listener->onWindowEvent( e );
    }
}

void SDL2WrapperImpl::notifyWindowEventCallbacks( const WindowEventType e )
{
    for( auto callback : m_winEventCallbacks )
    {
        callback( e );
    }
}

Cunt SDL2WrapperImpl::getInputLatency() const
{
    return m_eventLatencyUs.getValCopy();
}

void SDL2WrapperImpl::setInputLatency( Cunt latencyInUs )
{
    m_eventLatencyUs = latencyInUs;
}

const bool SDL2WrapperImpl::isKeyUp( CsStr& keyName ) const
{
    return m_keys.at( keyName )->getKeyIsDown();
}

Keys& SDL2WrapperImpl::getKeyStates()
{
    return m_keys;
}

ISprite* SDL2WrapperImpl::createSprite(
    const Path& objPath,
    IWindow* targetWindow )
{
    return targetWindow->createSprite( objPath );
}

ITexture* SDL2WrapperImpl::createTexture(
    const Path& objPath,
    IWindow* targetWindow )
{
    if( IWindow::Type::SDL_WIN == targetWindow->getType() )
    {
        return targetWindow->createTexture( objPath );
    }
    return nullptr;
}

ISprite* SDL2WrapperImpl::createSprite(
    ITexture* tex,
    IWindow* targetWindow )
{
    if( IWindow::Type::SDL_WIN == targetWindow->getType() )
    {
        return targetWindow->createSprite( tex );
    }
    return nullptr;
}

IWindow* SDL2WrapperImpl::getMainWindow()
{
    return m_mainWindow;
}

IGui* SDL2WrapperImpl::getGui()
{
    return nullptr;
}

void SDL2WrapperImpl::registerSDLEventObserver( ISDLInputObserver* eventObserver )
{
    std::lock_guard<std::mutex> lock( m_sdlEventObserversMtx );
    m_sdlEventObservers.insert( eventObserver );
}

void SDL2WrapperImpl::unRegisterSDLEventObserver( ISDLInputObserver* eventObserver )
{
    std::lock_guard<std::mutex> lock( m_sdlEventObserversMtx );
    m_sdlEventObservers.erase( eventObserver );
}