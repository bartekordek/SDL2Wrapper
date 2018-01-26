#include "SDL2Wrapper/ISDL2Wrapper.hpp"

#include "CUL/FS.hpp"
#include "CUL/LckPrim.hpp"
#include <thread>
#include <cmath>
#include <iostream>

class TestApp: public SDL2W::IKeyboardObserver
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
            this->m_obj1 = window->createObject( this->m_someFile );
            this->m_obj2 = window->createObject( this->m_someFile );
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
        m_thread = std::thread( &TestApp::objectManagmentFun, this );
        this->m_sdlW->runEventLoop();
    }

    void onKeyBoardEvent( const SDL2W::IKey& key ) override
    {
        if( false == key.getKeyIsDown() )
        {
            return;
        }

        std::cout << "WTF!!\n";
        if( ( key.getKeyName() == "q" ) || ( key.getKeyName() == "Q" ) )
        {
            this->m_sdlW->stopEventLoop();
            this->runLoop = false;
        }
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

            unsigned timeInSeconds = 60;
            unsigned iterations = 8192;
            auto sleepTimeS = static_cast< double >(
                timeInSeconds * 1.0 / iterations * 1.0 );
            unsigned sleepTimeinMs = static_cast< unsigned >( 1000 * sleepTimeS );
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

                auto amp = 64;
                obj2Pos.setX( static_cast< const int >( obj2Pos0.getX() + sin( i ) * amp ) );
                obj2Pos.setY( static_cast< const int >( obj2Pos0.getY() + cos( i ) * amp ) );
                this->m_obj2->setPosition( obj2Pos );
                i += sleepTimeS;
            }
        }
    }

    CUL::LckPrim<bool> runLoop{ true };

    SDL2W::ISDL2Wrapper* m_sdlW = nullptr;

    std::thread m_thread;

    CUL::FS::Path m_someFile = CUL::FS::Path( "../media/pikaczu.bmp" );

    std::shared_ptr<SDL2W::IObject> m_obj1;
    std::shared_ptr<SDL2W::IObject> m_obj2;

    CUL::Math::Vector3Dd obj1Scale;
    CUL::Math::Vector3Di obj2Pos0;
};

int main( int argc, char** argv )
{
    TestApp testApp;
    testApp.runMainLoop();
    return 0;
}