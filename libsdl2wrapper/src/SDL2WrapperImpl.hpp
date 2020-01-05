#pragma once
#include "SDL2Wrapper/ISDL2Wrapper.hpp"
#include "SDL2Wrapper/IWindow.hpp"
#include "ISDLInputObserver.hpp"
#include "WindowFactoryConcrete.hpp"
#include "CUL/GenericUtils/LckPrim.hpp"
#include "CUL/STL_IMPORTS/STD_vector.hpp"
#include "CUL/STL_IMPORTS/STD_set.hpp"
#include "CUL/GenericUtils/DumbPtr.hpp"

struct SDL_Surface;
union SDL_Event;

NAMESPACE_BEGIN( SDL2W )

using WindowCollection = std::map<unsigned int, std::unique_ptr<IWindow>>;
template <typename TYPE> using LckPrim = CUL::GUTILS::LckPrim<TYPE>;
template <typename TYPE> using DumbPtr = CUL::GUTILS::DumbPtr<TYPE>;
class MouseDataSDL;

class SDL2WrapperImpl final:
    public ISDL2Wrapper
{
public:
    SDL2WrapperImpl();

    ~SDL2WrapperImpl();

    void registerSDLEventObserver( ISDLInputObserver* eventObserver );
    void unRegisterSDLEventObserver( ISDLInputObserver* eventObserver );

protected:
private:
    void init( const WindowData& wd ) override;
    void refreshScreen() override;
    void renderFrame( Cbool clearContext = true, Cbool refreshWindow = true ) override;
    void clearWindows() override;
    void runEventLoop() override;
    void stopEventLoop() override;
    void pollEvents() override;

    void registerKeyboardEventCallback( const std::function<void( const IKey& key )>& callback ) override;
    void registerWindowEventCallback( const WindowCallback& callback ) override;

    void registerKeyboardEventListener( IKeyboardObserver* observer ) override;
    void unregisterKeyboardEventListener( IKeyboardObserver* observer ) override;

    void registerWindowEventListener( IWindowEventObserver* observer ) override;
    void unregisterWindowEventListener( IWindowEventObserver* observer ) override;

    void addMouseEventCallback( const MouseCallback& callback ) override;

    void registerMouseEventListener( IMouseObserver* observer ) override;
    void unregisterMouseEventListener( IMouseObserver* observer ) override;

    void registerOnInitCallback( const InitCallback& callback ) override;

    IMouseData& getMouseData() override;

    Cunt getInputLatency() const override;
    void setInputLatency( Cunt latencyInUs ) override;
    Cbool isKeyUp( CsStr& keyName ) const override;
    Keys& getKeyStates() override;

    IWindow* getMainWindow() override;

    IGui* getGui() override;
    void createKeys();
    IKey* createKey( const int keySignature, const unsigned char* sdlKey ) const;

    void handleEveent( const SDL_Event& event );

    static Cbool isMouseEvent( const SDL_Event& event );
    static Cbool isWindowEvent( const SDL_Event& event );

    void handleKeyboardEvent( const SDL_Event& sdlEvent );
    void handleMouseEvent( const SDL_Event& sdlEvent );
    void handleWindowEvent( const SDL_Event& sdlEvent );

    void notifyKeyboardCallbacks( const IKey& key );
    void notifyKeyboardListeners( const IKey& key );
    void notifyMouseListerners( const IMouseData& md );
    void notifyWindowEventListeners( const WindowEventType e );
    void notifyWindowEventCallbacks( const WindowEventType e );

    ITexture* createTexture( const Path& path, IWindow* targetWindow ) override;
    ISprite* createSprite( const Path& path, IWindow* targetWindow ) override;
    ISprite* createSprite( ITexture* tex, IWindow* targetWindow ) override;

    DumbPtr<WindowCreatorConcrete> m_windowFactory;

    LckPrim<bool> eventLoopActive = true;
    LckPrim<unsigned int> m_eventLatencyUs = 256;

    std::set<IWindowEventObserver*> m_windowEventObservers;
    IWindow* m_mainWindow = nullptr;
    WindowCollection m_windows;

    Keys m_keys;

    std::unique_ptr<MouseDataSDL> m_mouseData;

    std::vector<std::function<void( const IKey& key )>> m_keyCallbacks;
    std::vector<std::function<void( const IMouseData& md )>> m_mouseCallbacks;
    std::vector<std::function<void( const WindowEventType wEt )>> m_winEventCallbacks;

    InitCallback m_onInitCallback;

    std::set<IKeyboardObserver*> m_keyboardObservers;
    std::mutex m_keyboardObserversMtx;
    std::set<IMouseObserver*> m_mouseObservers;
    std::mutex m_mouseObserversMtx;
    std::set<ISDLInputObserver*> m_sdlEventObservers;
    std::mutex m_sdlEventObserversMtx;

private: // Deleted methods.
    SDL2WrapperImpl( const SDL2WrapperImpl& rhv ) = delete;
    SDL2WrapperImpl( SDL2WrapperImpl&& rhv ) = delete;
    SDL2WrapperImpl& operator=( const SDL2WrapperImpl& rhv ) = delete;
    SDL2WrapperImpl& operator=( SDL2WrapperImpl&& rhv ) = delete;
};

NAMESPACE_END( SDL2W )