#include "SDL2Wrapper/ISDL2Wrapper.hpp"
#include "SDL2Wrapper/IWindow.hpp"
#include "SDL2Wrapper/WindowData.hpp"
#include "SDL2Wrapper/IWindowEventListener.hpp"
#include "SDL2Wrapper/Input/IKeyboardObserver.hpp"

#include "CUL/Log/ILogger.hpp"
#include "CUL/Graphics/Position3DDMutexed.hpp"
#include "CUL/Graphics/Color.hpp"
#include "CUL/Video/IFPSCounter.hpp"
#include "CUL/ITimer.hpp"
#include "CUL/Threading/ThreadUtils.hpp"
#include "CUL/Filesystem/FS.hpp"
#include "CUL/GenericUtils/LckPrim.hpp"
#include "CUL/Math/Angle.hpp"
#include "CUL/STL_IMPORTS/STD_thread.hpp"
#include "CUL/STL_IMPORTS/STD_cmath.hpp"
#include "CUL/Log/ILogContainer.hpp"
#include "CUL/GenericUtils/IConfigFile.hpp"
#include "CUL/GenericUtils/ConsoleUtilities.hpp"
#include "CUL/GenericUtils/SimpleAssert.hpp"

using Pos3D = CUL::Graphics::Position3DDMutexed;
using WinEventType = SDL2W::WindowEvent::Type;
using SDL2WinData = SDL2W::WindowData;
template <typename TYPE> using DumbPtr = CUL::GUTILS::DumbPtr<TYPE>;


SDL2WinData winData;
DumbPtr<CUL::GUTILS::IConfigFile> configFile;
SDL2W::ISDL2Wrapper* sdlWrapper = nullptr;

#ifdef _MSC_VER
#pragma warning( push )
#pragma warning( disable : 4820 )
#endif

struct Object
{
    SDL2W::ISprite* sprite = nullptr;
};

class TestApp final:
    public SDL2W::IKeyboardObserver,
    public SDL2W::IMouseObserver,
    private SDL2W::IWindowEventObserver
{
public:
    TestApp():
        m_sdlW( SDL2W::ISDL2Wrapper::createSDL2Wrapper() )
    {
        sdlWrapper = m_sdlW.get();
        m_sdlW->init( winData, "../media/Config.txt" );

        configFile = sdlWrapper->getConfig();

        m_logger = m_sdlW->getLogger();
        m_activeWindow = m_sdlW->getMainWindow();

        m_activeWindow->toggleFpsCounter( true, 4u );

        m_sdlW->setInputLatency( 1024 );

        CUL::FS::Path pikachuBmp = configFile->getValue( "pikachuBmp" );
        CUL::FS::Path pikachuPng = configFile->getValue( "pikachuPng" );

        CUL::Assert::simple( pikachuBmp.exists(), pikachuBmp.getPath() + " does not exist." );
        CUL::Assert::simple( pikachuPng.exists(), pikachuPng.getPath() + " does not exist." );

        auto aw = m_activeWindow;
        m_obj1.sprite = m_sdlW->createSprite( pikachuBmp, aw );
        m_obj2 = m_sdlW->createSprite( pikachuPng, aw );
        m_obj3 = m_sdlW->createSprite( pikachuPng, aw );
        m_obj4 = m_sdlW->createSprite( pikachuBmp, aw );
        m_obj5 = m_sdlW->createSprite( pikachuPng, aw );
        obj4Pos = m_obj4->getPosition();

        m_keyObservable = m_sdlW.get();
    }

    TestApp( const TestApp& rhv ) = delete;
    TestApp( TestApp&& rhv ) = delete;

    void runMainLoop()
    {
        m_sdlW->registerKeyboardEventListener( this );
        m_sdlW->registerWindowEventListener( this );
        m_sdlW->registerMouseEventListener( this );
        m_objectMoveThread = std::thread( &TestApp::objectManagmentFun, this );
        m_sdlW->runEventLoop();
    }

    void onKeyBoardEvent( const SDL2W::IKey& key ) override
    {
        if( false == key.getKeyIsDown() )
        {
            return;
        }

        m_logger->log( "KEY: " + key.getKeyName().string() );

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

    void onMouseEvent( const SDL2W::MouseData& md ) override
    {
        m_obj5->setX( static_cast<double>( md.getX() ) );
        m_obj5->setY( static_cast<double>( md.getY() ) );
    }

    void onWindowEvent( const WinEventType windowEventType ) override
    {
        m_logger->log( "Event Type: " + CUL::String( static_cast<short>(windowEventType) ) );
        if( WinEventType::CLOSE == windowEventType )
        {
            m_sdlW->stopEventLoop();
            runLoop = false;
        }
    }

    ~TestApp()
    {
        if( m_objectMoveThread.joinable() )
        {
            m_objectMoveThread.join();
        }
    }

protected:
private:

    void objectManagmentFun()
    {
        m_sdlW->getCul()->getThreadUtils().setCurrentThreadName( "TestApp::objectManagmentFun" );

        CUL::MATH::Vector3Dd someScale;
        m_obj1.sprite->setScale( someScale );

        obj3Pos.setXYZ( 300, 300, 0 );

        Pos3D obj1Pos( 100, 100, 0 );
        Pos3D somePosition1( 450, 100, 0 );
        Pos3D somePosition2( 600, 600, 0 );
        Pos3D somePosition3( 800, 500, 0 );
        Pos3D obj2Pos;
        obj4Pos.setXYZ( 380, 380, 0 );
        m_obj1.sprite->setPosition( obj1Pos );
        m_obj2->setPosition( somePosition2 );
        m_obj3->setPivotX( 0.1 );
        m_obj3->setPosition( somePosition3 );
        someScale.setXYZ( 0.5, 0.5, 0.0 );
        m_obj3->setScale( someScale );

        unsigned sleepTimeinMs = 2;
        double i = 0.0;
        CUL::MATH::Angle obj2Angle;
        CUL::MATH::Angle obj3Angle;

        while( runLoop )
        {
            m_sdlW->renderFrame();
            CUL::ITimer::sleepMiliSeconds( sleepTimeinMs );
            auto xScale = ( sin( i ) + 1.0 ) * 0.25;
            auto yScale = ( cos( i ) + 1.0 ) * 0.25;
            someScale.setXYZ( xScale, yScale, 0 );
            m_obj1.sprite->setScale( someScale );
            m_obj2->setScale( someScale );
            m_obj2->rotate( obj2Angle );
            m_obj3->rotate( obj3Angle );

            m_obj4->setPosition( obj4Pos );

            obj2Angle -= 1;
            obj3Angle += 1;
            bckgroundColor.setGF( sin( i / 2 ) * 0.5f + 0.5f );
            m_activeWindow->setBackgroundColor( bckgroundColor );
            i += 0.02;
        }
    }

    SDL2W::IKeyboardObservable* m_keyObservable = nullptr;
    SDL2W::IWindow* m_activeWindow = nullptr;

    CUL::Graphics::ColorS bckgroundColor;

    CUL::GUTILS::LckPrim<bool> runLoop = true;

    std::unique_ptr< SDL2W::ISDL2Wrapper> m_sdlW;
    std::unique_ptr<CUL::Video::IFPSCounter> m_fpsCounter;

    std::thread m_objectMoveThread;

    Object m_obj1;
    SDL2W::ISprite* m_obj2 = nullptr;
    SDL2W::ISprite* m_obj3 = nullptr;
    SDL2W::ISprite* m_obj4 = nullptr;
    SDL2W::ISprite* m_obj5 = nullptr;

    Pos3D obj2Pos0;
    Pos3D obj3Pos;
    Pos3D obj4Pos;

    CUL::LOG::ILogger* m_logger;

private:
    TestApp& operator=( const TestApp& rhv ) = delete;
};

#ifdef _MSC_VER
#pragma warning( pop )
#endif

int main( int argc, char** argv )
{
    winData.currentRes.setSize( 800, 600 );
    winData.pos.setXY( 128, 128 );

#if defined _MSC_VER
    winData.rendererName = "direct3d";
#else
    winData.rendererName = "software";
#endif

    CUL::GUTILS::ConsoleUtilities console;
    console.setArgs( argc, argv );
    console.printInputParameters();

    TestApp testApp;
    testApp.runMainLoop();
    return 0;
}