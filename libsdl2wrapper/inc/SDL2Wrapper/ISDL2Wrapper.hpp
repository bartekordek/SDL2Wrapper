#pragma once
#include "SDL2Wrapper/SDL2Wrapper.hpp"
#include "SDL2Wrapper/IWindow.hpp"
#include "SDL2Wrapper/IKey.hpp"
#include "SDL2Wrapper/IWindowEventListener.hpp"
#include "SDL2Wrapper/IKeyboardObservable.hpp"
#include <memory>
#include <map>

namespace SDL2W
{
    using Keys = std::map<std::string, std::unique_ptr<IKey>>;
    class SDL2WrapperAPI ISDL2Wrapper: public IKeyboardObservable
    {
    public:
        ISDL2Wrapper();
        virtual ~ISDL2Wrapper();
        virtual IWindow* createWindow(
            const CUL::Math::Vector3Di& pos = CUL::Math::Vector3Di(),
            const CUL::Math::Vector3Du& size = CUL::Math::Vector3Du(),
            const std::string& winName = "" ) = 0;
        virtual void refreshScreen() = 0;
        virtual void renderFrame( 
            const bool clearContext = true,
            const bool refreshWindow = true ) = 0;
        virtual void clearWindows() = 0;

        /*
        * Should be run in main process.
        */
        virtual void runEventLoop() = 0;
        virtual void stopEventLoop() = 0;

        virtual void setInputLatency( const unsigned int latencyInUs ) = 0;

        virtual void registerWindowEventListener( IWindowEventObserver* observer ) = 0;
        virtual void unregisterWindowEventListener( IWindowEventObserver* observer ) = 0;

        virtual Keys& getKeyStates() = 0;

    protected:
    private:
    };

    SDL2WrapperAPI ISDL2Wrapper* getSDL2Wrapper();
    SDL2WrapperAPI void destroySDL2Wrapper();
}