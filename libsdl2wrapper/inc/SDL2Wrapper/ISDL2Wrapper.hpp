#pragma once
#include "SDL2Wrapper/SDL2Wrapper.hpp"
#include "SDL2Wrapper/IWindow.hpp"
#include "SDL2Wrapper/IKey.hpp"
#include <memory>
#include <functional>
namespace SDL2W
{
    class SDL2WrapperAPI ISDL2Wrapper
    {
    public:
        ISDL2Wrapper();
        virtual ~ISDL2Wrapper();
        virtual std::shared_ptr<IWindow> createWindow(
            const CUL::Position2D<int>& pos = CUL::Position2D<int>(),
            const CUL::Size<unsigned>& size = CUL::Size<unsigned>(),
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
        virtual void addKeyboardEventCallback( const std::function<void( const IKey& key )>& callback ) = 0;

    protected:
    private:
    };

    SDL2WrapperAPI ISDL2Wrapper* getSDL2Wrapper();
    SDL2WrapperAPI void destroySDL2Wrapper();
}