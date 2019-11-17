#include "Input/MouseDataSDL.hpp"
#include "CUL/Log/ILogContainer.hpp"

using MouseDataSDL = SDL2W::MouseDataSDL;
using MouseButtonIndex = SDL2W::MouseButtonIndex;
using WheelDirection = SDL2W::WheelDirection;
using Cunt = SDL2W::Cunt;
using Cint = SDL2W::Cint;

MouseDataSDL::MouseDataSDL()
{

}

MouseDataSDL::~MouseDataSDL()
{
}

Cunt MouseDataSDL::getMouseButtonCount() const
{
    return static_cast<unsigned>( this->m_buttonStates.size() );
}

#ifdef _MSC_VER
// Yes, I know that is a Spectre mitigation.
// But for now, I let this as TODO, since i don't know
// How to fix this.
// TODO
#pragma warning( push )
#pragma warning( disable: 5045 )
#endif
const bool MouseDataSDL::isButtonDown( const MouseButtonIndex buttonIndex ) const
{
    if( this->m_buttonStates.size() < buttonIndex )
    {
        return this->m_buttonStates.at( buttonIndex );
    }
    return false;
}
#ifdef _MSC_VER
#pragma warning( pop )
#endif

Cint MouseDataSDL::getX() const
{
    return this->m_x;
}

Cint MouseDataSDL::getY() const
{
    return this->m_y;
}

Cint MouseDataSDL::getWheelX() const
{
    return this->m_wheelX;
}

Cint MouseDataSDL::getWheelY() const
{
    return this->m_wheelY;
}

const WheelDirection MouseDataSDL::getWheelDirection() const
{
    return this->m_wheelDirection;
}

void MouseDataSDL::setPos( Cint x, Cint y )
{
    const CUL::MyString log = "RegularSDL2Window::RegularSDL2Window( " +
        CUL::MyString( x ) + ", " +
        CUL::MyString( y ) + " );";
    CUL::LOG::LOG_CONTAINER::getLogger()->log( log );
    this->m_x = x;
    this->m_y = y;
}

void MouseDataSDL::setState( const MouseButtonIndex buttonIndex, const bool isUp )
{
    const CUL::MyString log = "MouseDataSDL::setState( " +
        CUL::MyString( buttonIndex ) + ", " +
        CUL::MyString( isUp ) + " );";
    CUL::LOG::LOG_CONTAINER::getLogger()->log( log );
    this->m_buttonStates[ buttonIndex ] = isUp;
}
void MouseDataSDL::setWheel( Cint x, Cint y, const WheelDirection direction )
{
    const CUL::MyString log = "MouseDataSDL::setState( " +
        CUL::MyString( x ) + ", " +
        CUL::MyString( y ) + ", " +
        CUL::MyString( static_cast<unsigned>( direction ) ) + " );";
    CUL::LOG::LOG_CONTAINER::getLogger()->log( log );
    this->m_wheelX = x;
    this->m_wheelY = y;
    this->m_wheelDirection = direction;
}