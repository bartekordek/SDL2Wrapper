#pragma once
#include "SDL2Wrapper/IWindow.hpp"
#include <string>
#include <memory>
#include <map>
struct SDL_Window;
struct SDL_Renderer;
struct SDL_Surface;
namespace SDL2W
{
    class RegularSDL2Window:
        public IWindow
    {
    public:
        RegularSDL2Window( 
            const Vector3Di& pos,
            const Vector3Du& size,
            const std::string& name );
        RegularSDL2Window( const RegularSDL2Window& win );
        RegularSDL2Window() = delete;
        virtual ~RegularSDL2Window();

        RegularSDL2Window& operator=( const RegularSDL2Window& right );

        IObject* createObject( const Path& objPath ) override;
        ITexture* createTexture( const Path& objPath ) override;
        IObject* createObject( const ITexture* tex ) override;

        void renderNext() override;

        void refreshScreen() override;
        void renderAllObjects() override;
        void clear() override;

        void setBackgroundColor( const ColorE color ) override;
        void setBackgroundColor( const ColorS& color ) override;

    protected:
    private:
        static SDL_Surface* createSurface( const Path& path );
        ITexture* createTexture( SDL_Surface* surface, const Path& path );

        ColorS m_backgroundColor;
        static void windowDeleter( SDL_Window* win );
        static void rendererDeleter( SDL_Renderer* rend );
        std::shared_ptr<SDL_Window> window;
        std::shared_ptr<SDL_Renderer> renderer;
        std::map<IObject*, std::shared_ptr<IObject>> objects;
        std::map<const char*, std::shared_ptr<ITexture>> m_textures;

    };
}