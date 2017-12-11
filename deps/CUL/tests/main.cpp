#include "gtest/gtest.h"

int main( int argc, char **argv )
{
	::testing::InitGoogleTest( &argc, argv );
	const int result = RUN_ALL_TESTS();
#ifdef _WIN32
	std::getchar();
	return result;
#else
	return result;
#endif
}