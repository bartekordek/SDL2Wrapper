#include "SDL2Wrapper/ISDL2Wrapper.hpp"

#include "CUL/FS.hpp"
#include "CUL/LckPrim.hpp"
#include "CUL/Math/Degree.hpp"
#include "CUL/STD_thread.hpp"
#include "CUL/STD_cmath.hpp"
#include "CUL/STD_iostream.hpp"

class TestApp final: 
    public SDL2W::IKeyboardObserver, 
    private SDL2W::IWindowEventObserver
{
public:
    TestApp():
        m_sdlW( SDL2W::createSDL2Wrapper( SDL2W::Vector3Di( 200, 200, 0 ) ) )
    {
        this->m_windowFactory = this->m_sdlW->getWindowFactory();
        this->m_activeWindow = this->m_windowFactory->getMainWindow();
 
        if( this->m_someFile.exists() )
        {
            this->m_obj1 = m_sdlW->createSprite( this->m_someFile, this->m_activeWindow );
            this->m_obj2 = m_sdlW->createSprite( this->m_someFile, this->m_activeWindow );
            this->m_obj3 = m_sdlW->createSprite( this->m_someFile, this->m_activeWindow );
            this->m_obj4 = m_sdlW->createSprite( this->m_someFile, this->m_activeWindow );
            this->obj4Pos = this->m_obj4->getPosition();
        }
        this->m_keyObservable = this->m_sdlW;
    }

    TestApp( const TestApp& rhv ) = delete;

    ~TestApp()
    {
        if( this->m_thread.joinable() )
        {
            this->m_thread.join();
        }
        SDL2W::destroySDL2Wrapper();
    }

    TestApp& operator=( const TestApp& rhv ) = delete;

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


        if( m_keyObservable->isKeyUp( "D" ) )
        {
            this->obj4Pos.setX( this->obj4Pos.getX() + delta );
        }

        if( m_keyObservable->isKeyUp( "A" ) )
        {
            this->obj4Pos.setX( this->obj4Pos.getX() - delta );
        }
        
        if( m_keyObservable->isKeyUp( "W" ) )
        {
            this->obj4Pos.setY( this->obj4Pos.getY() - delta );
        }

        if( m_keyObservable->isKeyUp( "S" ) )
        {
            this->obj4Pos.setY( this->obj4Pos.getY() + delta );
        }

        if( ( key.getKeyName() == "q" ) || ( key.getKeyName() == "Q" ) )
        {
            this->m_sdlW->stopEventLoop();
            this->runLoop = false;
        }
    }

    void onWindowEvent( const WindowEventType windowEventType ) override
    {
        std::cout << "Event Type: " << static_cast<short>( windowEventType ) << "WAT!!\n";
    }

protected:
private:
    void objectManagmentFun()
    {
        if( this->m_someFile.exists() )
        {
            CUL::Math::Vector3Dd someScale;
            this->m_obj1->setScale( someScale );

            this->obj3Pos.setXYZ( 300, 300, 0 );

            CUL::Math::Vector3Di obj1Pos( 100, 100, 0 );
            CUL::Math::Vector3Di somePosition1( 450, 100, 0 );
            CUL::Math::Vector3Di somePosition2( 600, 600, 0 );
            CUL::Math::Vector3Di somePosition3( 800, 500, 0 );
            CUL::Math::Vector3Di obj2Pos;
            this->m_obj1->setPosition( obj1Pos );
            this->m_obj2->setPosition( somePosition2 );
            this->m_obj3->setPivotX( 0.1 );
            this->m_obj3->setPosition( somePosition3 );
            someScale.setXYZ( 0.5, 0.5, 0.0 );
            this->m_obj3->setScale( someScale );

            unsigned sleepTimeinMs = 18;
            double i = 0.0;
            CUL::Math::Degree obj2Angle;
            CUL::Math::Degree obj3Angle;

            while( this->runLoop )
            {
                this->m_sdlW->renderFrame();
                std::this_thread::sleep_for(
                    std::chrono::milliseconds( sleepTimeinMs ) );
                auto xScale = ( sin( i ) + 1.0 ) * 0.25;
                auto yScale = ( cos( i ) + 1.0 ) * 0.25;
                someScale.setXYZ( xScale, yScale, 0 );
                this->m_obj1->setScale( someScale );
                this->m_obj2->setScale( someScale );
                this->m_obj2->rotate( obj2Angle );
                this->m_obj3->rotate( obj3Angle );

                this->m_obj4->setPosition( this->obj4Pos );

                obj2Angle -= 1;
                obj3Angle += 1;
                auto amp = 64;
                obj2Pos.setX( static_cast< const int >( somePosition1.getX() + sin( i ) * amp ) );
                obj2Pos.setY( static_cast< const int >( somePosition1.getY() + cos( i ) * amp ) );
                auto greeVal = static_cast<uint8_t>( 127 + 127 * sin( i / 2 ) );
                this->bckgroundColor.setGCU( greeVal );
                m_activeWindow->setBackgroundColor( this->bckgroundColor );
                i += 0.02;
            }
        }
    }
    SDL2W::IKeyboardObservable* m_keyObservable = nullptr;
    SDL2W::IWindowFactory* m_windowFactory = nullptr;
    SDL2W::IWindow* m_activeWindow = nullptr;

    SDL2W::ColorS bckgroundColor;

    CUL::LckPrim<bool> runLoop{ true };

    SDL2W::ISDL2Wrapper* m_sdlW = nullptr;

    std::thread m_thread;

    CUL::FS::Path m_someFile = CUL::FS::Path( "../media/pikaczu.bmp" );

    SDL2W::ISprite* m_obj1 = nullptr;
    SDL2W::ISprite* m_obj2 = nullptr;
    SDL2W::ISprite* m_obj3 = nullptr;
    SDL2W::ISprite* m_obj4 = nullptr;

    CUL::Math::Vector3Dd obj1Scale;
    CUL::Math::Vector3Di obj2Pos0;
    CUL::Math::Vector3Di obj3Pos;
    CUL::Math::Vector3Di obj4Pos;
};

#if _MSC_VER
#pragma warning( push )
#pragma warning( disable: 4100 )
#endif
int main( int argc, char** argv )
{
    TestApp testApp;
    testApp.runMainLoop();
    return 0;
}
#if _MSC_VER
#pragma warning( pop )
#endif