#pragma once
#include <SDL_render.h>
#include <memory>
#include <mutex>
namespace SDL2W
{
    class TextureWrapper
    {
    public:
        TextureWrapper();
        virtual ~TextureWrapper();
        const SDL_Texture* getTexture()const;
        void setTexture( const SDL_Texture* texture );
    protected:
    private:
        mutable std::mutex m_textureLock;
        SDL_Texture* m_texture = nullptr;
    };
}