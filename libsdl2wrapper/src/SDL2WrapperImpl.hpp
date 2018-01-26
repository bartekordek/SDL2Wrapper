#pragma once
#include "SDL2Wrapper/ISDL2Wrapper.hpp"
#include "SDL2Wrapper/IWindow.hpp"
#include "CUL/LckPrim.hpp"
#include <map>
#include <vector>
struct SDL_Surface;
namespace SDL2W
{
    using Keys = std::map<unsigned int, std::unique_ptr<IKey>>;
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

    protected:
    private:
        void createKeys();
        IKey* createKey( const int keySignature, const unsigned char* sdlKey )const;
        void notifyCallbacks( const IKey& key );

        std::map<std::string, std::shared_ptr<IWindow>> windows;
        CUL::LckPrim<bool> eventLoopActive{ true };
        Keys m_keys;
        std::vector<std::function<void( const IKey& key )>> m_keyCallbacks;
    };
}