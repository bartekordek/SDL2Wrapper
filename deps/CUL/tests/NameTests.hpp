#pragma once

#include "CUL/MyString.hpp"
#include "gtest/gtest.h"

class NameTests: public ::testing::Test
{
protected:
    NameTests()
    {
    }

    virtual ~NameTests()
    {
    }

    virtual void SetUp()
    {
    }

    virtual void TearDown()
    {
    }
    CUL::MyString genericName = CUL::MyString( "Generic name." );
};