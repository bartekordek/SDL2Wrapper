#pragma once
#include "SDL2Wrapper/ISDL2Wrapper.hpp"
#include "SDL2Wrapper/IWindow.hpp"
#include "CUL/LckPrim.hpp"
#include <map>
#include <vector>
struct SDL_Surface;
namespace SDL2W
{
    class SDL2WrapperImpl: public ISDL2Wrapper
    {
    public:
        SDL2WrapperImpl();
        virtual ~SDL2WrapperImpl();

        std::shared_ptr<IWindow> createWindow( 
            const CUL::Position2D<int>& pos = CUL::Position2D<int>(),
            const CUL::Size<unsigned>& size = CUL::Size<unsigned>(),
            const std::string& winName = "" ) override;

        void refreshScreen() override;
        void renderFrame( 
            const bool clearContext = true,
            const bool refreshWindow = true ) override;
        void clearWindows() override;
        void runEventLoop() override;
        void stopEventLoop() override;

        void addKeyboardEventCallback( const std::function<void( const IKey& key )>& callback ) override;

    protected:
    private:
        const std::map<unsigned int, std::shared_ptr<IKey>> createKeys()const;
        IKey* createKey( const int keySignature, const unsigned char* sdlKey )const;
        void notifyCallbacks( const IKey& key );

        std::map<std::string, std::shared_ptr<IWindow>> windows;
        CUL::LckPrim<bool> eventLoopActive{ true };
        std::map<unsigned int, std::shared_ptr<IKey>> m_keys;
        std::vector<std::function<void( const IKey& key )>> m_keyCallbacks;
    };
}