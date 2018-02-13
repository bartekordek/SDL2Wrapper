#pragma once
#include "SDL2Wrapper/ITexture.hpp"
#include <SDL_render.h>
#include <memory>
#include <mutex>
namespace SDL2W
{
    class TextureSDL:
        public ITexture
    {
    public:
        TextureSDL();
        virtual ~TextureSDL();
        const SDL_Texture* getTexture()const;
        void setTexture( const SDL_Texture* texture, const Path& path );
        const Vector3Du& getSize()const override;
        const Path& getPath()const override;
    protected:
    private:
        SDL_Texture* m_texture = nullptr;
        Vector3Du m_size;
        Path m_path;
    };
}