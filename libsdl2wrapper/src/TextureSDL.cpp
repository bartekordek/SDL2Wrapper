#include "TextureSDL.hpp"
#include "CUL/SimpleAssert.hpp"

using namespace SDL2W;

TextureSDL::TextureSDL()
{

}

TextureSDL::~TextureSDL()
{
    SDL_DestroyTexture( this->m_texture );
    this->m_texture = nullptr;
}

SDL_Texture* TextureSDL::getTexture()const
{
    return this->m_texture;
}

void TextureSDL::setTexture( const SDL_Texture* texture, const Path& path )
{
    this->m_texture = const_cast<SDL_Texture*>( texture );
    int w, h;
    const auto sdlQuerySuccess = SDL_QueryTexture(
        this->m_texture,
        nullptr,
        nullptr,
        &w,
        &h );
    CUL::Assert::simple(
        0 == sdlQuerySuccess,
        "Cannot initialize SDL subsystem" );
    this->m_size.setX( static_cast<unsigned>( w ) );
    this->m_size.setY( static_cast<unsigned>( h ) );
    this->m_path = path;
}

const Vector3Dd& TextureSDL::getSize()const
{
    return this->m_size;
}

const Path& TextureSDL::getPath()const
{
    return this->m_path;
}