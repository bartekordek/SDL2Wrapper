#include "SDL2Wrapper/ISDL2Wrapper.hpp"
//#include "CUL"
#include <thread>

int main( int argc, char** argv )
{
	auto sdlW = SDL2W::getSDL2Wrapper();
	auto window = sdlW->createWindow( CUL::XYPosition<int>( 1922, 64 ), CUL::Size<unsigned>( 800, 600 ), "Windows 1" );
	
	auto obj = window->createObject( CUL::FS::Path( "../../Media/pikaczu.bmp") );
	obj->setScale( CUL::Math::Vector3Dd( 0.0, 0.0, 0.0 ) );

	unsigned ticks = 4096;
	double timeInSeconds = 60;
	auto tickTimeInMs = static_cast<unsigned>( 1000 * timeInSeconds / ticks );
	for( unsigned int i = 0; i < ticks; ++i )
	{
		sdlW->clearWindows();
		sdlW->renderFrame();
		sdlW->refreshScreen();
		std::this_thread::sleep_for( 
			std::chrono::milliseconds( 
				tickTimeInMs ) );
		obj->setScale( 
			CUL::Math::Vector3Dd( 4.0 * i / ticks, 4.0 * i / ticks, 0 ) );
	}

	return 0;
}