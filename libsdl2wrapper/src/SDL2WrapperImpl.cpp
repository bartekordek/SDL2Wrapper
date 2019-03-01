#include "SDL2WrapperImpl.hpp"
#include "RegularSDL2Window.hpp"
#include "Input/KeySDL.hpp"
#include "Input/MouseDataSDL.hpp"
#include "Sprite.hpp"
#include "TextureSDL.hpp"

#include "SDL2Wrapper/IMPORT_SDL.hpp"
#include "CUL/SimpleAssert.hpp"
#include "CUL/ITimer.hpp"
#include "CUL/Log/ILogContainer.hpp"

using namespace SDL2W;

SDL2WrapperImpl::SDL2WrapperImpl(
    const Vector3Di& pos,
    const Vector3Du& size,
    CUL::CnstMyStr& winName,
    const bool opengl )
{
    const auto sdlInitSuccess = SDL_Init( SDL_INIT_EVERYTHING );
    if( 0 != sdlInitSuccess )
    {
        CUL::Assert::simple( 0, SDL_GetError() );
    }
    
    this->m_windowFactory = new WindowCreatorConcrete();
    if( opengl )
    {
        this->m_mainWindow = this->m_windowFactory->createWindowOGL( pos, size, winName );
    }
    else
    {
        this->m_mainWindow = this->m_windowFactory->createWindow( pos, size, winName );
    }
    this->m_windows[ this->m_mainWindow->getWindowID() ] = std::unique_ptr<IWindow>( this->m_mainWindow );
    
    createKeys();

    this->m_mouseData.reset( new MouseDataSDL() );

}

SDL2WrapperImpl::~SDL2WrapperImpl()
{
    delete this->m_windowFactory;
    this->m_windowFactory = nullptr;
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
            const auto keyName = key->getKeyName();
            this->m_keys[ keyName ] = std::unique_ptr<IKey>( key );
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
    if( true == clearContext )
    {
        clearWindows();
    }

    for( auto& window : this->m_windows )
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
    for( auto& window : this->m_windows )
    {
        window.second->clearBuffers();
    }
}

void SDL2WrapperImpl::refreshScreen()
{
    for( auto& window : this->m_windows )
    {
        window.second->updateScreenBuffers();
    }
}

#include "CUL/STD_iostream.hpp"
void SDL2WrapperImpl::runEventLoop()
{
    CUL::ThreadUtils::setCurrentThreadName( "SDL2WrapperImpl::runEventLoop()/main" );
    SDL_Event event;
    while( this->eventLoopActive )
    {
        if( SDL_PollEvent( &event ) > 0 )
        {
            handleEveent( event );
        }
        CUL::ITimer::sleepMicroSeconds( this->m_eventLatencyUs );
    }
}

void SDL2WrapperImpl::handleEveent( const SDL_Event& event )
{
    const CUL::MyString log = "SDL2WrapperImpl::handleEveent( " +
        CUL::MyString( event.type ) + " );";
    CUL::LOG::LOG_CONTAINER::getLogger()->log( log );
    if( ( event.type == SDL_KEYDOWN || event.type == SDL_KEYUP ) )
    {
        if( SDL_SCANCODE_UNKNOWN != event.key.keysym.scancode )
        {
            handleKeyboardEvent( event );
        }
    }
    else if( event.type == SDL_QUIT )
    {
        notifyWindowEventListeners( WindowEventType::CLOSE );
    }
    else if( event.type == SDL_WINDOWEVENT_MOVED )
    {
        CUL::LOG::LOG_CONTAINER::getLogger()->log( "Window has been moved." );
        notifyWindowEventListeners( WindowEventType::MOVED );
    }
    else if( event.type == SDL_WINDOWEVENT_ENTER )
    {
        notifyWindowEventListeners( WindowEventType::MOUSE_ENTERED );
    }
    else if( event.type == SDL_WINDOWEVENT_LEAVE )
    {
        notifyWindowEventListeners( WindowEventType::MOUSE_LEAVED );
    }

    if( eventIsMouseEvent( event ) )
    {
        handleMouseEvent( event );
        notifyMouseListerners( *this->m_mouseData );
    }
}

const bool SDL2WrapperImpl::eventIsMouseEvent( const SDL_Event& event )
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

void SDL2WrapperImpl::handleKeyboardEvent( const SDL_Event& sdlEvent )
{
    CUL::LOG::LOG_CONTAINER::getLogger()->log( "SDL2WrapperImpl::handleKeyboardEvent" );
    const bool keyIsDown = ( SDL_KEYDOWN == sdlEvent.type ) ? true : false;
    auto& key = this->m_keys.at( SDL_GetScancodeName( sdlEvent.key.keysym.scancode ) );
    key->setKeyIsDown( keyIsDown );

    CUL::LOG::LOG_CONTAINER::getLogger()->log(
        "EVENT: Key press/release, key: " +
        key->getKeyName().string() );

    CUL::LOG::LOG_CONTAINER::getLogger()->log(
        "EVENT: Key press/release, keyID: " +
        sdlEvent.key.keysym.scancode );

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
        this->m_mouseData->setState( mbIndex, isUp );
    }
    else if( event.type == SDL_MOUSEMOTION )
    {
        this->m_mouseData->setPos( event.button.x, event.button.y );
    }
    else if( event.type == SDL_MOUSEWHEEL )
    {
        const auto we = event.wheel;
        this->m_mouseData->setWheel(
            we.x,
            we.y,
            we.direction == SDL_MOUSEWHEEL_NORMAL ? SDL2W::WheelDirection::UP : SDL2W::WheelDirection::DOWN );
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

void SDL2WrapperImpl::notifyMouseListerners( const IMouseData& md )
{
    for( const auto& listener: this->m_mouseObservers )
    {
        listener->onMouseEvent( md );
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

void SDL2WrapperImpl::addMouseEventCallback(
    const std::function<void( const IMouseData& md )>& callback )
{
    this->m_mouseCallbacks.push_back( callback );
}

void SDL2WrapperImpl::registerMouseEventListener( IMouseObserver* observer )
{
    this->m_mouseObservers.insert( observer );
}

void SDL2WrapperImpl::unregisterMouseEventListener( IMouseObserver* observer )
{
    this->m_mouseObservers.erase( observer );
}

IMouseData& SDL2WrapperImpl::getMouseData( void )
{
    return *this->m_mouseData;
}

void SDL2WrapperImpl::notifyWindowEventListeners( const WindowEventType e )
{
    for( auto listener : this->m_windowEventObservers )
    {
        listener->onWindowEvent( e );
    }
}

cunt SDL2WrapperImpl::getInputLatency()const
{
    return this->m_eventLatencyUs.getValCopy();
}

void SDL2WrapperImpl::setInputLatency( cunt latencyInUs )
{
    this->m_eventLatencyUs = latencyInUs;
}

const bool SDL2WrapperImpl::isKeyUp( CUL::CnstMyStr& keyName )const
{
    return this->m_keys.at( keyName )->getKeyIsDown();
}

Keys& SDL2WrapperImpl::getKeyStates()
{
    return this->m_keys;
}

ISprite* SDL2WrapperImpl::createSprite( const Path& objPath,
                                        IWindow* targetWindow )
{
    return targetWindow->createSprite( objPath );
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

IWindow* SDL2WrapperImpl::getMainWindow()
{
    return this->m_mainWindow;
}