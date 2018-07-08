#pragma once

#include "SDL2Wrapper/SDL2Wrapper.hpp"
#include "SDL2Wrapper/IWindow.hpp"

namespace SDL2W
{
    class SDL2WAPI IWindowFactory
    {
    public:
        IWindowFactory();
        IWindowFactory( const IWindowFactory& rhv ) = delete;
        virtual ~IWindowFactory();

        IWindowFactory& operator=( const IWindowFactory& rhv ) = delete;

        virtual IWindow* createWindow(
            const Vector3Di& pos, const Vector3Du& size,
            CnstStr& winName ) = 0;

        virtual IWindow* createWindowOGL(
            const Vector3Di& pos, const Vector3Du& size,
            CnstStr& winName,
            const int major = 2, const int minor = 1 ) = 0;

        virtual IWindow* getMainWindow() = 0;
        virtual IWindow* getWindow( const char* winName ) = 0;

    protected:
    private:
    };
}