#pragma once
#include "SDL2Wrapper/ISDL2Wrapper.hpp"
#include "SDL2Wrapper/IWindow.hpp"
#include <map>
struct SDL_Surface;
namespace SDL2W
{
	class SDL2WrapperImpl: public ISDL2Wrapper
	{
	public:
		SDL2WrapperImpl();
		virtual ~SDL2WrapperImpl();

		std::shared_ptr<IWindow> createWindow( 
			const CUL::XYPosition<int>& pos = CUL::XYPosition<int>(),
			const CUL::Size<unsigned>& size = CUL::Size<unsigned>(),
			const std::string& winName = "" ) override;

		void refreshScreen() override;
		void renderFrame() override;

	protected:
	private:
		std::map<std::string, std::shared_ptr<IWindow>> windows;
	};
}