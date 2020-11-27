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
using SDL2WinData = SDL2W::WindowData;


void logMsg(
    const CUL::String& msg,
    const CUL::LOG::Severity severity = CUL::LOG::Severity::INFO )
{
    CUL::LOG::LOG_CONTAINER::getLogger()->log( msg, severity );
}

#if _MSC_VER
#pragma warning( push )
#pragma warning( disable: 4820 )
#endif
class TestApp final:
    public SDL2W::IKeyboardObserver,
    public SDL2W::IMouseObserver,
    private SDL2W::IWindowEventObserver
{
public:
    TestApp():
        m_sdlW( SDL2W::createSDL2Wrapper() )
    {
        SDL2WinData winData;
        winData.name = "libsdl2wrapperTestAppGui";
        winData.pos = { 600, 600, 0 };
        winData.size = { 800, 600 };

        m_sdlW->init( winData, "../media/Config.txt" );
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

    void onMouseEvent( const SDL2W::MouseData& ) override
    {
    }

    void onWindowEvent( const SDL2W::WindowEvent::Type windowEventType ) override
    {
        logMsg( "Event Type: " + CUL::String( static_cast< short >( windowEventType ) ) );
        if( SDL2W::WindowEvent::Type::CLOSE == windowEventType )
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
            logMsg( "CURRENT FPS: " + CUL::String( currentFpsCount ) );
            logMsg( "AVERAGE FPS: " + CUL::String( averageFpsCount ) );
        }
    }

    void objectManagmentFun()
    {
        CUL::ThreadUtils::setCurrentThreadName( "TestApp::objectManagmentFun" );
        unsigned sleepTimeinMs = 18;
        double i = 0.0;
        CUL::MATH::Angle obj2Angle;
        CUL::MATH::Angle obj3Angle;

        while( runLoop )
        {
            m_sdlW->renderFrame();
            CUL::ITimer::sleepMiliSeconds( sleepTimeinMs );

        }
    }

    SDL2W::IKeyboardObservable* m_keyObservable = nullptr;
    SDL2W::IWindow* m_activeWindow = nullptr;

    SDL2W::ColorS bckgroundColor;

    CUL::GUTILS::LckPrim<bool> runLoop{ true };

    std::unique_ptr< SDL2W::ISDL2Wrapper> m_sdlW;
    std::unique_ptr<CUL::Video::IFPSCounter> m_fpsCounter;

    std::thread m_objectMoveThread;
    std::thread m_dataInfoThread;

};
#if _MSC_VER
#pragma warning( pop )
#endif

int main( int, char** )
{
    TestApp testApp;
    testApp.runMainLoop();
    return 0;
}