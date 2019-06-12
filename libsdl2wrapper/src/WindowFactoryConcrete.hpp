#pragma once

#include "SDL2Wrapper/IWindowFactory.hpp"
#include "CUL/STD_map.hpp"
#include "CUL/STD_vector.hpp"
#include "CUL/STD_memory.hpp"

namespace SDL2W
{
    
    class WindowCreatorConcrete final:
        public IWindowFactory
    {
    public:
        explicit WindowCreatorConcrete();
        WindowCreatorConcrete( const WindowCreatorConcrete& rhv ) = delete;
        ~WindowCreatorConcrete();
        WindowCreatorConcrete& operator=( WindowCreatorConcrete& rhv ) = delete;

        IWindow* createWindow(
            const Vector3Di& pos = Vector3Di( 0, 0, 0 ),
            const Vector3Du& size = Vector3Du( 800, 600, 0 ),
            CUL::CnstMyStr& winName = "Generic Window Name.",
            const bool withOpenGL = true ) override;


    protected:
    private:
    };
}
