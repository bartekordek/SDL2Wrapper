#pragma once
#include "SDL2Wrapper/SDL2Wrapper.hpp"
#include "SDL2Wrapper/IKey.hpp"
#include "SDL2Wrapper/IWindowEventListener.hpp"
#include "SDL2Wrapper/IKeyboardObservable.hpp"
#include "SDL2Wrapper/ITexture.hpp"
#include "SDL2Wrapper/ISprite.hpp"
#include "SDL2Wrapper/IWindowFactory.hpp"
#include "CUL/STD_memory.hpp"
#include "CUL/STD_map.hpp"

namespace SDL2W
{
    using cunt = const unsigned int;
    using Keys = std::map<std::string, std::unique_ptr<IKey>>;
    class SDL2WAPI ISDL2Wrapper:
        public IKeyboardObservable
    {
    public:
        ISDL2Wrapper();
        ISDL2Wrapper( const ISDL2Wrapper& rhv ) = delete;
        virtual ~ISDL2Wrapper();
        ISDL2Wrapper& operator=( const ISDL2Wrapper& rhv ) = delete;
        
        virtual void refreshScreen() = 0;
        virtual void renderFrame( 
            const bool clearContext = true,
            const bool refreshWindow = true ) = 0;
        virtual void clearWindows() = 0;

        virtual ITexture* createTexture( const Path& path,
                                         IWindow* targetWindow ) = 0;
        virtual ISprite* createSprite( const Path& path,
                                       IWindow* targetWindow ) = 0;
        virtual ISprite* createSprite( ITexture* tex,
                                       IWindow* targetWindow ) = 0;

        virtual IWindowFactory* getWindowFactory() = 0;

        /*
        * Should be run in main process.
        */
        virtual void runEventLoop() = 0;
        virtual void stopEventLoop() = 0;

        virtual void setInputLatency( cunt latencyInUs ) = 0;

        virtual void registerWindowEventListener(
            IWindowEventObserver* observer ) = 0;
        virtual void unregisterWindowEventListener(
            IWindowEventObserver* observer ) = 0;

        virtual Keys& getKeyStates() = 0;

    protected:
    private:
    };

    SDL2WAPI ISDL2Wrapper* createSDL2Wrapper( const Vector3Di& pos = Vector3Di(),
                                              const Vector3Du& size = Vector3Du( 800, 600, 0 ),
                                              CnstStr& winName = "" );
    SDL2WAPI ISDL2Wrapper* getSDL2Wrapper();
    void SDL2WAPI destroySDL2Wrapper();
}