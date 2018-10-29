#pragma once
#include "SDL2Wrapper/ISDL2Wrapper.hpp"
#include "SDL2Wrapper/IWindow.hpp"
#include "WindowFactoryConcrete.hpp"
#include "CUL/IThreadUtility.hpp"
#include "CUL/LckPrim.hpp"
#include "CUL/STD_vector.hpp"
#include "CUL/STD_set.hpp"
struct SDL_Surface;
union SDL_Event;
namespace SDL2W
{
    using WindowEventType = IWindowEventObserver::WindowEventType;
    using IThreadUtil = CUL::IThreadUtility;
    class SDL2WrapperImpl:
        public ISDL2Wrapper
    {
    public:
        SDL2WrapperImpl(
            const Vector3Di& pos = Vector3Di(),
            const Vector3Du& size = Vector3Du(),
            CUL::CnstMyStr& winName = "",
            const bool opengl = false);
        SDL2WrapperImpl( const SDL2WrapperImpl& rhv ) = delete;
        virtual ~SDL2WrapperImpl();

        SDL2WrapperImpl& operator=( const SDL2WrapperImpl& rhv ) = delete;

        void refreshScreen() override;
        void renderFrame( 
            const bool clearContext = true,
            const bool refreshWindow = true ) override;
        void clearWindows() override;
        void runEventLoop() override;
        void stopEventLoop() override;

        void addKeyboardEventCallback( 
            const std::function<void( const IKey& key )>& callback ) override;

        void registerKeyboardEventListener( 
            IKeyboardObserver* observer ) override;
        void unregisterKeyboardEventListener( IKeyboardObserver* observer ) override;

        void registerWindowEventListener( 
            IWindowEventObserver* observer ) override;
        void unregisterWindowEventListener( 
            IWindowEventObserver* observer ) override;

        cunt getInputLatency()const override;
        void setInputLatency( const unsigned int latencyInUs ) override;
        const bool isKeyUp( CUL::CnstMyStr& keyName )const;
        Keys& getKeyStates() override;

        IWindowFactory* getWindowFactory() override;

        ITexture* createTexture( const Path& path,
                                 IWindow* targetWindow ) override;
        ISprite* createSprite( const Path& path,
                               IWindow* targetWindow ) override;
        ISprite* createSprite( ITexture* tex,
                               IWindow* targetWindow ) override;

        IWindow* getMainWindow() override;

    protected:
    private:
        void createKeys();
        IKey* createKey( const int keySignature, const unsigned char* sdlKey )const;
        void notifyKeyboardCallbacks( const IKey& key );
        void notifyKeyboardListeners( const IKey& key );
        void notifyWindowEventListeners( const WindowEventType e );
        void handleEveent( const SDL_Event& event );
        const bool eventIsMouseEvent( const SDL_Event& event );
        void handleKeyboardEvent( const SDL_Event& sdlEvent );
        void handleMouseEvent( const SDL_Event& sdlEvent );

        WindowCreatorConcrete* m_windowFactory = nullptr;

        CUL::LckPrim<bool> eventLoopActive{ true };
        CUL::LckPrim<unsigned int> m_eventLatencyUs{ 256 };

        Keys m_keys;
        std::vector<std::function<void( const IKey& key )>> m_keyCallbacks;
        std::set<IKeyboardObserver*> m_keyboardObservers;
        std::set<IWindowEventObserver*> m_windowEventObservers;
        WindowCollection* m_windows = nullptr;
        IWindow* m_mainWindow = nullptr;
        std::shared_ptr<IThreadUtil> m_threadUtil;

    };
}