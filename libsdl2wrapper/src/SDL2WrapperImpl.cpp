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

bool SDLBoolToCppBool( const SDL_bool value )
{
    return value == 1 ? true : false;
}

SDL2WrapperImpl::SDL2WrapperImpl()
{
}

#ifdef _MSC_VER
// Yes, I know that is a Spectre mitigation.
// But for now, I let this as TODO, since i don't know
// How to fix this.
// TODO
#pragma warning( push )
#pragma warning( disable: 5045 )
#endif

void SDL2WrapperImpl::init( const WindowData& wd, IConfigFile* configFile )
{
    m_culInterface = std::move( CUL::CULInterface::createInstance() );
    m_logger = m_culInterface->getLogger();
    m_configFile = configFile;
    m_logger->log( "Initializing SDL..." );
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
    m_logger->log( "Initializing SDL... Done." );


    auto cpuCount = SDL_GetCPUCount();
    m_logger->log( "Available cpu cores: " + String( cpuCount ) );

    auto cpuCacheSize = SDL_GetCPUCacheLineSize();
    m_logger->log( "Available cache size: " + String( cpuCacheSize ) );

    auto hasRDTSC = SDLBoolToCppBool( SDL_HasRDTSC() );
    m_logger->log( "CPU has the RDTSC instruction: " + String( hasRDTSC ) );

    auto renderDriversCount = SDL_GetNumRenderDrivers();
    m_logger->log( "Available render drivers count: " + String( renderDriversCount ) + "\n" );

    SDL_RendererInfo renderInfo;
    for( auto i = 0; i < renderDriversCount; ++i )
    {
        m_logger->log( "#################################################################################" );
        Assert( SDL_GetRenderDriverInfo( i, &renderInfo ) == 0, "Cannnot get driver info for index = " + String( i ) );
        String rendererName( renderInfo.name );
        m_logger->log( "Renderer name:" + rendererName );
        m_logger->log( "Max texture width = " + CUL::String( renderInfo.max_texture_width ) );
        m_logger->log( "Max texture height = " + CUL::String( renderInfo.max_texture_width ) );
        m_logger->log( "Available texture formats:" );
        for( Uint32 iTexFormat = 0; iTexFormat < renderInfo.num_texture_formats; ++iTexFormat )
        {
            m_logger->log( String( SDL_GetPixelFormatName( renderInfo.texture_formats[ iTexFormat ] ) ) );
        }

        m_logger->log( "#################################################################################\n" );

        m_renderers[ rendererName ] = i;
    }


    m_windowFactory = new WindowCreatorConcrete( m_logger );
    m_mainWindow = m_windowFactory->createWindow( wd, this );
    m_windows[m_mainWindow->getWindowID()] = std::unique_ptr<IWindow>( m_mainWindow );

    createKeys();

    m_mouseData = std::move( std::unique_ptr<MouseDataSDL>( new MouseDataSDL() ) );

    if( m_onInitCallback )
    {
        m_onInitCallback();
    }
}

CUL::CULInterface* SDL2WrapperImpl::getCul()
{
    return m_culInterface;
}

IConfigFile* SDL2WrapperImpl::getConfig()
{
    return m_configFile;
}


void SDL2WrapperImpl::createKeys()
{
    m_logger->log( "SDL2WrapperImpl::createKeys()::Begin" );
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
    m_logger->log( "SDL2WrapperImpl::createKeys() - found keys:" );
    for( const auto& key : m_keys )
    {
        m_logger->log( key.first );
    }
    m_logger->log( "SDL2WrapperImpl::createKeys()::End" );
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

Logger* SDL2WrapperImpl::getLogger()
{
    return m_logger;
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

int SDL2WrapperImpl::getRendererId( const String& name ) const
{
    return m_renderers.at( name );
}

const std::map<String, int>& SDL2WrapperImpl::getRenderersList() const
{
    return m_renderers;
}

void SDL2WrapperImpl::printAvailableRenderers() const
{
    m_logger->log( "SDL2WrapperImpl::printAvailableRenderers():" );
    for( const auto& renderer: m_renderers )
    {
        m_logger->log( "Name: " + renderer.first + ", id: " + String( renderer.second ) );
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
    m_logger->log( "SDL2WrapperImpl::runEventLoop()::Begin" );

    while( eventLoopActive )
    {
        pollEvents();
        CUL::ITimer::sleepMicroSeconds( m_eventLatencyUs );
    }
    m_logger->log( "SDL2WrapperImpl::runEventLoop()::End" );
}

void SDL2WrapperImpl::pollEvents()
{
    static SDL_Event event;
    if( SDL_PollEvent( &event ) > 0 )
    {
        handleEvent( event );
        {
            std::lock_guard<std::mutex> lock( m_sdlEventObserversMtx );
            for( auto eventObserver : m_sdlEventObservers )
            {
                eventObserver->handleEvent( event );
            }
        }
    }
}

void SDL2WrapperImpl::handleEvent( const SDL_Event& event )
{
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

bool SDL2WrapperImpl::isMouseEvent( const SDL_Event& event )
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

bool SDL2WrapperImpl::isWindowEvent( const SDL_Event& event )
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
    const bool keyIsDown = ( SDL_KEYDOWN == sdlEvent.type ) ? true : false;
    auto& key = m_keys.at( SDL_GetScancodeName( sdlEvent.key.keysym.scancode ) );
    key->setKeyIsDown( keyIsDown );

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

unsigned int SDL2WrapperImpl::getInputLatency() const
{
    return m_eventLatencyUs.getValCopy();
}

void SDL2WrapperImpl::setInputLatency( Cunt latencyInUs )
{
    m_eventLatencyUs = latencyInUs;
}

bool SDL2WrapperImpl::isKeyUp( const String& keyName ) const
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

SDL2WrapperImpl::~SDL2WrapperImpl()
{
    m_keys.clear();
    SDL_Quit();
}