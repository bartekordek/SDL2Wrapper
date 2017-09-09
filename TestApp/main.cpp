#include "SDL2Wrapper/ISDL2Wrapper.hpp"
//#include "CUL"
#include <thread>

int main( int argc, char** argv )
{
	auto sdlW = SDL2W::getSDL2Wrapper();
	auto window = sdlW->createWindow( CUL::XYPosition<int>( 500, 500 ), CUL::Size<unsigned>( 800, 600 ), "Windows 1" );
	
	window->createObject( CUL::FS::Path( "../../Media/pikaczu.bmp") );
	sdlW->renderFrame();
	sdlW->refreshScreen();
	std::this_thread::sleep_for( std::chrono::seconds( 4 ) );
}