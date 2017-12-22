#include "SDL2Wrapper/ISDL2Wrapper.hpp"
#include "CUL/Math/XYPosition.hpp"
#include "CUL/Math/Size.hpp"
#include "CUL/FS.hpp"
#include <thread>
#include <cmath>
#include <iostream>

int main( int argc, char** argv )
{
	auto cwd = CUL::FS::FSApi::getCurrentDir();
	std::cout << "Working directory: " << cwd;
	auto file = CUL::FS::Path( "../media/pikaczu.bmp");
	if( file.exists() )
	{
		auto sdlW = SDL2W::getSDL2Wrapper();
		auto window = sdlW->createWindow( 
			CUL::XYPosition<int>( 256, 256 ), 
			CUL::Size<unsigned>( 800, 600 ), 
			"Windows 1" );

		auto obj1 = window->createObject( file );
		CUL::Math::Vector3Dd obj1Scale;
		obj1->setScale( obj1Scale );
		
		auto obj2 = window->createObject( file );
		
		CUL::Math::Vector3Di obj2Pos0( 450, 100, 0 ), obj2Pos;
		obj2->setPosition( obj2Pos0 );

		unsigned timeInSeconds = 60;
		unsigned iterations = 8192;
		auto sleepTimeS = static_cast<double>(
			timeInSeconds * 1.0 / iterations * 1.0 );
		unsigned sleepTimeinMs = static_cast<unsigned>( 1000 * sleepTimeS );
		
		for( double i = 0; i < timeInSeconds; i += sleepTimeS )
		{
			sdlW->renderFrame();
			std::this_thread::sleep_for(
				std::chrono::milliseconds( sleepTimeinMs ) );
			auto xScale = (sin( i ) + 1.0) * 0.5;
			auto yScale = (cos( i ) + 1.0) * 0.5;
			obj1Scale.setXYZ( xScale, yScale, 0 );
			obj1->setScale( obj1Scale );

			auto amp = 64;
			obj2Pos.setX( static_cast<const int>( obj2Pos0.getX() + sin( i ) * amp ) );
			obj2Pos.setY( static_cast<const int>( obj2Pos0.getY() + cos( i ) * amp ) );
			obj2->setPosition( obj2Pos );
		}
		return 0;
	}
	return 1;
}
