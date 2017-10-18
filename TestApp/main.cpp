#include "SDL2Wrapper/ISDL2Wrapper.hpp"
//#include "CUL"
#include <thread>

int main( int argc, char** argv )
{
	auto sdlW = SDL2W::getSDL2Wrapper();
	auto window = sdlW->createWindow( CUL::XYPosition<int>( 500, 500 ), CUL::Size<unsigned>( 800, 600 ), "Windows 1" );
	
	auto obj = window->createObject( CUL::FS::Path( "../../Media/pikaczu.bmp") );

	unsigned ticks = 128;
	double timeInSeconds = 60;
	auto tickTimeInMs = static_cast<unsigned>( 1000 * timeInSeconds / ticks );
	for( unsigned int i = 0; i < ticks; ++i )
	{
		sdlW->renderFrame();
		sdlW->refreshScreen();
		std::this_thread::sleep_for( 
			std::chrono::milliseconds( 
				tickTimeInMs ) );
		obj->setScale( 
			CUL::Math::Vector3Du( i / ticks, i / ticks, 0 ) );
	}

	return 0;
}