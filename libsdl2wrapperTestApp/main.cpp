#include "SDL2Wrapper/ISDL2Wrapper.hpp"

#include "CUL/FS.hpp"
#include "CUL/LckPrim.hpp"
#include <thread>
#include <cmath>
#include <iostream>

class TestApp final: private SDL2W::IKeyboardObserver, private SDL2W::IWindowEventObserver
{
public:
    TestApp():
        m_sdlW( SDL2W::getSDL2Wrapper() )
    {
        auto window = this->m_sdlW->createWindow(
            CUL::Math::Vector3Di( 256, 256, 0 ),
            CUL::Math::Vector3Du( 800, 600, 0 ),
            "Windows 1" );

        if( this->m_someFile.exists() )
        {
            this->m_obj1 = window->createObject( this->m_someFile ).get();
            this->m_obj2 = window->createObject( this->m_someFile ).get();
            //this->m_obj3 = window->createObject( this->m_someFile ).get().get();
            this->m_obj4 = window->createObject( this->m_someFile ).get();
            this->obj4Pos = this->m_obj4->getPosition();
        }
    }

    ~TestApp()
    {
        if( this->m_thread.joinable() )
        {
            this->m_thread.join();
        }
        SDL2W::destroySDL2Wrapper();
    }

    void runMainLoop()
    {
        this->m_sdlW->registerKeyboardEventListener( this );
        this->m_sdlW->registerWindowEventListener( this );
        m_thread = std::thread( &TestApp::objectManagmentFun, this );
        this->m_sdlW->runEventLoop();
    }

    void onKeyBoardEvent( const SDL2W::IKey& key ) override
    {
        if( false == key.getKeyIsDown() )
        {
            return;
        }
        std::cout << "KEY: " << key.getKeyName() << "\n";

        static int delta = 8;
        if( "D" == key.getKeyName() )
        {
            this->obj4Pos.setX( this->obj4Pos.getX() + delta );
        }
        else if( "A" == key.getKeyName() )
        {
            this->obj4Pos.setX( this->obj4Pos.getX() - delta );
        }
        else if( "W" == key.getKeyName() )
        {
            this->obj4Pos.setY( this->obj4Pos.getY() - delta );
        }
        else if( "S" == key.getKeyName() )
        {
            this->obj4Pos.setY( this->obj4Pos.getY() + delta );
        }
        else if( ( key.getKeyName() == "q" ) || ( key.getKeyName() == "Q" ) )
        {
            this->m_sdlW->stopEventLoop();
            this->runLoop = false;
        }

        std::cout
            << "OBJ4 Pos( "
            << this->obj4Pos.getX() << ", "
            << this->obj4Pos.getY() << " )\n";
    }

    void onWindowEvent( const WindowEventType e )
    {
        std::cout << "WAT!!\n";
    }

protected:
private:
    void objectManagmentFun()
    {
        if( this->m_someFile.exists() )
        {
            CUL::Math::Vector3Dd obj1Scale;
            this->m_obj1->setScale( obj1Scale );

            CUL::Math::Vector3Di obj2Pos0( 450, 100, 0 ), obj2Pos;
            this->m_obj2->setPosition( obj2Pos0 );

            CUL::Math::Vector3Dd obj4Scale( 0.25, 0.25, 0.0 );
            this->m_obj4->setScale( obj4Scale );

            this->m_obj4->setPosition( CUL::Math::Vector3Di( 300, 300, 0 ) );

            unsigned sleepTimeinMs = 8;
            double i = 0.0;

            while( this->runLoop )
            {
                this->m_sdlW->renderFrame();
                std::this_thread::sleep_for(
                    std::chrono::milliseconds( sleepTimeinMs ) );
                auto xScale = ( sin( i ) + 1.0 ) * 0.5;
                auto yScale = ( cos( i ) + 1.0 ) * 0.5;
                obj1Scale.setXYZ( xScale, yScale, 0 );
                this->m_obj1->setScale( obj1Scale );
                this->m_obj4->setPosition( this->obj4Pos );

                auto amp = 64;
                obj2Pos.setX( static_cast< const int >( obj2Pos0.getX() + sin( i ) * amp ) );
                obj2Pos.setY( static_cast< const int >( obj2Pos0.getY() + cos( i ) * amp ) );
                this->m_obj2->setPosition( obj2Pos );
                i += 0.02;
            }
        }
    }

    CUL::LckPrim<bool> runLoop{ true };

    SDL2W::ISDL2Wrapper* m_sdlW = nullptr;

    std::thread m_thread;

    CUL::FS::Path m_someFile = CUL::FS::Path( "../media/pikaczu.bmp" );

    SDL2W::IObject* m_obj1 = nullptr;
    SDL2W::IObject* m_obj2 = nullptr;
    //std::shared_ptr<SDL2W::IObject> m_obj3;
    SDL2W::IObject* m_obj4;

    CUL::Math::Vector3Dd obj1Scale;
    CUL::Math::Vector3Di obj2Pos0;
    CUL::Math::Vector3Di obj4Pos;
};

int main( int argc, char** argv )
{
    TestApp testApp;
    testApp.runMainLoop();
    return 0;
}