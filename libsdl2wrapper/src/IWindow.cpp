#include "SDL2Wrapper/IWindow.hpp"

using namespace SDL2W;



IWindow::IWindow(
    const CUL::Math::Vector3Di& pos,
    const CUL::Math::Vector3Du& size,
    const std::string& name ):
        position( pos ),
        m_size( size ),
        name( name )
{
}

IWindow::IWindow( const IWindow& win )
{
    if( this != & win )
    {
        this->position = win.position;
        this->m_size = win.m_size;
        this->name = win.name;
    }
}

IWindow::~IWindow()
{
}

IWindow& IWindow::operator=( const IWindow& window )
{
    if( this != &window )
    {
        this->position = window.position;
        this->m_size = window.m_size;
        this->name = window.name;
    }
    return *this;
}

const CUL::Math::Vector3Di& IWindow::getPos()const
{
    return this->position;
}

void IWindow::setPos( const  CUL::Math::Vector3Di& pos )
{
    this->position = pos;
}

const CUL::Math::Vector3Du& IWindow::getSize()const
{
    return this->m_size;
}

void IWindow::setSize( const CUL::Math::Vector3Du& winSize )
{
    this->m_size = winSize;
}

const std::string& IWindow::getName()const
{
    return this->name;
}

void IWindow::setName( const std::string& winName )
{
    this->name = winName;
}