#include "TextureWrapper.hpp"

using namespace SDL2W;

TextureWrapper::TextureWrapper()
{

}

TextureWrapper::~TextureWrapper()
{
	std::lock_guard<std::mutex> lock( this->m_textureLock );
	SDL_DestroyTexture( this->m_texture );
	this->m_texture = nullptr;
}

const SDL_Texture* TextureWrapper::getTexture()const
{
	std::lock_guard<std::mutex> lock( this->m_textureLock );
	return this->m_texture;
}

void TextureWrapper::setTexture( const SDL_Texture* texture )
{
	std::lock_guard<std::mutex> lock( this->m_textureLock );
	this->m_texture = const_cast<SDL_Texture*>( texture );
}