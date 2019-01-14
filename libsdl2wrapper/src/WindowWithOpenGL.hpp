#pragma once

#include "SDL2Wrapper/IWindow.hpp"
#include "SDL2Wrapper/IRender.hpp"

#include "CUL/STD_memory.hpp"
#include "CUL/STD_set.hpp"
#include "CUL/STD_mutex.hpp"
#include "CUL/Video/IFPSCounter.hpp"
#include "CUL/LckPrim.hpp"

#include "SDL2Wrapper/IMPORT_SDL_video.hpp"

struct SDL_Window;
struct SDL_Renderer;
struct SDL_Surface;

namespace SDL2W
{
    class WindowWithOpenGL:
        public IWindow
    {
    public:
        WindowWithOpenGL() = delete;
        WindowWithOpenGL(
            const Vector3Di& pos,
            const Vector3Du& size,
            CUL::CnstMyStr& name );
        WindowWithOpenGL( const WindowWithOpenGL& win ) = delete;
        virtual ~WindowWithOpenGL();

        WindowWithOpenGL& operator=(
            const WindowWithOpenGL& right ) = delete;

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

        SDL_Window* getSDLWindow()const override;

    protected:
    private:
        SDL_Surface * createSurface( const Path& path );
        ITexture* createTexture( SDL_Surface* surface, const Path& path );

        // Inherited via IWindow
        void addObject( IObject * object ) override;
        void removeObject( IObject * object ) override;

        ColorS m_backgroundColor;
        SDL_Window* m_window = nullptr;
        SDL_Renderer* m_renderer = nullptr;
        
        std::set<IObject*> m_objects;
        std::mutex m_objectsMtx;
        TextureMap m_textures;
        CUL::LckPrim<bool> m_updateBuffers { true };

        Vector3Di m_position;
        Vector3Du m_size;
    };
}