#include "SDL2Wrapper/ISDL2Wrapper.hpp"
#include "CUL/Math/XYPosition.hpp"
#include "CUL/Math/Size.hpp"
#include "CUL/FS.hpp"
#include "CUL/LckPrim.hpp"
#include <thread>
#include <cmath>
#include <iostream>

auto file = CUL::FS::Path( "../media/pikaczu.bmp" );
void objectManagmentFun( SDL2W::IObject*, SDL2W::IObject* );
SDL2W::ISDL2Wrapper* sdlW = nullptr;

void keyCallback( const SDL2W::IKey& key );
CUL::LckPrim<bool> runLoop{ true };

int main( int argc, char** argv )
{
    auto cwd = CUL::FS::FSApi::getCurrentDir();
    std::cout << "Working directory: " << cwd;
    if( file.exists() )
    {
        sdlW = SDL2W::getSDL2Wrapper();
        auto window = sdlW->createWindow(
            CUL::Position2D<int>( 256, 256 ),
            CUL::Size<unsigned>( 800, 600 ),
            "Windows 1" );

        auto obj1 = window->createObject( file );
        auto obj2 = window->createObject( file );

        std::thread objectsThread( objectManagmentFun, obj1.get(), obj2.get() );

        sdlW->addKeyboardEventCallback( keyCallback );
        sdlW->runEventLoop();

        objectsThread.join();
        SDL2W::destroySDL2Wrapper();
    }
    return 0;
}

void objectManagmentFun( SDL2W::IObject* obj1, SDL2W::IObject* obj2 )
{
    CUL::Math::Vector3Dd obj1Scale;
    obj1->setScale( obj1Scale );

    CUL::Math::Vector3Di obj2Pos0( 450, 100, 0 ), obj2Pos;
    obj2->setPosition( obj2Pos0 );

    unsigned timeInSeconds = 60;
    unsigned iterations = 8192;
    auto sleepTimeS = static_cast<double>(
        timeInSeconds * 1.0 / iterations * 1.0 );
    unsigned sleepTimeinMs = static_cast<unsigned>( 1000 * sleepTimeS );
    double i = 0.0;

    while( runLoop )
    {
        sdlW->renderFrame();
        std::this_thread::sleep_for(
            std::chrono::milliseconds( sleepTimeinMs ) );
        auto xScale = ( sin( i ) + 1.0 ) * 0.5;
        auto yScale = ( cos( i ) + 1.0 ) * 0.5;
        obj1Scale.setXYZ( xScale, yScale, 0 );
        obj1->setScale( obj1Scale );

        auto amp = 64;
        obj2Pos.setX( static_cast<const int>( obj2Pos0.getX() + sin( i ) * amp ) );
        obj2Pos.setY( static_cast<const int>( obj2Pos0.getY() + cos( i ) * amp ) );
        obj2->setPosition( obj2Pos );
        i += sleepTimeS;
    }
}

void keyCallback( const SDL2W::IKey& key )
{
    std::cout << "WTF";
    if( ( key.getKeyName() == "q" ) || ( key.getKeyName() == "Q" ) )
    {
        sdlW->stopEventLoop();
        runLoop = false;
    }
}