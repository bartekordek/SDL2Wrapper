#pragma once

#include "SDL2Wrapper/Gui/IGui.hpp"
#include "SDL2Wrapper/IEventLoop.hpp"
#include "SDL2Wrapper/Input/IKey.hpp"
#include "SDL2Wrapper/IWindowEventListener.hpp"
#include "SDL2Wrapper/Input/IKeyboardObservable.hpp"
#include "SDL2Wrapper/Input/IMouseObservable.hpp"
#include "SDL2Wrapper/ISprite.hpp"
#include "SDL2Wrapper/IWindowFactory.hpp"
#include "CUL/Graphics/ITexture.hpp"
#include "CUL/ThreadUtils.hpp"
#include "CUL/STL_IMPORTS/STD_memory.hpp"
#include "CUL/STL_IMPORTS/STD_map.hpp"
#include "CUL/STL_IMPORTS/STD_functional.hpp"

NAMESPACE_BEGIN( SDL2W )

using Keys = std::map<CUL::String, std::unique_ptr<IKey>>;
using WindowEventType = WindowEvent::Type;
using Cbool = const bool;
using WindowCallback = std::function<void( const WindowEventType wEt )>;
using InitCallback = std::function<void()>;

class SDL2WAPI ISDL2Wrapper:
    public IKeyboardObservable,
    public IMouseObservable,
    public IEventLoop
{
public:
    ISDL2Wrapper();
    virtual ~ISDL2Wrapper();

    virtual void init( const WindowData& wd ) = 0;
    virtual void refreshScreen() = 0;
    virtual void renderFrame( Cbool clearContext = true, Cbool refreshWindow = true ) = 0;
    virtual void clearWindows() = 0;

    virtual ITexture* createTexture( const Path& path, IWindow* targetWindow ) = 0;
    virtual ISprite* createSprite( const Path& path, IWindow* targetWindow ) = 0;

    virtual ISprite* createSprite( ITexture* tex, IWindow* targetWindow ) = 0;

    virtual IWindow* getMainWindow() = 0;

    virtual Cunt getInputLatency()const = 0;
    virtual void setInputLatency( Cunt latencyInUs ) = 0;

    virtual void registerWindowEventListener( IWindowEventObserver* observer ) = 0;
    virtual void unregisterWindowEventListener( IWindowEventObserver* observer ) = 0;
    virtual void registerWindowEventCallback( const WindowCallback& callback) = 0;
    virtual void registerOnInitCallback( const InitCallback& callback ) = 0;

    virtual Keys& getKeyStates() = 0;

    virtual IGui* getGui() = 0;

protected:
private:

private: // Deleted
    ISDL2Wrapper( const ISDL2Wrapper& rhv ) = delete;
    ISDL2Wrapper& operator=( const ISDL2Wrapper& rhv ) = delete;

};

SDL2WAPI ISDL2Wrapper* createSDL2Wrapper();

NAMESPACE_END( SDL2W )