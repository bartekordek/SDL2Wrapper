#include "Vector3DTests.hpp"
#include "CUL/Math/Vector3D.hpp"

TEST_F( Vector3DTests, initialization )
{
	CUL::Math::Vector3Di v( 1, 2, 3 );
	GTEST_ASSERT_EQ( v.getX(), 1 );
	GTEST_ASSERT_EQ( v.getY(), 2 );
	GTEST_ASSERT_EQ( v.getZ(), 3 );
}

TEST_F( Vector3DTests, multiplicationVecTimesVec )
{
	CUL::Math::Vector3Di v1( 2, 2, 2 );
	CUL::Math::Vector3Di v2( 3, 3, 3 );
	v1 *= v2;

	GTEST_ASSERT_EQ( v1, CUL::Math::Vector3Di( 6, 6, 6 ) );
}

TEST_F( Vector3DTests, addVec2Vec )
{
	CUL::Math::Vector3Di v1( 2, 2, 2 );
	CUL::Math::Vector3Di v2( 3, 3, 3 );
	v1 += v2;
	GTEST_ASSERT_EQ( v1, CUL::Math::Vector3Di( 5, 5, 5 ) );
}

TEST_F( Vector3DTests, multiplicationVecTimesScalar )
{
	CUL::Math::Vector3Di v( 3, 3, 3 );
	v *= 10;
	GTEST_ASSERT_EQ( v, CUL::Math::Vector3Di( 30, 30, 30 ) );
}

TEST_F( Vector3DTests, assigmentOperator )
{
	CUL::Math::Vector3Di v1( 1, 2, 3 );
	CUL::Math::Vector3Di v2( 3, 2, 1 );
	v1 = v2;
	GTEST_ASSERT_EQ( v1, v2 );
}