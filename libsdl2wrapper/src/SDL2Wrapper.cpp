#include "SDL2Wrapper\SDL2Wrapper.hpp"
#include "SDL2WrapperImpl.hpp"
namespace SDL2W
{
	ISDL2Wrapper* sdlWrapper = nullptr;

	ISDL2Wrapper* getSDL2Wrapper()
	{
		if(nullptr == sdlWrapper)
		{
			sdlWrapper = new SDL2WrapperImpl();
		}
		return sdlWrapper;
	}
}