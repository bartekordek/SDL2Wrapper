#pragma once

#include "CUL/Graphics/ITexture.hpp"
#include "SDL2Wrapper/IMPORT_SDL_renderer.hpp"
#include <CUL/STD_memory.hpp>
#include <CUL/STD_mutex.hpp>

NAMESPACE_BEGIN( SDL2W )

using ITexture = CUL::Graphics::ITexture;
using Path = CUL::FS::Path;
using Vector3Dd = CUL::Math::Vector3Dd;

#ifdef _MSC_VER
#pragma warning( push )
#pragma warning( disable: 4820 )
#endif

class TextureSDL:
    public ITexture
{
public:
    TextureSDL();
    TextureSDL( const TextureSDL& val ) = delete;
    virtual ~TextureSDL();

    TextureSDL& operator=( const TextureSDL& val ) = delete;

    SDL_Texture* getTexture()const;
    void setTexture(
        const SDL_Texture* texture,
        const Path& path );
    const Vector3Dd& getSize()const override;
    const Path& getPath()const override;
protected:
private:
    SDL_Texture* m_texture = nullptr;
    Vector3Dd m_size;
    Path m_path;
};

#ifdef _MSC_VER
#pragma warning( pop )
#endif

NAMESPACE_END( CUL )