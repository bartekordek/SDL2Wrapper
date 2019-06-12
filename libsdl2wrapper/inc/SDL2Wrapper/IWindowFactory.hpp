#pragma once

#include "SDL2Wrapper/IWindow.hpp"

#include "CUL/MyString.hpp"

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
            const Vector3Di& pos = Vector3Di( 0, 0, 0 ),
            const Vector3Du& size = Vector3Du( 800, 600, 0 ),
            CUL::CnstMyStr& winName = "Generic Window Name.",
            const bool withOpenGL = true ) = 0;

    protected:
    private:
    };
}