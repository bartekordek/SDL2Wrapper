#include "SDL2Wrapper/ISDL2Wrapper.hpp"
#include "CUL/Video/IFPSCounter.hpp"
#include "CUL/ITimer.hpp"
#include "CUL/ThreadUtils.hpp"
#include "CUL/Filesystem/FS.hpp"
#include "CUL/GenericUtils/LckPrim.hpp"
#include "CUL/Math/Angle.hpp"
#include "CUL/STL_IMPORTS/STD_thread.hpp"
#include "CUL/STL_IMPORTS/STD_cmath.hpp"
#include "CUL/Log/ILogContainer.hpp"

using Pos3D = CUL::Graphics::Position3DDMutexed;
using WinEventType = SDL2W::WindowEvent::Type;
using SDL2WinData = SDL2W::WindowData;

SDL2WinData winData;

class TestApp final:
    public SDL2W::IKeyboardObserver,
    public SDL2W::IMouseObserver,
    private SDL2W::IWindowEventObserver
{
public:
    TestApp():
        m_sdlW( SDL2W::createSDL2Wrapper() )
    {
        m_sdlW->init( winData );
        m_activeWindow = m_sdlW->getMainWindow();
        m_fpsCounter.reset( CUL::Video::FPSCounterFactory::getConcreteFPSCounter() );
        m_activeWindow->addFPSCounter( m_fpsCounter.get() );
        m_fpsCounter->start();
        m_sdlW->setInputLatency( 1024 );

        if( m_pikachuBmp.exists() )
        {
            auto aw = m_activeWindow;
            m_obj1 = m_sdlW->createSprite( m_pikachuPng, aw );
            m_obj2 = m_sdlW->createSprite( m_pikachuPng, aw );
            m_obj3 = m_sdlW->createSprite( m_pikachuBmp, aw );
            m_obj4 = m_sdlW->createSprite( m_pikachuBmp, aw );
            m_obj5 = m_sdlW->createSprite( m_pikachuBmp, aw );
            obj4Pos = m_obj4->getPosition();
        }
        m_keyObservable = m_sdlW.get();
    }

    TestApp( const TestApp& rhv ) = delete;

    ~TestApp()
    {
        if( m_objectMoveThread.joinable() )
        {
            m_objectMoveThread.join();
        }

        if( m_dataInfoThread.joinable() )
        {
            m_dataInfoThread.join();
        }
    }

    TestApp& operator=( const TestApp& rhv ) = delete;

    void runMainLoop()
    {
        m_sdlW->registerKeyboardEventListener( this );
        m_sdlW->registerWindowEventListener( this );
        m_sdlW->registerMouseEventListener( this );
        m_objectMoveThread = std::thread( &TestApp::objectManagmentFun, this );
        m_dataInfoThread = std::thread( &TestApp::dataPrintFun, this );
        m_sdlW->runEventLoop();
    }

    void onKeyBoardEvent( const SDL2W::IKey& key ) override
    {
        if( false == key.getKeyIsDown() )
        {
            return;
        }
        CUL::LOG::LOG_CONTAINER::getLogger()->log( "KEY: " + key.getKeyName().string() );

        static int delta = 8;

        if( m_keyObservable->isKeyUp( "D" ) )
        {
            obj4Pos.setX( obj4Pos.getX() + delta );
        }

        if( m_keyObservable->isKeyUp( "A" ) )
        {
            obj4Pos.setX( obj4Pos.getX() - delta );
        }

        if( m_keyObservable->isKeyUp( "W" ) )
        {
            obj4Pos.setY( obj4Pos.getY() - delta );
        }

        if( m_keyObservable->isKeyUp( "S" ) )
        {
            obj4Pos.setY( obj4Pos.getY() + delta );
        }

        if( ( key.getKeyName() == "q" ) || ( key.getKeyName() == "Q" ) )
        {
            m_sdlW->stopEventLoop();
            runLoop = false;
        }
    }

    void onMouseEvent( const SDL2W::IMouseData& md ) override
    {
        m_obj5->setX( static_cast<double>( md.getX() ) );
        m_obj5->setY( static_cast<double>( md.getY() ) );
    }

    void onWindowEvent( const WinEventType windowEventType ) override
    {
        CUL::LOG::LOG_CONTAINER::getLogger()->log( "Event Type: " + CUL::String( static_cast< short >( windowEventType ) ) );
        if( WinEventType::CLOSE == windowEventType )
        {
            m_sdlW->stopEventLoop();
            runLoop = false;
        }
    }

protected:
private:
    void dataPrintFun()
    {
        while( runLoop )
        {
            CUL::ITimer::sleepSeconds( 2 );
            const auto currentFpsCount = m_fpsCounter->getCurrentFps();
            const auto averageFpsCount = m_fpsCounter->getAverageFps();
            const CUL::String messageCfps = "CURRENT FPS: " + CUL::String( currentFpsCount );
            const CUL::String messageAfps = "AVERAGE FPS: " + CUL::String( averageFpsCount );
            CUL::LOG::LOG_CONTAINER::getLogger()->log( messageCfps );
            CUL::LOG::LOG_CONTAINER::getLogger()->log( messageAfps );
        }
    }

    void objectManagmentFun()
    {
        CUL::ThreadUtils::setCurrentThreadName( "TestApp::objectManagmentFun" );
        if( m_pikachuBmp.exists() )
        {
            CUL::Math::Vector3Dd someScale;
            m_obj1->setScale( someScale );

            obj3Pos.setXYZ( 300, 300, 0 );

            Pos3D obj1Pos( 100, 100, 0 );
            Pos3D somePosition1( 450, 100, 0 );
            Pos3D somePosition2( 600, 600, 0 );
            Pos3D somePosition3( 800, 500, 0 );
            Pos3D obj2Pos;
            m_obj1->setPosition( obj1Pos );
            m_obj2->setPosition( somePosition2 );
            m_obj3->setPivotX( 0.1 );
            m_obj3->setPosition( somePosition3 );
            someScale.setXYZ( 0.5, 0.5, 0.0 );
            m_obj3->setScale( someScale );

            unsigned sleepTimeinMs = 2;
            double i = 0.0;
            CUL::Math::Angle obj2Angle;
            CUL::Math::Angle obj3Angle;

            while( runLoop )
            {
                m_sdlW->renderFrame();
                CUL::ITimer::sleepMiliSeconds( sleepTimeinMs );
                auto xScale = ( sin( i ) + 1.0 ) * 0.25;
                auto yScale = ( cos( i ) + 1.0 ) * 0.25;
                someScale.setXYZ( xScale, yScale, 0 );
                m_obj1->setScale( someScale );
                m_obj2->setScale( someScale );
                m_obj2->rotate( obj2Angle );
                m_obj3->rotate( obj3Angle );

                m_obj4->setPosition( obj4Pos );

                obj2Angle -= 1;
                obj3Angle += 1;
                auto amp = 64;
                obj2Pos.setX( somePosition1.getX() + sin( i ) * amp );
                obj2Pos.setY( somePosition1.getY() + cos( i ) * amp );
                auto greeVal = static_cast<uint8_t>( 127 + 127 * sin( i / 2 ) );
                bckgroundColor.setGCU( greeVal );
                m_activeWindow->setBackgroundColor( bckgroundColor );
                i += 0.02;
            }
        }
    }
    SDL2W::IKeyboardObservable* m_keyObservable = nullptr;
    SDL2W::IWindow* m_activeWindow = nullptr;

    SDL2W::ColorS bckgroundColor;

    CUL::GUTILS::LckPrim<bool> runLoop = true;

    std::unique_ptr< SDL2W::ISDL2Wrapper> m_sdlW;
    std::unique_ptr<CUL::Video::IFPSCounter> m_fpsCounter;

    std::thread m_objectMoveThread;
    std::thread m_dataInfoThread;

    CUL::FS::Path m_pikachuBmp = CUL::FS::Path( "../media/pikaczu.bmp" );
    CUL::FS::Path m_pikachuPng = CUL::FS::Path( "../media/pikaczu.png" );

    SDL2W::ISprite* m_obj1 = nullptr;
    SDL2W::ISprite* m_obj2 = nullptr;
    SDL2W::ISprite* m_obj3 = nullptr;
    SDL2W::ISprite* m_obj4 = nullptr;
    SDL2W::ISprite* m_obj5 = nullptr;

    Pos3D obj1Scale;
    Pos3D obj2Pos0;
    Pos3D obj3Pos;
    Pos3D obj4Pos;

};

#if _MSC_VER
#pragma warning( push )
#pragma warning( disable: 4100 )
#endif
int main( int argc, char** argv )
{
    winData.size.setSize( 800, 600 );
    winData.pos.setXYZ( 480, 480, 0 );
    winData.withOpenGL = false;

    TestApp testApp;
    testApp.runMainLoop();
    return 0;
}
#if _MSC_VER
#pragma warning( pop )
#endif