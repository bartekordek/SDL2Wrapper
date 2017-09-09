#pragma once
#include "SDL2Wrapper/SDL2Wrapper.hpp"
#include "SDL2Wrapper/IWindow.hpp"
#include <memory>
namespace SDL2W
{
	class SDL2WrapperAPI ISDL2Wrapper
	{
	public:
		ISDL2Wrapper();
		virtual ~ISDL2Wrapper();
		virtual std::shared_ptr<IWindow> createWindow(
			const CUL::XYPosition<int>& pos = CUL::XYPosition<int>(),
			const CUL::Size<unsigned>& size = CUL::Size<unsigned>(),
			const std::string& winName = "" ) = 0;
		virtual void refreshScreen() = 0;
		virtual void renderFrame() = 0;

	protected:
	private:
	};

	SDL2WrapperAPI ISDL2Wrapper* getSDL2Wrapper();
}