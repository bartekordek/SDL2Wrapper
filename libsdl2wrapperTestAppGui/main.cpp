#include "SDL2Wrapper/ISDL2Wrapper.hpp"
#include "CUL/Video/IFPSCounter.hpp"
#include "CUL/ITimer.hpp"
#include "CUL/ThreadUtils.hpp"
#include "CUL/Filesystem/FS.hpp"
#include "CUL/LckPrim.hpp"
#include "CUL/Math/Angle.hpp"
#include "CUL/STD_thread.hpp"
#include "CUL/STD_cmath.hpp"
#include "CUL/Log/ILogContainer.hpp"

using Pos3D = CUL::Graphics::Position3DDMutexed;

void logMsg(
    CUL::CnstMyStr& msg,
    const CUL::LOG::Severity severity = CUL::LOG::Severity::INFO )
{
    CUL::LOG::LOG_CONTAINER::getLogger()->log( msg, severity );
}

class TestApp final:
    public SDL2W::IKeyboardObserver,
    public SDL2W::IMouseObserver,
    private SDL2W::IWindowEventObserver
{
public:
    TestApp():
        m_sdlW( SDL2W::createSDL2Wrapper(
            SDL2W::Vector3Di( 200, 200, 0 ),
            SDL2W::Vector3Du( 1024, 768, 0 ),
            "Test app.", true ) )
    {
        m_activeWindow = m_sdlW->getMainWindow();
        m_fpsCounter.reset( CUL::Video::FPSCounterFactory::getConcreteFPSCounter() );
        m_activeWindow->addFPSCounter( m_fpsCounter.get() );
        m_fpsCounter->start();
        m_sdlW->setInputLatency( 1024 );
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
        logMsg( "KEY: " + key.getKeyName().string() );

        static int delta = 8;

        if( m_keyObservable->isKeyUp( "D" ) )
        {
        }

        if( m_keyObservable->isKeyUp( "A" ) )
        {
        }

        if( m_keyObservable->isKeyUp( "W" ) )
        {
        }

        if( m_keyObservable->isKeyUp( "S" ) )
        {
        }

        if( ( key.getKeyName() == "q" ) || ( key.getKeyName() == "Q" ) )
        {
            quitApp();
        }
    }

    void onMouseEvent( const SDL2W::IMouseData& ) override
    {
    }

    void onWindowEvent( const WindowEventType windowEventType ) override
    {
        logMsg( "Event Type: " + CUL::MyString( static_cast< short >( windowEventType ) ) );
        if( WindowEventType::CLOSE == windowEventType )
        {
            quitApp();
        }
    }

    void quitApp()
    {
        m_sdlW->stopEventLoop();
        runLoop = false;
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
            logMsg( "CURRENT FPS: " + CUL::MyString( currentFpsCount ) );
            logMsg( "AVERAGE FPS: " + CUL::MyString( averageFpsCount ) );
        }
    }

    void objectManagmentFun()
    {
        CUL::ThreadUtils::setCurrentThreadName( "TestApp::objectManagmentFun" );
        unsigned sleepTimeinMs = 18;
        double i = 0.0;
        CUL::Math::Angle obj2Angle;
        CUL::Math::Angle obj3Angle;

        while( runLoop )
        {
            m_sdlW->renderFrame();
            CUL::ITimer::sleepMiliSeconds( sleepTimeinMs );

        }
    }

    SDL2W::IKeyboardObservable* m_keyObservable = nullptr;
    SDL2W::IWindow* m_activeWindow = nullptr;

    SDL2W::ColorS bckgroundColor;

    CUL::LckPrim<bool> runLoop{ true };

    std::unique_ptr< SDL2W::ISDL2Wrapper> m_sdlW;
    std::unique_ptr<CUL::Video::IFPSCounter> m_fpsCounter;

    std::thread m_objectMoveThread;
    std::thread m_dataInfoThread;

};

int main( int, char** )
{
    TestApp testApp;
    testApp.runMainLoop();
    return 0;
}