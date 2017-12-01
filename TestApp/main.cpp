#include "SDL2Wrapper/ISDL2Wrapper.hpp"
#include "CUL/Math/XYPosition.hpp"
#include "CUL/Math/Size.hpp"
#include <thread>
#include <cmath>

int main( int argc, char** argv )
{
    auto sdlW = SDL2W::getSDL2Wrapper();
    auto window = sdlW->createWindow( 
        CUL::XYPosition<int>( 256, 256 ), 
        CUL::Size<unsigned>( 800, 600 ), 
        "Windows 1" );
    
    
    auto obj = window->createObject( CUL::FS::Path( "../../Media/pikaczu.bmp") );
    obj->setScale( CUL::Math::Vector3Dd( 0.0, 0.0, 0.0 ) );

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
        obj->setScale(
            CUL::Math::Vector3Dd( xScale, yScale, 0 ) );
    }
    return 0;
}