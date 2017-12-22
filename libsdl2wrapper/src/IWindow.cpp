#include "SDL2Wrapper\IWindow.hpp"

using namespace SDL2W;

IWindow::IWindow(
	const CUL::XYPosition<int>& pos,
	const  CUL::Size<unsigned>& size,
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

const  CUL::XYPosition<int>& IWindow::getPos()const
{
	return this->position;
}

void IWindow::setPos( const  CUL::XYPosition<int>& pos )
{
	this->position = pos;
}

const CUL::Size<unsigned>& IWindow::getSize()const
{
	return this->m_size;
}

void IWindow::setSize( const CUL::Size<unsigned>& winSize )
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