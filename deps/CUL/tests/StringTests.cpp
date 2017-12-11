#include "CUL/MyString.hpp"
#include "StringTest.hpp"

TEST_F( StringTests, shouldStringBeLowerWhenLowered )
{
    CUL::MyString string( "someString" );
    ASSERT_EQ( string.toLower(), "somestring" );
}

TEST_F( StringTests, shouldStringBeLowerWhenLoweredByStatic )
{
    CUL::MyString string( "someString" );
    ASSERT_EQ( string.toLower(), "somestring" );
}