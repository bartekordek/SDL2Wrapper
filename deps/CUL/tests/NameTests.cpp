#include "NameTests.hpp"
#include "CUL/Named.hpp"

TEST_F( NameTests, CopyConstructorWorks )
{
    CUL::Name oldName( genericName );
    CUL::Name newName( oldName );
    ASSERT_EQ( newName.GetName(), oldName.GetName() );
}

TEST_F( NameTests, ConstructorWithParameterWorks )
{
    CUL::Name name( genericName );
    ASSERT_EQ( name.GetName(), genericName );
}

TEST_F( NameTests, AccessorsWork )
{
    CUL::Name name;
    name.setName( genericName );
    ASSERT_EQ( name.GetName(), genericName );
}