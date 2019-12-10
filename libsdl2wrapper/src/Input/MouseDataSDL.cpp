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
    return static_cast<unsigned>( m_buttonStates.size() );
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
    if( m_buttonStates.size() < buttonIndex )
    {
        return m_buttonStates.at( buttonIndex );
    }
    return false;
}
#ifdef _MSC_VER
#pragma warning( pop )
#endif

Cint MouseDataSDL::getX() const
{
    return m_x;
}

Cint MouseDataSDL::getY() const
{
    return m_y;
}

Cint MouseDataSDL::getWheelX() const
{
    return m_wheelX;
}

Cint MouseDataSDL::getWheelY() const
{
    return m_wheelY;
}

const WheelDirection MouseDataSDL::getWheelDirection() const
{
    return m_wheelDirection;
}

void MouseDataSDL::setPos( Cint x, Cint y )
{
    const CUL::String log = "RegularSDL2Window::RegularSDL2Window( " +
        CUL::String( x ) + ", " +
        CUL::String( y ) + " );";
    CUL::LOG::LOG_CONTAINER::getLogger()->log( log );
    m_x = x;
    m_y = y;
}

void MouseDataSDL::setState( const MouseButtonIndex buttonIndex, const bool isUp )
{
    const CUL::String log = "MouseDataSDL::setState( " +
        CUL::String( buttonIndex ) + ", " +
        CUL::String( isUp ) + " );";
    CUL::LOG::LOG_CONTAINER::getLogger()->log( log );
    m_buttonStates[ buttonIndex ] = isUp;
}
void MouseDataSDL::setWheel( Cint x, Cint y, const WheelDirection direction )
{
    const CUL::String log = "MouseDataSDL::setState( " +
        CUL::String( x ) + ", " +
        CUL::String( y ) + ", " +
        CUL::String( static_cast<unsigned>( direction ) ) + " );";
    CUL::LOG::LOG_CONTAINER::getLogger()->log( log );
    m_wheelX = x;
    m_wheelY = y;
    m_wheelDirection = direction;
}