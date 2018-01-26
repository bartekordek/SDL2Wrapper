#pragma once
#include "SDL2Wrapper/IWindow.hpp"
#include "CUL/IList.hpp"
#include <string>
#include <memory>
struct SDL_Window;
struct SDL_Renderer;
struct SDL_Surface;
namespace SDL2W
{
    class RegularSDL2Window: public IWindow
    {
    public:
        RegularSDL2Window( 
            const CUL::Math::Vector3Di& pos,
            const CUL::Math::Vector3Du& size,
            const std::string& name );
        RegularSDL2Window( const RegularSDL2Window& win );
        RegularSDL2Window() = delete;
        virtual ~RegularSDL2Window();

        RegularSDL2Window& operator=( const RegularSDL2Window& right );

        std::shared_ptr<IObject> createObject(
            const CUL::FS::Path& objPath,
            const IObject::Type type = IObject::Type::SPRITE ) const override;

        void renderNext() override;

        void refreshScreen() override;
        void renderAllObjects() override;
        void clear() override;
            
    protected:
    private:
        static SDL_Surface* createSurface( const CUL::FS::Path& path );

        static void windowDeleter( SDL_Window* win );
        static void rendererDeleter( SDL_Renderer* rend );
        std::shared_ptr<SDL_Window> window;
        std::shared_ptr<SDL_Renderer> renderer;
        std::shared_ptr<CUL::IList<std::shared_ptr<IObject>>> objects;

    };
}