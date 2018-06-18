#pragma once

#include "SDL2Wrapper/IWindowFactory.hpp"
#include "CUL/STD_map.hpp"
#include "CUL/STD_vector.hpp"

namespace SDL2W
{
    using WindowCollection = std::map<IWindow*, std::unique_ptr<IWindow>>;
    class WindowCreatorConcrete final:
        public IWindowFactory
    {
    public:
        WindowCreatorConcrete(
            const Vector3Di& pos,
            const Vector3Du& size,
            CnstStr& winName);
        WindowCreatorConcrete( const WindowCreatorConcrete& rhv ) = delete;
        ~WindowCreatorConcrete();
        WindowCreatorConcrete& operator=( WindowCreatorConcrete& rhv ) = delete;

        IWindow* createWindow(
            const Vector3Di& pos,
            const Vector3Du& size,
            CnstStr& winName ) override;

        IWindow* getMainWindow() override;
        IWindow* getWindow( const char* winName ) override;

    protected:
    private:

        WindowCollection m_windows;
        IWindow* m_mainWindow = nullptr;
    };
}