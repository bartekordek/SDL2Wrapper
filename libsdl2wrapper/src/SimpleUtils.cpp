#include "SimpleUtils.hpp"

using namespace SDL2W;

void SDL2W::logMsg(
    CUL::CnstMyStr& msg,
    const CUL::LOG::Severity severity )
{
    CUL::LOG::LOG_CONTAINER::getLogger()->log( msg, severity );
}

void SDL2W::Assert( const bool result, CUL::CnstMyStr& msg )
{
    CUL::Assert::simple( result, msg );
}