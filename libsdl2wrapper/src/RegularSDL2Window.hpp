#pragma once

#include "SDL2Wrapper/IWindow.hpp"
#include "SDL2Wrapper/IRender.hpp"

#include "CUL/STD_memory.hpp"
#include "CUL/STD_set.hpp"
#include "CUL/STD_map.hpp"
#include "CUL/STD_mutex.hpp"

struct SDL_Window;
struct SDL_Renderer;
struct SDL_Surface;

namespace SDL2W
{
    using TextureMap = std::map<std::string, std::unique_ptr<ITexture>>;
    class RegularSDL2Window:
        public IWindow
    {
    public:
        RegularSDL2Window() = delete;
        RegularSDL2Window(
            const Vector3Di& pos,
            const Vector3Du& size,
            CnstStr& name );
        RegularSDL2Window( const RegularSDL2Window& win ) = delete;
        virtual ~RegularSDL2Window();

        RegularSDL2Window& operator=(
            const RegularSDL2Window& right ) = delete;


        const Vector3Di& getPos()const override;
        void setPos( const Vector3Di& pos ) override;

        const Vector3Du& getSize()const override;
        void setSize( const Vector3Du& size ) override;

        void setBackgroundColor( const ColorE color ) override;
        void setBackgroundColor( const ColorS& color ) override;
        void clearBuffers() override;
        void renderAll() override;
        void updateScreenBuffers() override;

        const IWindow::Type getType() const override;

        ITexture* createTexture( const Path& path ) override;
        ISprite* createSprite( const Path& path ) override;
        ISprite* createSprite( ITexture* tex ) override;

        const ColorS getBackgroundColor()const override;

    protected:
    private:
        SDL_Surface * createSurface( const Path& path );
        ITexture* createTexture( SDL_Surface* surface, const Path& path );

        // Inherited via IWindow
        virtual void addObject( IObject * object ) override;
        virtual void removeObject( IObject * object ) override;

        ColorS m_backgroundColor;
        SDL_Window* m_window = nullptr;
        SDL_Renderer* m_renderer = nullptr;
        std::set<IObject*> m_objects;
        std::mutex m_objectsMtx;
        TextureMap m_textures;

        Vector3Di m_position;
        Vector3Du m_size;
    };
}