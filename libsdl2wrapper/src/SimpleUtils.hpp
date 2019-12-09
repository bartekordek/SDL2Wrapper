#pragma once

#include "CUL/Log/ILogContainer.hpp"
#include "CUL/GenericUtils/SimpleAssert.hpp"

NAMESPACE_BEGIN( SDL2W )

void logMsg(
    CUL::CsStr& msg,
    const CUL::LOG::Severity severity = CUL::LOG::Severity::INFO );
void Assert( const bool result, CUL::CsStr& msg );

NAMESPACE_END( SDL2W )