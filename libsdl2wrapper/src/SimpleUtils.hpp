#pragma once

#include "CUL/Log/ILogContainer.hpp"
#include "CUL/SimpleAssert.hpp"

NAMESPACE_BEGIN( SDL2W )

void logMsg(
    CUL::CnstMyStr& msg,
    const CUL::LOG::Severity severity = CUL::LOG::Severity::INFO );
void Assert( const bool result, CUL::CnstMyStr& msg );

NAMESPACE_END( SDL2W )