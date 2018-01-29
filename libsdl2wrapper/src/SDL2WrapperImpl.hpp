#pragma once
#include "SDL2Wrapper/ISDL2Wrapper.hpp"
#include "SDL2Wrapper/IWindow.hpp"
#include "CUL/LckPrim.hpp"
#include <map>
#include <set>
#include <vector>
struct SDL_Surface;
namespace SDL2W
{
    using Keys = std::map<std::string, std::unique_ptr<IKey>>;
    using WindowEventType = IWindowEventObserver::WindowEventType;
    class SDL2WrapperImpl: public ISDL2Wrapper
    {
    public:
        SDL2WrapperImpl();
        virtual ~SDL2WrapperImpl();

        std::shared_ptr<IWindow> createWindow(
            const CUL::Math::Vector3Di& pos = CUL::Math::Vector3Di(),
            const CUL::Math::Vector3Du& size = CUL::Math::Vector3Du(),
            const std::string& winName = "" ) override;

        void refreshScreen() override;
        void renderFrame( 
            const bool clearContext = true,
            const bool refreshWindow = true ) override;
        void clearWindows() override;
        void runEventLoop() override;
        void stopEventLoop() override;

        void addKeyboardEventCallback( const std::function<void( const IKey& key )>& callback ) override;

        void registerKeyboardEventListener( IKeyboardObserver* observer ) override;
        void unregisterKeyboardEventListener( IKeyboardObserver* observer ) override;

        void registerWindowEventListener( IWindowEventObserver* observer ) override;
        void unregisterWindowEventListener( IWindowEventObserver* observer ) override;

        void setInputLatency( const unsigned int latencyInUs ) override;

        const bool isKeyUp( const std::string& keyName )const;

    protected:
    private:
        void createKeys();
        IKey* createKey( const int keySignature, const unsigned char* sdlKey )const;
        void notifyKeyboardCallbacks( const IKey& key );
        void notifyKeyboardListeners( const IKey& key );
        void notifyWindowEventListeners( const WindowEventType e );

        std::map<std::string, std::shared_ptr<IWindow>> windows;
        CUL::LckPrim<bool> eventLoopActive{ true };
        CUL::LckPrim<unsigned int> m_eventLatencyUs{ 256 };

        Keys m_keys;
        std::vector<std::function<void( const IKey& key )>> m_keyCallbacks;
        std::set<IKeyboardObserver*> m_keyboardObservers;
        std::set<IWindowEventObserver*> m_windowEventObservers;
    };
}