#pragma once

#include "SDL2Wrapper/IWindowFactory.hpp"
#include "CUL/STD_map.hpp"
#include "CUL/STD_vector.hpp"
#include "CUL/STD_memory.hpp"

namespace SDL2W
{
    using WindowCollection = std::map<IWindow*, std::unique_ptr<IWindow>>;
    class WindowCreatorConcrete final:
        public IWindowFactory
    {
    public:
        WindowCreatorConcrete(
            const Vector3Di& pos, const Vector3Du& size,
            CUL::CnstMyStr& winName,
            const bool opengl = false );
        WindowCreatorConcrete( const WindowCreatorConcrete& rhv ) = delete;
        ~WindowCreatorConcrete();
        WindowCreatorConcrete& operator=( WindowCreatorConcrete& rhv ) = delete;

        IWindow* createWindow(
            const Vector3Di& pos = Vector3Di( 0, 0, 0 ),
            const Vector3Du& size = Vector3Du( 800, 600, 0 ),
            CUL::CnstMyStr& winName = "Generic Window Name." ) override;

        IWindow* createWindowOGL(
            const Vector3Di& pos = Vector3Di( 0, 0, 0 ),
            const Vector3Du& size = Vector3Du( 800, 600, 0 ),
            CUL::CnstMyStr& winName = "Generic Window Name." ) override;

        IWindow* getMainWindow() override;
        IWindow* getWindow( const char* winName ) override;
        WindowCollection& getAllWindows();

    protected:
    private:

        WindowCollection m_windows;
        IWindow* m_mainWindow = nullptr;
    };
}
