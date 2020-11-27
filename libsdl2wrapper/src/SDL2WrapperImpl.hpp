#pragma once
#include "SDL2Wrapper/ISDL2Wrapper.hpp"
#include "SDL2Wrapper/IWindow.hpp"
#include "SDL2Wrapper/ISDLEventObserver.hpp"
#include "WindowFactoryConcrete.hpp"
#include "CUL/CULInterface.hpp"
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

#ifdef _MSC_VER
#pragma warning( push )
#pragma warning( disable : 4820 )
#endif

class SDL2WrapperImpl final:
    public ISDL2Wrapper
{
public:
    SDL2WrapperImpl();

    ~SDL2WrapperImpl();
protected:
private:
    void init( const WindowData& wd, const Path& configPath = "" ) override;


    void registerSDLEventObserver( ISDLEventObserver* eventObserver ) override;
    void unRegisterSDLEventObserver( ISDLEventObserver* eventObserver ) override;

    CUL::CULInterface* getCul() override;

    IConfigFile* getConfig() const override;
    void refreshScreen() override;
    void renderFrame( Cbool clearContext = true, Cbool refreshWindow = true ) override;
    void clearWindows() override;

    int getRendererId( const String& name ) const override;
    const std::map<String, int>& getRenderersList() const override;
    void printAvailableRenderers() const override;

    void runEventLoop() override;
    void stopEventLoop() override;
    void pollEvents() override;

    void notifySDLEventObservers( SDL_Event& event );

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

    MouseData& getMouseData() override;

    unsigned int getInputLatency() const override;
    void setInputLatency( Cunt latencyInUs ) override;
    bool isKeyUp( const String& keyName ) const override;
    Keys& getKeyStates() override;

    IWindow* getMainWindow() const override;

    IGui* getGui() const override;
    void createKeys();
    IKey* createKey( const int keySignature, const unsigned char* sdlKey ) const;
    CUL::GUTILS::DumbPtr<CUL::CULInterface> m_culInterface;
    Logger* getLogger() const override;

    void handleEvent( const SDL_Event& event );

    static bool isMouseEvent( const SDL_Event& event );
    static bool isWindowEvent( const SDL_Event& event );

    void handleKeyboardEvent( const SDL_Event& sdlEvent );
    void handleMouseEvent( const SDL_Event& sdlEvent );
    void handleWindowEvent( const SDL_Event& sdlEvent );

    void notifyKeyboardCallbacks( const IKey& key );
    void notifyKeyboardListeners( const IKey& key );
    void notifyMouseListerners( const MouseData& md );
    void notifyMouseCallbacks( const MouseData& md );
    void notifyWindowEventListeners( const WindowEventType e );
    void notifyWindowEventCallbacks( const WindowEventType e );

    ITexture* createTexture( const Path& path, IWindow* targetWindow ) const override;
    ISprite* createSprite( const Path& path, IWindow* targetWindow ) const override;
    ISprite* createSprite( ITexture* tex, IWindow* targetWindow ) const override;

    DumbPtr<WindowCreatorConcrete> m_windowFactory;

    std::map<String, int> m_renderers;

    LckPrim<bool> eventLoopActive = true;
    LckPrim<unsigned int> m_eventLatencyUs = 256;

    std::set<IWindowEventObserver*> m_windowEventObservers;
    IWindow* m_mainWindow = nullptr;
    WindowCollection m_windows;

    Keys m_keys;

    Logger* m_logger = nullptr;

    MouseData m_mouseData;

    InitCallback m_onInitCallback;

    std::set<IKeyboardObserver*> m_keyboardObservers;
    std::vector<std::function<void( const IKey& key )>> m_keyCallbacks;
    std::mutex m_keyboardObserversMtx;

    std::set<IMouseObserver*> m_mouseObservers;
    std::vector<std::function<void( const MouseData& md )>> m_mouseCallbacks;
    std::mutex m_mouseObserversMtx;

    std::vector<std::function<void( const WindowEventType wEt )>> m_winEventCallbacks;

    std::set<ISDLEventObserver*> m_sdlEventObservers;
    std::mutex m_sdlEventObserversMtx;

    IConfigFile* m_configFile = nullptr;

private: // Deleted methods.
    SDL2WrapperImpl( const SDL2WrapperImpl& rhv ) = delete;
    SDL2WrapperImpl( SDL2WrapperImpl&& rhv ) = delete;
    SDL2WrapperImpl& operator=( const SDL2WrapperImpl& rhv ) = delete;
    SDL2WrapperImpl& operator=( SDL2WrapperImpl&& rhv ) = delete;
};

#ifdef _MSC_VER
#pragma warning( pop )
#endif

NAMESPACE_END( SDL2W )
